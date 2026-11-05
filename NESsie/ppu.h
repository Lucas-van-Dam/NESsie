//
// Created by LucasVanDam on 08/07/2026.
//
#pragma once
#include <array>
#include <coroutine>
#include <utility>

#include "defines.h"
#include "mapper.h"
#include "SDL3/SDL_pixels.h"

namespace NESsie {
    class VirtualScreen;

    class MainBus;

    enum class ppuHardwareRegisters : WORD {
        PPUCTRL = 0x2000,
        PPUMASK = 0x2001,
        PPUSTATUS = 0x2002,
        OAMADDR = 0x2003,
        OAMDATA = 0x2004,
        PPUSCROLL = 0x2005,
        PPUADDR = 0x2006,
        PPUDATA = 0x2007,
        OAMDMA = 0x4014,
    };

class ppu {
public:
    ppu(std::shared_ptr<Mapper> mapper, MainBus& MainBus, VirtualScreen& screen);

    void write_to_ppu(WORD address, BYTE value);
    BYTE read_from_ppu(WORD address);

    void step();

    bool do_nmi();
private:
    struct PPUCTRL {
        BYTE nametableAddress : 2;
        bool vramIncrement : 1;
        bool spritePatternTableAddress : 1;
        bool backgroundPatternTableAddress : 1;
        bool spriteSize : 1;
        bool masterSlaveSelect : 1;
        bool vblankNMIEnable : 1;

        operator BYTE(){
            return *reinterpret_cast<BYTE*>(this);
        }
    } ppuctrl_;
    struct PPUMASK {
        bool greyscale : 1;
        bool showBackgroundLeft : 1;
        bool showSpritesLeft : 1;
        bool enableBackgroundRendering : 1;
        bool enableSpritesRendering : 1;
        bool emphasizeRed : 1; // green on PAL
        bool emphasizeGreen : 1; // red on PAL
        bool emphasizeBlue : 1;

        operator BYTE(){
            return *reinterpret_cast<BYTE*>(this);
        }
    } ppumask_;
    struct PPUSTATUS {
        BYTE openBus : 5;
        bool spriteOverflow : 1;
        bool sprite0Hit : 1;
        bool vblank : 1;

        operator BYTE(){
            return *reinterpret_cast<BYTE*>(this);
        }
    } ppustatus_;

    BYTE OAMADDR;
    BYTE OAMDATA;
    WORD PPUSCROLL;
    WORD PPUADDR;
    BYTE PPUDATA;
    BYTE OAMDMA;

    BYTE internalDataBus;

    std::array<BYTE, 64 * 4> OAM;

    std::array<BYTE, 0x2000> VRAM;

    WORD v = 0;
    WORD t = 0;
    BYTE fineXScroll : 3;
    bool firstWrite = true;

    BYTE currentTile;
    BYTE currentAttribute;
    BYTE currentPatternLow;
    BYTE currentPatternHigh;

    std::vector<Uint32> colorBuffer;
    std::vector<BYTE> secondaryOAM;

    bool nmi_output;

    std::shared_ptr<Mapper> mapper;
    MainBus& mainbus;
    VirtualScreen& screen;

    uint32_t frame = 0;
    uint32_t scanline = 261;
    uint32_t cycle = 1;

    WORD nametableBaseAddress = 0;

    static constexpr uint16_t scanlinesPerFrame_ = 262;
    static constexpr uint16_t cyclesPerScanline_ = 341;
};

    //temporary color data
    static constexpr std::array nesPalette = {
        SDL_Color{84, 84, 84},    SDL_Color{0, 30, 116},   SDL_Color{8, 16, 144},   SDL_Color{48, 0, 136},
        SDL_Color{68, 0, 100},    SDL_Color{92, 0, 48},    SDL_Color{84, 4, 0},     SDL_Color{60, 24, 0},
        SDL_Color{32, 42, 0},     SDL_Color{8, 58, 0},     SDL_Color{0, 64, 0},     SDL_Color{0, 60, 0},
        SDL_Color{0, 50, 60},     SDL_Color{0, 0, 0},      SDL_Color{0, 0, 0},      SDL_Color{0, 0, 0},

        SDL_Color{152, 150, 152}, SDL_Color{8, 76, 196},   SDL_Color{48, 50, 236},  SDL_Color{92, 30, 228},
        SDL_Color{136, 20, 176},  SDL_Color{160, 20, 100}, SDL_Color{152, 34, 32},  SDL_Color{120, 60, 0},
        SDL_Color{84, 90, 0},     SDL_Color{40, 114, 0},   SDL_Color{8, 124, 0},    SDL_Color{0, 118, 40},
        SDL_Color{0, 102, 120},   SDL_Color{0, 0, 0},      SDL_Color{0, 0, 0},      SDL_Color{0, 0, 0},

        SDL_Color{236, 238, 236}, SDL_Color{76, 154, 236}, SDL_Color{120, 124, 236},SDL_Color{176, 98, 236},
        SDL_Color{228, 84, 236},  SDL_Color{236, 88, 180}, SDL_Color{236, 106, 100},SDL_Color{212, 136, 32},
        SDL_Color{160, 170, 0},   SDL_Color{116, 196, 0},  SDL_Color{76, 208, 32},  SDL_Color{56, 204, 108},
        SDL_Color{56, 180, 204},  SDL_Color{60, 60, 60},   SDL_Color{0, 0, 0},      SDL_Color{0, 0, 0},

        SDL_Color{236, 238, 236}, SDL_Color{168, 204, 236},SDL_Color{188, 188, 236},SDL_Color{212, 178, 236},
        SDL_Color{236, 174, 236}, SDL_Color{236, 174, 212},SDL_Color{236, 180, 176},SDL_Color{228, 196, 144},
        SDL_Color{204, 210, 120}, SDL_Color{180, 222, 120},SDL_Color{168, 226, 144},SDL_Color{152, 226, 180},
        SDL_Color{160, 214, 228}, SDL_Color{160, 162, 160},SDL_Color{0, 0, 0},      SDL_Color{0, 0, 0}
    };
}

