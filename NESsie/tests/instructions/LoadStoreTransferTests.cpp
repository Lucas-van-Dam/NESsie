#include <iostream>

#include "TestCpu.h"



#pragma region Load
#pragma region LDA
#pragma region Immediate

TEST_F(CPUTest, LDAImmediateBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	memory.set_byte(0xFFFC, CPU::LDAIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, LDAImmediateCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	memory.set_byte(0xFFFC, CPU::LDAIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, LDAImmediateCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x83;

	memory.set_byte(0xFFFC, CPU::LDAIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

#pragma endregion

#pragma region ZeroPage

TEST_F(CPUTest, LDAZeroPageBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDAZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAZeroPageCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDAZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAZeroPageCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDAZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, LDAZeroPageXBehavesCorrectly) {
	BYTE address = 0x45;
	BYTE value = 0x07;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAZPX);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAZeroPageXCorrectlySetsZeroFlag) {
	BYTE address = 0x45;
	BYTE value = 0x00;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAZPX);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAZeroPageXCorrectlySetsNegativeFlag) {
	BYTE address = 0x45;
	BYTE value = 0x87;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAZPX);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAZeroPageXCorrectlyOverFlows) {
	BYTE address = 0x45;
	BYTE value = 0x07;
	BYTE addedAddress = 0xF0;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAZPX);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, LDAAbsoluteBehavesCorrectly) {
	WORD address = 0x0345;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAAbsoluteCorrectlySetsZeroFlag) {
	WORD address = 0x0345;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAAbsoluteCorrectlySetsNegativeFlag) {
	WORD address = 0x0345;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region AbsoluteX
TEST_F(CPUTest, LDAAbsoluteXBehavesCorrectly) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABSX);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAAbsoluteXCorrectlySetsZeroFlag) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABSX);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAAbsoluteXCorrectlySetsNegativeFlag) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABSX);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAAbsoluteXCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	WORD address = 0x03F5;
	BYTE addedAddress = 0x14;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 5;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABSX);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region AbsoluteY
TEST_F(CPUTest, LDAAbsoluteYBehavesCorrectly) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABSY);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAAbsoluteYCorrectlySetsZeroFlag) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABSY);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAAbsoluteYCorrectlySetsNegativeFlag) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABSY);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAAbsoluteYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	WORD address = 0x03F5;
	BYTE addedAddress = 0x14;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 5;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAABSY);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region IndirectX
TEST_F(CPUTest, LDAIndirectXBehavesCorrectly) {
	BYTE zeroPageAddress = 0x33;
	BYTE addedZeroPageAddress = 0x12;
	WORD address = 0x0345;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 6;

	cpu.X = addedZeroPageAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAINDX);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress + addedZeroPageAddress, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAIndirectXCorrectlySetsZeroFlag) {
	BYTE zeroPageAddress = 0x33;
	BYTE addedZeroPageAddress = 0x12;
	WORD address = 0x0345;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 6;

	cpu.X = addedZeroPageAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAINDX);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress + addedZeroPageAddress, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAIndirectXCorrectlySetsNegativeFlag) {
	BYTE zeroPageAddress = 0x33;
	BYTE addedZeroPageAddress = 0x12;
	WORD address = 0x0345;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 6;

	cpu.X = addedZeroPageAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAINDX);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress + addedZeroPageAddress, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region IndirectY
TEST_F(CPUTest, LDAIndirectYBehavesCorrectly) {
	BYTE zeroPageAddress = 0x33;
	WORD address = 0x0345;
	BYTE addedAddress = 0x12;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 5;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAINDY);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAIndirectYCorrectlySetsZeroFlag) {
	BYTE zeroPageAddress = 0x33;
	WORD address = 0x0345;
	BYTE addedAddress = 0x12;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 5;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAINDY);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAIndirectYCorrectlySetsNegativeFlag) {
	BYTE zeroPageAddress = 0x33;
	WORD address = 0x0345;
	BYTE addedAddress = 0x12;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 5;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAINDY);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDAIndirectYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	BYTE zeroPageAddress = 0x33;
	WORD address = 0x0345;
	BYTE addedAddress = 0xF2;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 6;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDAINDY);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion
#pragma endregion

#pragma region LDX
#pragma region Immediate
TEST_F(CPUTest, LDXImmediateBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	memory.set_byte(0xFFFC, CPU::LDXIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, LDXImmediateCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	memory.set_byte(0xFFFC, CPU::LDXIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, LDXImmediateCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x87;

	memory.set_byte(0xFFFC, CPU::LDXIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, LDXZeroPageBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDXZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXZeroPageCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDXZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXZeroPageCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDXZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

#pragma endregion

#pragma region ZeroPageY
TEST_F(CPUTest, LDXZeroPageYBehavesCorrectly) {
	BYTE address = 0x45;
	BYTE value = 0x07;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXZPY);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXZeroPageYCorrectlySetsZeroFlag) {
	BYTE address = 0x45;
	BYTE value = 0x00;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXZPY);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXZeroPageYCorrectlySetsNegativeFlag) {
	BYTE address = 0x45;
	BYTE value = 0x87;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXZPY);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXZeroPageYCorrectlyOverFlows) {
	BYTE address = 0x45;
	BYTE value = 0x07;
	BYTE addedAddress = 0xF0;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXZPY);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, LDXAbsoluteBehavesCorrectly) {
	WORD address = 0x0345;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXAbsoluteCorrectlySetsZeroFlag) {
	WORD address = 0x0345;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXAbsoluteCorrectlySetsNegativeFlag) {
	WORD address = 0x0345;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region AbsoluteY
TEST_F(CPUTest, LDXAbsoluteYBehavesCorrectly) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXABSY);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXAbsoluteYCorrectlySetsZeroFlag) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXABSY);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXAbsoluteYCorrectlySetsNegativeFlag) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 4;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXABSY);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDXAbsoluteYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	WORD address = 0x03F5;
	BYTE addedAddress = 0x14;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 5;

	cpu.Y = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDXABSY);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion
#pragma endregion

#pragma region LDY
#pragma region Immediate
TEST_F(CPUTest, LDYImmediateBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	memory.set_byte(0xFFFC, CPU::LDYIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, LDYImmediateCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	memory.set_byte(0xFFFC, CPU::LDYIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, LDYImmediateCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x87;

	memory.set_byte(0xFFFC, CPU::LDYIM);
	memory.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, LDYZeroPageBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDYZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYZeroPageCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDYZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYZeroPageCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 3;

	memory.set_byte(0xFFFC, CPU::LDYZP);
	memory.set_byte(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, LDYZeroPageXBehavesCorrectly) {
	BYTE address = 0x45;
	BYTE value = 0x07;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYZPX);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYZeroPageXCorrectlySetsZeroFlag) {
	BYTE address = 0x45;
	BYTE value = 0x00;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYZPX);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYZeroPageXCorrectlySetsNegativeFlag) {
	BYTE address = 0x45;
	BYTE value = 0x87;
	BYTE addedAddress = 0x10;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYZPX);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYZeroPageXCorrectlyOverFlows) {
	BYTE address = 0x45;
	BYTE value = 0x07;
	BYTE addedAddress = 0xF0;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYZPX);
	memory.set_byte(0xFFFD, address);
	memory.set_byte((BYTE)(address + addedAddress), value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, LDYAbsoluteBehavesCorrectly) {
	WORD address = 0x0345;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYAbsoluteCorrectlySetsZeroFlag) {
	WORD address = 0x0345;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYAbsoluteCorrectlySetsNegativeFlag) {
	WORD address = 0x0345;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 4;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYABS);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region AbsoluteX
TEST_F(CPUTest, LDYAbsoluteXBehavesCorrectly) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYABSX);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYAbsoluteXCorrectlySetsZeroFlag) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYABSX);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYAbsoluteXCorrectlySetsNegativeFlag) {
	WORD address = 0x0345;
	BYTE addedAddress = 0x14;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 4;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYABSX);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, LDYAbsoluteXCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	WORD address = 0x03F5;
	BYTE addedAddress = 0x14;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 5;

	cpu.X = addedAddress;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::LDYABSX);
	memory.set_word(0xFFFD, address);
	memory.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion
#pragma endregion
#pragma endregion

#pragma region Store
#pragma region STA

#pragma region ZeroPage
TEST_F(CPUTest, STAZeroPageBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;

	uint32_t cyclesNeeded = 3;

	cpu.A = value;

	memory.set_byte(0xFFFC, CPU::STAZP);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, STAZeroPageXBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 4;

	cpu.A = value;
	cpu.X = addedAddress;

	memory.set_byte(0xFFFC, CPU::STAZPX);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address + addedAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, STAZeroPageXCorrectlyOverflows) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x17;
	BYTE addedAddress = 0xF0;

	uint32_t cyclesNeeded = 4;

	cpu.A = value;
	cpu.X = addedAddress;

	memory.set_byte(0xFFFC, CPU::STAZPX);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	BYTE resultingAddress = address + addedAddress;

	EXPECT_EQ(memory.read_byte(resultingAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, STAAbsoluteBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;

	uint32_t cyclesNeeded = 4;

	cpu.A = value;

	memory.set_byte(0xFFFC, CPU::STAABS);
	memory.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region AbsoluteX
TEST_F(CPUTest, STAAbsoluteXBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 5;

	cpu.A = value;
	cpu.X = addedAddress;

	memory.set_byte(0xFFFC, CPU::STAABSX);
	memory.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address + addedAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region AbsoluteY
TEST_F(CPUTest, STAAbsoluteYBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 5;

	cpu.A = value;
	cpu.Y = addedAddress;

	memory.set_byte(0xFFFC, CPU::STAABSY);
	memory.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address + addedAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region IndirectX
TEST_F(CPUTest, STAIndirectXBehavesCorrectly) {
	BYTE zeroPageAddress = 0x33;
	BYTE addedZeroPageAddress = 0x12;
	WORD address = 0x0345;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 6;

	cpu.X = addedZeroPageAddress;
	cpu.A = value;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::STAINDX);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress + addedZeroPageAddress, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region IndirectY
TEST_F(CPUTest, STAIndirectYBehavesCorrectly) {
	BYTE zeroPageAddress = 0x33;
	WORD address = 0x0345;
	BYTE addedAddress = 0x12;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 6;

	cpu.Y = addedAddress;
	cpu.A = value;

	CPU::CPU cpuCopy = cpu;

	memory.set_byte(0xFFFC, CPU::STAINDY);
	memory.set_word(0xFFFD, zeroPageAddress);
	memory.set_word(zeroPageAddress, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address + addedAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma endregion

#pragma region STX

#pragma region ZeroPage
TEST_F(CPUTest, STXZeroPageBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;

	uint32_t cyclesNeeded = 3;

	cpu.X = value;

	memory.set_byte(0xFFFC, CPU::STXZP);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region ZeroPageY
TEST_F(CPUTest, STXZeroPageYBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 4;

	cpu.X = value;
	cpu.Y = addedAddress;

	memory.set_byte(0xFFFC, CPU::STXZPY);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address + addedAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, STXZeroPageYCorrectlyOverflows) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x17;
	BYTE addedAddress = 0xF0;

	uint32_t cyclesNeeded = 4;

	cpu.X = value;
	cpu.Y = addedAddress;

	memory.set_byte(0xFFFC, CPU::STXZPY);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	BYTE resultingAddress = address + addedAddress;

	EXPECT_EQ(memory.read_byte(resultingAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, STXAbsoluteBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;

	uint32_t cyclesNeeded = 4;

	cpu.X = value;

	memory.set_byte(0xFFFC, CPU::STXABS);
	memory.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma endregion

#pragma region STY

#pragma region ZeroPage
TEST_F(CPUTest, STYZeroPageBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;

	uint32_t cyclesNeeded = 3;

	cpu.Y = value;

	memory.set_byte(0xFFFC, CPU::STYZP);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, STYZeroPageXBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 4;

	cpu.Y = value;
	cpu.X = addedAddress;

	memory.set_byte(0xFFFC, CPU::STYZPX);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address + addedAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}

TEST_F(CPUTest, STYZeroPageXCorrectlyOverflows) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x17;
	BYTE addedAddress = 0xF0;

	uint32_t cyclesNeeded = 4;

	cpu.Y = value;
	cpu.X = addedAddress;

	memory.set_byte(0xFFFC, CPU::STYZPX);
	memory.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	BYTE resultingAddress = address + addedAddress;

	EXPECT_EQ(memory.read_byte(resultingAddress), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, STYAbsoluteBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;

	uint32_t cyclesNeeded = 4;

	cpu.Y = value;

	memory.set_byte(0xFFFC, CPU::STYABS);
	memory.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, memory);

	EXPECT_EQ(memory.read_byte(address), value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma endregion
#pragma endregion

#pragma region Transfer
#pragma region TAX
TEST_F(CPUTest, TAXBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	cpu.A = value;

	memory.set_byte(0xFFFC, CPU::TAX);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, TAXCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	cpu.A = value;

	memory.set_byte(0xFFFC, CPU::TAX);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, TAXCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x81;

	cpu.A = value;

	memory.set_byte(0xFFFC, CPU::TAX);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.X, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}
#pragma endregion

#pragma region TXA
TEST_F(CPUTest, TXABehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	cpu.X = value;

	memory.set_byte(0xFFFC, CPU::TXA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, TXACorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	cpu.X = value;

	memory.set_byte(0xFFFC, CPU::TXA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, TXACorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x81;

	cpu.X = value;

	memory.set_byte(0xFFFC, CPU::TXA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}
#pragma endregion

#pragma region TAY
TEST_F(CPUTest, TAYBehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	cpu.A = value;

	memory.set_byte(0xFFFC, CPU::TAY);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, TAYCorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	cpu.A = value;

	memory.set_byte(0xFFFC, CPU::TAY);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, TAYCorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x81;

	cpu.A = value;

	memory.set_byte(0xFFFC, CPU::TAY);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.Y, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}
#pragma endregion

#pragma region TYA
TEST_F(CPUTest, TYABehavesCorrectly) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	cpu.Y = value;

	memory.set_byte(0xFFFC, CPU::TYA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, TYACorrectlySetsZeroFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	cpu.Y = value;

	memory.set_byte(0xFFFC, CPU::TYA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}

TEST_F(CPUTest, TYACorrectlySetsNegativeFlag) {
	CPU::CPU cpuCopy = cpu;

	BYTE value = 0x81;

	cpu.Y = value;

	memory.set_byte(0xFFFC, CPU::TYA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, memory);

	EXPECT_EQ(cpu.A, value);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, 2);
}
#pragma endregion
#pragma endregion
