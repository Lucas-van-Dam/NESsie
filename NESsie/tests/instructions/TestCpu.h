#include <gtest/gtest.h>
#include <cpu.h>

class CPUTest : public testing::Test {
protected:
	CPUTest() {
		cpu.initialize(memory);
	}

	~CPUTest() {

	}

	CPU::CPU cpu;
	Memory::Memory memory;
};