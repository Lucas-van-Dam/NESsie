//
// Created by LucasVanDam on 08/07/2026.
//
#pragma once
#include <array>
#include <coroutine>
#include <utility>

#include "defines.h"
#include "mapper.h"

namespace NESsie {

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
    ppu(std::shared_ptr<Mapper> mapper, MainBus& MainBus);

    void write_to_ppu(WORD address, BYTE value);
    BYTE read_from_ppu(WORD address);

    void step();
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

    std::shared_ptr<Mapper> mapper;
    MainBus& mainbus;

    uint32_t frame = 0;
    uint32_t scanline = 261;
    uint32_t cycle = 1;

    WORD nametableBaseAddress = 0;

    static constexpr uint16_t scanlinesPerFrame_ = 262;
    static constexpr uint16_t cyclesPerScanline_ = 341;
};
}

