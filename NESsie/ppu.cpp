//
// Created by LucasVanDam on 08/07/2026.
//

#include "ppu.h"

#include <iostream>
#include <coroutine>

#include "mainbus.h"

namespace NESsie {
    ppu::ppu(std::shared_ptr<Mapper> mapper, MainBus &MainBus) : mapper(std::move(mapper)), mainbus(MainBus) {
        ppuctrl_ = static_cast<PPUCTRL>(0);
        ppumask_ = static_cast<PPUMASK>(0);
        ppustatus_ = static_cast<PPUSTATUS>(0b10100000);
        OAMADDR = 0x00;
        firstWrite = true;
        PPUSCROLL = 0x0000;
        PPUADDR = 0x0000;
        PPUDATA = 0x00;
    }

    void ppu::write_to_ppu(WORD address, BYTE value) {
        if (address < 0x3FFF)
            address = address & 0x3FFF;
        switch (static_cast<ppuHardwareRegisters>(address)) {
            case ppuHardwareRegisters::PPUCTRL: {
                ppuctrl_ = static_cast<PPUCTRL>(value);
                auto mask = 0b11 << 10;
                auto values = (value & 0b11) << 10;
                t = (t & ~mask) | (values & mask);
                internalDataBus = value;
                break;
            }
            case ppuHardwareRegisters::PPUMASK: {
                ppumask_ = static_cast<PPUMASK>(value);
                internalDataBus = value;
                break;
            }
            case ppuHardwareRegisters::PPUSTATUS:
                ppustatus_ = static_cast<PPUSTATUS>(value & 0b11100000);
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
                PPUSCROLL = value << (firstWrite ? 8 : 0);
                if (firstWrite) {
                    t = (t & ~0b11111) | (value >> 3);
                    fineXScroll = value & 0b111;
                }
                else {
                    auto AB =   value & 0b11000000;
                    auto CDE =  value & 0b00111000;
                    auto FGH =  value & 0b00000111;

                    t = t & ~0b111001111100000;
                    t |= (FGH << 12);
                    t |= (AB << 2);
                    t |= (CDE << 2);
                }
                firstWrite = !firstWrite;
                internalDataBus = value;
                break;
            case ppuHardwareRegisters::PPUADDR:
                PPUADDR = (value << (firstWrite ? 8 : 0)) & (!firstWrite ? 0xFF : 0b00111111);
                if (firstWrite) {
                    t = t & (~0b11111111 << 8);
                    t |= (value & 0b00111111) << 8;
                }
                else {
                    t &= 0b11111111;
                    t |= value;
                    // TODO: wait for 1 - 1.5 dots before transfer
                    v = t;
                }
                firstWrite = !firstWrite;
                internalDataBus = value;
                break;
            case ppuHardwareRegisters::PPUDATA: {
                internalDataBus = value;
                if (PPUADDR < 0x2000)
                    std::cerr << "Trying to write to chr-rom" << std::endl;
                else if (PPUADDR < 0x3000) {
                    NameTableMirroring mirroring = mapper->getNameTableMirroring();
                    switch (mirroring) {
                        case NameTableMirroring::Horizontal: {
                            if (PPUADDR > 0x27FF)
                                VRAM[PPUADDR - 0x2400] = value;
                            else
                                VRAM[PPUADDR - 0x2000] = value;
                            break;
                        }
                        case NameTableMirroring::Vertical: {
                            if (PPUADDR > 0x2400 && PPUADDR < 0x27FF) {
                                VRAM[PPUADDR - 0x2400] = value;
                            } else if (PPUADDR > 0x2C00 && PPUADDR < 0x2FFF) {
                                VRAM[PPUADDR - 0x2400] = value;
                            } else {
                                VRAM[PPUADDR - 0x2000] = value;
                            }
                        }
                    }
                } else {
                    if (PPUADDR > 0x3FFF || PPUADDR < 0x0) {
                        PPUADDR = 0x3FFF;
                        std::cerr << "vram overflow" << std::endl;
                    }
                    VRAM[PPUADDR - 0x2000] = value;
                }
                PPUADDR += (ppuctrl_ & 0b00000100) ? 32 : 1;
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
                std::cerr << "Unknown Hardware Register" << std::endl;
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
                internalDataBus = VRAM[PPUADDR];
                PPUADDR += (ppuctrl_ & 0b00000100) ? 32 : 1;
                break;
            case ppuHardwareRegisters::OAMDMA:
                break;
            default:
                std::cerr << "Unknown Hardware Register" << std::endl;
        }
        return internalDataBus;
    }

    void ppu::step() {
        if (scanline == 261 && frame & 1 && cycle == 339) {
            std::cout << "frame start" << std::endl;
            cycle = 0;
            scanline = 0;
            frame++;
        } else if (cycle == 340) {
            cycle = 0;
            if (scanline >= 261) {
                scanline = 0;
                frame++;
            } else
                scanline++;
        }

        if (scanline < 240) {
            if (cycle == 0) {
                BYTE nametable = ppuctrl_ & 0b111;
                switch (nametable) {
                    case 0:
                        nametableBaseAddress = 0x2000;
                        break;
                    case 1:
                        nametableBaseAddress = 0x2400;
                        break;
                    case 2:
                        nametableBaseAddress = 0x2800;
                        break;
                    case 3:
                        nametableBaseAddress = 0x2C00;
                        break;
                }
            } else if (cycle < 257) {
                switch ((cycle - 1) % 8) {
                    case 0: {
                        WORD offset = 2 + ((cycle - 1) % 8);
                        auto nametableByte = VRAM[nametableBaseAddress + offset];
                        //std::cout << "fetching nametable byte;" << std::endl;
                        break;
                    }
                    case 2:

                        //std::cout << "fetching attribute byte;" << std::endl;
                        break;
                    case 4:
                        //std::cout << "fetching pattern table tile low byte;" << std::endl;
                        break;
                    case 6:
                        //std::cout << "fetching pattern table tile high byte;" << std::endl;
                        break;
                    default:
                        break;
                }
                // fetch nametable byte (2 cycles)
                // fetch attribute table byte (2 cycles)
                // fetch pattern table tile low (2 cycles)
                // fetch pattern table tile high (2 cycles)
            }
        }

        cycle++;
    }
}
