//
// Created by LucasVanDam on 29/07/2026.
//
#pragma once
#include "defines.h"

namespace NESsie {
    class Input {
    public:
        Input ();

        const WORD INPUT1_ADDR = 0x4016;
        const WORD INPUT2_ADDR = 0x4017;

        void write(WORD address, BYTE value);
        BYTE read(WORD address);

        void step();
    private:
        bool strobeBit = false;
        BYTE currentInputState = 0x00;
        BYTE currentInputIndex = 0x00;

        const bool * keys;
    };
}

