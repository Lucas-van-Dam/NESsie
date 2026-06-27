#include "TestCpu.h"

#pragma region AND

#pragma region Immediate
TEST_F(CPUTest, ANDImmediateBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDIM);
	memory.set_byte(0xFFFD, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ANDImmediateCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDIM);
	memory.set_byte(0xFFFD, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ANDImmediateCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDIM);
	memory.set_byte(0xFFFD, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, ANDZeroPageBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01011101;

	BYTE zeroPageAddress = 0x07;

	BYTE ANDvalue = 0b10110101;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDZP);
	memory.set_byte(0xFFFD, zeroPageAddress);

	memory.set_byte(zeroPageAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ANDZeroPageCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDZP);
	memory.set_byte(0xFFFD, zeroPageAddress);

	memory.set_byte(zeroPageAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ANDZeroPageCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDZP);
	memory.set_byte(0xFFFD, zeroPageAddress);

	memory.set_byte(zeroPageAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, ANDZeroPageXBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDZPX);
	memory.set_byte(0xFFFD, zeroPageAddress);

	memory.set_byte(zeroPageAddress + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ANDZeroPageXCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDZPX);
	memory.set_byte(0xFFFD, zeroPageAddress);

	memory.set_byte(zeroPageAddress + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ANDZeroPageXCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	memory.set_byte(0xFFFC, CPU::ANDZPX);
	memory.set_byte(0xFFFD, zeroPageAddress);

	memory.set_byte(zeroPageAddress + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, memory);

	EXPECT_EQ(cpu.A, accumulatorValue & ANDvalue);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion
#pragma endregion
