//
// Created by LucasVanDam on 07/07/2026.
//
#pragma once
#include <array>

#include "Mapper.h"

namespace NESsie {
    class TestMapper : public Mapper {

        public:
        TestMapper();

        virtual void write_prg(WORD address, BYTE value) override;
        virtual BYTE read_prg(WORD address) override;

        virtual void write_chr(WORD address, BYTE value) override;
        virtual BYTE read_chr(WORD address) override;

        virtual NameTableMirroring getNameTableMirroring() override;

        constexpr static WORD MAPPED_MEMORY_SIZE = 0xFFFF - 0x8000;
    private:
        std::array<BYTE, MAPPED_MEMORY_SIZE> memory;

    };
}