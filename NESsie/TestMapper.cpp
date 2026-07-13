//
// Created by LucasVanDam on 07/07/2026.
//

#include "TestMapper.h"

namespace NESsie {
    TestMapper::TestMapper() : Mapper({}) {}

    void TestMapper::write_prg(WORD address, BYTE value) {
        memory[address - 0x8000] = value;
    }

    BYTE TestMapper::read_prg(WORD address) {
        return memory[address - 0x8000];
    }

    void TestMapper::write_chr(WORD address, BYTE value) {
    }

    BYTE TestMapper::read_chr(WORD address) {
        return 0;
    }

    NameTableMirroring TestMapper::getNameTableMirroring() {
        return Mapper::getNameTableMirroring();
    }

    std::shared_ptr<Mapper> create_test_mapper() {
        return std::make_shared<TestMapper>();
    }
}
