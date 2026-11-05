//
// Created by LucasVanDam on 08/07/2026.
//

#include "ppu.h"

#include <iostream>
#include <coroutine>
#include <thread>

#include "mainbus.h"
#include "VirtualScreen.h"

namespace NESsie {
    ppu::ppu(std::shared_ptr<Mapper> mapper, MainBus &MainBus, VirtualScreen &screen) : mapper(std::move(mapper)),
        mainbus(MainBus), screen(screen) {
        ppuctrl_ = static_cast<PPUCTRL>(0);
        ppumask_ = static_cast<PPUMASK>(0);
        ppustatus_ = static_cast<PPUSTATUS>(0b10100000);
        OAMADDR = 0x00;
        firstWrite = true;
        PPUSCROLL = 0x0000;
        t = 0;
        PPUDATA = 0x00;

        colorBuffer.resize(256 * 240);

        secondaryOAM.resize(32);
    }

    void ppu::write_to_ppu(WORD address, BYTE value) {
        if (address < 0x3FFF)
            address = address & 0x3FFF;
        switch (static_cast<ppuHardwareRegisters>(address)) {
            case ppuHardwareRegisters::PPUCTRL: {
                ppuctrl_ = std::bit_cast<PPUCTRL>(value);
                auto mask = 0b11 << 10;
                auto values = (value & 0b11) << 10;
                t = (t & ~mask) | (values & mask);

                nmi_output = ppuctrl_.vblankNMIEnable;

                if ((value & 0b11) > 0) {
                    std::cout << "nametable select: " << std::hex << ppuctrl_.nametableAddress << std::endl;
                }


                internalDataBus = value;

                break;
            }
            case ppuHardwareRegisters::PPUMASK: {
                ppumask_ = std::bit_cast<PPUMASK>(value);
                internalDataBus = value;
                //             std::cout
                // << "PPUMASK = " << std::hex << static_cast<int>(value)
                // << " bg=" << static_cast<int>(ppumask_.enableBackgroundRendering)
                // << " sprites=" << static_cast<int>(ppumask_.enableSpritesRendering)
                // << '\n';
                break;
            }
            case ppuHardwareRegisters::PPUSTATUS:
                ppustatus_ = std::bit_cast<PPUSTATUS>(static_cast<BYTE>(value & 0b11100000));
                internalDataBus = value & 0b11100000 | (internalDataBus & 0b00011111);
                break;
            case ppuHardwareRegisters::OAMADDR:
                OAMADDR = value;
                internalDataBus = value;
                break;
            case ppuHardwareRegisters::OAMDATA:
                if (OAMADDR > 64 * 4 - 1) {
                    OAMADDR = 64 * 4 - 1;
                    std::cerr << "OAM Address Overflow" << std::endl;
                }
                OAM[OAMADDR] = value;
                internalDataBus = value;
                OAMADDR++;
                break;
            case ppuHardwareRegisters::PPUSCROLL:
                if (firstWrite) {
                    t = (t & ~0b11111) | (value >> 3);
                    fineXScroll = value & 0b111;
                } else {
                    auto AB = value & 0b11000000;
                    auto CDE = value & 0b00111000;
                    auto FGH = value & 0b00000111;

                    t = t & ~0b111001111100000;
                    t |= (FGH << 12);
                    t |= (AB << 2);
                    t |= (CDE << 2);
                }
                firstWrite = !firstWrite;
                internalDataBus = value;
                break;
            case ppuHardwareRegisters::PPUADDR:
                if (firstWrite) {
                    t = t & (~0b11111111 << 8);
                    t |= (value & 0b00111111) << 8;
                } else {
                    t &= ~0b11111111;
                    t |= value;
                    // TODO: wait for 1 - 1.5 dots before transfer
                    v = t;
                    //std::cout << "PPUADDR loaded: " << std::hex << v << '\n';
                }
                firstWrite = !firstWrite;
                internalDataBus = value;
                break;
            case ppuHardwareRegisters::PPUDATA: {
                //std::cout << "PPUDATA write at: " << std::hex << v << '\n';
                internalDataBus = value;
                if (v < 0x2000)
                    std::cout << "Trying to write to chr-ram" << std::endl;
                else if (v < 0x3000) {
                    NameTableMirroring mirroring = mapper->getNameTableMirroring();
                    switch (mirroring) {
                        case NameTableMirroring::Horizontal: {
                            if (v > 0x27FF)
                                VRAM[v - 0x2400] = value;
                            else
                                VRAM[v - 0x2000] = value;
                            break;
                        }
                        case NameTableMirroring::Vertical: {
                            if (v > 0x2400 && v < 0x27FF) {
                                VRAM[v - 0x2400] = value;
                            } else if (v > 0x2C00 && v < 0x2FFF) {
                                VRAM[v - 0x2400] = value;
                            } else {
                                VRAM[v - 0x2000] = value;
                            }
                        }
                    }
                } else {
                    if (v > 0x3FFF || v < 0x0) {
                        std::cerr << "vram overflow" << std::endl;
                        break;
                    }
                    VRAM[v - 0x2000] = value;
                }
                v += ppuctrl_.vramIncrement ? 32 : 1;
                //std::cout << "PPUADDR incremented to: " << std::hex << v << '\n';
                break;
            }
            case ppuHardwareRegisters::OAMDMA: {
                WORD mainBusAddress = value << 8;
                for (int i = 0; i < 256; i++) {
                    OAM[i] = mainbus.read_byte(mainBusAddress | i);
                    // TODO: check if this needs to start at OAMADDR, which might cause corruption if not properly reset to 0 first
                }
                break;
            }
            default:
                //std::cerr << "Unknown Hardware Register" << std::endl;
                break;
        }
    }

    BYTE ppu::read_from_ppu(WORD address) {
        switch (static_cast<ppuHardwareRegisters>(address)) {
            case ppuHardwareRegisters::PPUCTRL:
                break;
            case ppuHardwareRegisters::PPUMASK:
                break;
            case ppuHardwareRegisters::PPUSTATUS:
                internalDataBus = ppustatus_ & 0b11100000 | (internalDataBus & 0b00011111);
                ppustatus_.vblank = false;
                firstWrite = true;
                break;
            case ppuHardwareRegisters::OAMADDR:
                break;
            case ppuHardwareRegisters::OAMDATA:
                internalDataBus = OAM[OAMADDR];
                break;
            case ppuHardwareRegisters::PPUSCROLL:
                break;
            case ppuHardwareRegisters::PPUADDR:
                break;
            case ppuHardwareRegisters::PPUDATA:
                internalDataBus = VRAM[v];
                v += (ppuctrl_ & 0b00000100) ? 32 : 1;
                break;
            case ppuHardwareRegisters::OAMDMA:
                break;
            default:
                break;
                //std::cerr << "Unknown Hardware Register" << std::endl;
        }
        return internalDataBus;
    }

    void ppu::step() {
        if (scanline == 261 && frame & 1 && cycle == 339) {
            //std::cout << "frame start" << std::endl;
            cycle = 0;
            scanline = 0;
            frame++;
            screen.clear_screen(SDL_Color{0, 0, 0});
            screen.set_screen(colorBuffer, 256, 240, frame);
            //screen.display();
        } else if (cycle == 340) {
            cycle = 0;
            if (scanline >= 261) {
                scanline = 0;
                frame++;
                screen.clear_screen(SDL_Color{0, 0, 0});
                screen.set_screen(colorBuffer, 256, 240, frame);
                //screen.display();
            } else
                scanline++;
        }

        if (scanline < 240 && (ppumask_.enableBackgroundRendering || ppumask_.enableSpritesRendering)) {
            if (cycle == 0) {
            } else if (cycle < 257) {
                if (cycle == 1) {
                    std::ranges::fill(secondaryOAM, 0xFF);

                    int n = 0;
                    int m = 0;
                    int currentSecondaryAddress = 0;
                    while (true) {
                        BYTE sprite_y = OAM[n * 4];

                        if ((scanline - 1) - sprite_y < 8) {
                            secondaryOAM[currentSecondaryAddress++] = OAM[n * 4];
                            secondaryOAM[currentSecondaryAddress++] = OAM[n * 4 + 1];
                            secondaryOAM[currentSecondaryAddress++] = OAM[n * 4 + 2];
                            secondaryOAM[currentSecondaryAddress++] = OAM[n * 4 + 3];
                        }

                        if (n >= 63) {
                            n = 0;
                            break;
                        }
                        if (currentSecondaryAddress < 32) {
                            n++;
                            continue;
                        }
                        if (currentSecondaryAddress >= 32) {
                            while (true) {
                                BYTE test_y = OAM[n * 4 + m];
                                if (scanline - test_y < 8) {
                                    ppustatus_.spriteOverflow = true;

                                    for (int i = 0; i < 3; i++) {
                                        if (m == 3) {
                                            n++;
                                            m = 0;
                                        } else {
                                            m++;
                                        }
                                    }
                                } else {
                                    if (n >= 63)
                                        break;

                                    n++;

                                    m++;
                                    m %= 3;
                                }
                            }
                            break;
                        }
                    }
                }

                switch ((cycle - 1) % 8) {
                    case 0: {
                        auto tile_address = 0x2000 | (v & 0x0FFF);

                        currentTile = VRAM[tile_address - 0x2000];


                        //std::cout << "fetching nametable byte;" << std::endl;
                        break;
                    }
                    case 2: {
                        auto attribute_address = 0x23C0 | (v & 0x0C00) | ((v >> 4) & 0x38) | ((v >> 2) & 0x07);
                        currentAttribute = VRAM[attribute_address - 0x2000];
                        // copied from the nesdev wiki
                        //std::cout << "fetching attribute byte;" << std::endl;
                        break;
                    }
                    case 4: {
                        const BYTE fineY = static_cast<BYTE>((v >> 12) & 0x07);

                        currentPatternLow = mapper->read_chr(
                            (ppuctrl_.backgroundPatternTableAddress ? 0x1000 : 0x0000) + (currentTile * 16) + fineY);
                        //std::cout << "fetching pattern table tile low byte;" << std::endl;
                        break;
                    }
                    case 6: {
                        const BYTE fineY = static_cast<BYTE>((v >> 12) & 0x07);

                        currentPatternHigh = mapper->read_chr(
                            ((ppuctrl_.backgroundPatternTableAddress ? 0x1000 : 0x0000) + (currentTile * 16) + fineY) +
                            8);

                        //std::cout << "fetching pattern table tile high byte;" << std::endl;
                        const BYTE coarseX = v & 0x001F;
                        const BYTE coarseY = (v >> 5) & 0x001F;
                        const BYTE y = fineY + coarseY * 8;
                        const BYTE x = (v & 0x001F) * 8;

                        const BYTE shift =
                                ((coarseY & 0x02) << 1) |
                                (coarseX & 0x02);

                        const BYTE paletteSelect =
                                (currentAttribute >> shift) & 0x03;

                        WORD paletteAddress;

                        bool backgroundTransparent = false;
                        bool spriteTransparent = false;
                        bool isSpriteForeground = false;

                        BYTE spriteColor = 0;
                        BYTE backgroundColor;

                        for (int i = 0; i < 8; i++) {
                            BYTE bit = 7 - i;

                            BYTE patternValue =
                                    ((currentPatternLow >> bit) & 1) |
                                    (((currentPatternHigh >> bit) & 1) << 1);

                            if (patternValue == 0) {
                                paletteAddress = 0x3F00;
                                backgroundTransparent = true;
                            } else {
                                paletteAddress =
                                        0x3F00
                                        + paletteSelect * 4
                                        + patternValue;

                                backgroundTransparent = false;
                            }

                            paletteAddress -= 0x2000;

                            for (int j = 0; j < 8; j++) {
                                spriteTransparent = true; // for when going over the edge of the sprite, to prevent coloring the entire 8 pixel wide slot
                                bool longSprites = ppuctrl_.spriteSize;

                                if (longSprites) {
                                    SDL_Log("Dont support long sprites yet");
                                }

                                BYTE spr_x = secondaryOAM[j * 4 + 3];

                                if (0 > x + i - spr_x || x + i - spr_x >= 8)
                                    continue;

                                BYTE spr_y = secondaryOAM[j * 4 + 0] + 1;
                                BYTE tile = secondaryOAM[j * 4 + 1];
                                BYTE attribute = secondaryOAM[j * 4 + 2];

                                int x_shift = (x + i - spr_x) % 8;
                                int y_offset = (y - spr_y) % 8;

                                if ((attribute & 0x40) == 0)
                                    x_shift ^= 7;
                                if ((attribute & 0x80) != 0)
                                    y_offset ^= (7);

                                WORD addr = 0;

                                addr = tile * 16 + y_offset;
                                if (ppuctrl_.spritePatternTableAddress)
                                    addr += 0x1000;

                                spriteColor = (mapper->read_chr(addr) >> (x_shift)) & 1;
                                spriteColor |= ((mapper->read_chr(addr + 8) >> (x_shift)) & 1) << 1;

                                if (!spriteColor) {
                                    spriteTransparent = true;
                                    continue;
                                }

                                spriteTransparent = false;

                                spriteColor |= 0x10;
                                spriteColor |= (attribute & 0x3) << 2;

                                isSpriteForeground = !(attribute & 0x20);

                                if (!ppustatus_.sprite0Hit && ppumask_.enableBackgroundRendering && j == 0 && !
                                    backgroundTransparent) {
                                    ppustatus_.sprite0Hit = true;
                                }

                                break;
                            }

                            if ((backgroundTransparent && !spriteTransparent) || (
                                    !backgroundTransparent && !spriteTransparent && isSpriteForeground))
                                paletteAddress = spriteColor + 0x1F00;
                            else if (backgroundTransparent && spriteTransparent)
                                paletteAddress = 0x1F00;

                            BYTE colorIndex = VRAM[paletteAddress] % 0x3F;

                            Uint32 pixel = SDL_MapRGBA(
                                SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_RGBA32),
                                nullptr,
                                nesPalette[colorIndex].r,
                                nesPalette[colorIndex].g,
                                nesPalette[colorIndex].b,
                                255
                            );

                            colorBuffer[x + i + y * 256] = pixel;
                        }
                        //screen.set_tile_pixels(x, y, currentPatternLow);


                        if ((v & 0x001F) == 31) {
                            // if coarse X == 31
                            v &= ~0x001F; // coarse X = 0
                            v ^= 0x0400; // switch horizontal nametable
                            //std::cout << "PPUADDR incremented to: " << std::hex << v << '\n';
                        } else {
                            v += 1; // increment coarse X
                            //std::cout << "PPUADDR incremented to: " << std::hex << v << '\n';
                        }
                        break;
                    }
                    default:
                        break;
                }

                if (cycle == 256) {
                    if ((v & 0x7000) != 0x7000) {
                        // if fine Y < 7
                        v += 0x1000; // increment fine Y
                    } else {
                        v &= ~0x7000; // fine Y = 0
                        int y = (v & 0x03E0) >> 5; // let y = coarse Y
                        if (y == 29) {
                            y = 0; // coarse Y = 0
                            v ^= 0x0800; // switch vertical nametable
                        } else if (y == 31) {
                            y = 0; // coarse Y = 0, nametable not switched
                        } else {
                            y += 1; // increment coarse Y
                            v = (v & ~0x03E0) | (y << 5); // put coarse Y back into v
                        }
                    }
                    //std::cout << "PPUADDR incremented to: " << std::hex << v << '\n';
                }
            } else if (cycle >= 257 && cycle <= 320) {
                if (cycle == 257) {
                    constexpr auto mask = 0b10000011111;
                    v &= ~mask;
                    v |= (t & mask);

                    //std::cout << "PPUADDR changed to: " << std::hex << v << '\n';
                }

                // fetch tile data for next 2 sprites
            } else if (cycle >= 321 && cycle <= 336) {
                switch ((cycle - 1) % 8) {
                    case 0: {
                        auto tile_address = 0x2000 | (v & 0x0FFF);

                        //std::cout << "fetching nametable byte;" << std::endl;
                        break;
                    }
                    case 2: {
                        auto attribute_address = 0x23C0 | (v & 0x0C00) | ((v >> 4) & 0x38) | ((v >> 2) & 0x07);
                        // copied from the nesdev wiki
                        //std::cout << "fetching attribute byte;" << std::endl;
                        break;
                    }
                    case 4:
                        //std::cout << "fetching pattern table tile low byte;" << std::endl;
                        break;
                    case 6: {
                        //std::cout << "fetching pattern table tile high byte;" << std::endl;
                        if ((v & 0x001F) == 31) {
                            // if coarse X == 31
                            v &= ~0x001F; // coarse X = 0
                            v ^= 0x0400; // switch horizontal nametable
                        } else
                            v += 1; // increment coarse X

                        //std::cout << "PPUADDR incremented to: " << std::hex << v << '\n';
                        break;
                    }
                    default:
                        break;
                }
            } else if (cycle >= 337 && cycle <= 340) {
                if (cycle == 337) {
                    auto tile_address = 0x2000 | (v & 0x0FFF);
                }
                if (cycle == 339) {
                    auto tile_address = 0x2000 | (v & 0x0FFF);
                }
            }
        }

        if (scanline == 241 && cycle == 1) {
            ppustatus_.vblank = true;
        } else if (scanline == 261) {
            if (cycle == 1) {
                ppustatus_.vblank = false;
            }
            if (cycle >= 280 && cycle <= 304 && (
                    ppumask_.enableBackgroundRendering || ppumask_.enableSpritesRendering)) {
                constexpr auto mask = 0b111101111100000;
                v &= ~mask;
                v |= (t & mask);

                //std::cout << "PPUADDR changed to: " << std::hex << v << '\n';
            }
        }

        cycle++;
    }

    bool ppu::do_nmi() {
        const auto nmi = ppustatus_.vblank && nmi_output;
        if (nmi)
            nmi_output = false;
        return nmi;
    }
}
