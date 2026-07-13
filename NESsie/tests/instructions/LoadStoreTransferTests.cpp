#include <iostream>

#include <tests/TestCpu.h>



#pragma region Load
#pragma region LDA
#pragma region Immediate

TEST_F(CPUTest, LDAImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	mainbus.set_byte(0xFFFC, NESsie::LDAIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	mainbus.set_byte(0xFFFC, NESsie::LDAIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x83;

	mainbus.set_byte(0xFFFC, NESsie::LDAIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDAZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDAZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDAZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAZPX);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAZPX);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAZPX);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAZPX);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress + addedZeroPageAddress, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress + addedZeroPageAddress, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress + addedZeroPageAddress, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	mainbus.set_byte(0xFFFC, NESsie::LDXIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	mainbus.set_byte(0xFFFC, NESsie::LDXIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x87;

	mainbus.set_byte(0xFFFC, NESsie::LDXIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDXZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDXZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDXZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXZPY);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXZPY);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXZPY);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXZPY);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDXABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	mainbus.set_byte(0xFFFC, NESsie::LDYIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	mainbus.set_byte(0xFFFC, NESsie::LDYIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x87;

	mainbus.set_byte(0xFFFC, NESsie::LDYIM);
	mainbus.set_byte(0xFFFD, value);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x07;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDYZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x00;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDYZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE address = 0x45;
	BYTE value = 0x87;
	uint32_t cyclesNeeded = 3;

	mainbus.set_byte(0xFFFC, NESsie::LDYZP);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYZPX);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYZPX);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);


	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYZPX);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYZPX);
	mainbus.set_byte(0xFFFD, address);
	mainbus.set_byte((BYTE)(address + addedAddress), value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::LDYABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, value);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;

	uint32_t cyclesNeeded = 3;

	cpu.A = value;

	mainbus.set_byte(0xFFFC, NESsie::STAZP);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 4;

	cpu.A = value;
	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::STAZPX);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + addedAddress), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x17;
	BYTE addedAddress = 0xF0;

	uint32_t cyclesNeeded = 4;

	cpu.A = value;
	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::STAZPX);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	BYTE resultingAddress = address + addedAddress;

	EXPECT_EQ(mainbus.read_byte(resultingAddress), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;

	uint32_t cyclesNeeded = 4;

	cpu.A = value;

	mainbus.set_byte(0xFFFC, NESsie::STAABS);
	mainbus.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 5;

	cpu.A = value;
	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::STAABSX);
	mainbus.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + addedAddress), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 5;

	cpu.A = value;
	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::STAABSY);
	mainbus.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + addedAddress), value);
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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::STAINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress + addedZeroPageAddress, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), value);
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

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::STAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + addedAddress), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;

	uint32_t cyclesNeeded = 3;

	cpu.X = value;

	mainbus.set_byte(0xFFFC, NESsie::STXZP);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 4;

	cpu.X = value;
	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::STXZPY);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + addedAddress), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x17;
	BYTE addedAddress = 0xF0;

	uint32_t cyclesNeeded = 4;

	cpu.X = value;
	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::STXZPY);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	BYTE resultingAddress = address + addedAddress;

	EXPECT_EQ(mainbus.read_byte(resultingAddress), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;

	uint32_t cyclesNeeded = 4;

	cpu.X = value;

	mainbus.set_byte(0xFFFC, NESsie::STXABS);
	mainbus.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;

	uint32_t cyclesNeeded = 3;

	cpu.Y = value;

	mainbus.set_byte(0xFFFC, NESsie::STYZP);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x07;
	BYTE addedAddress = 0x10;

	uint32_t cyclesNeeded = 4;

	cpu.Y = value;
	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::STYZPX);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + addedAddress), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	BYTE address = 0x17;
	BYTE addedAddress = 0xF0;

	uint32_t cyclesNeeded = 4;

	cpu.Y = value;
	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::STYZPX);
	mainbus.set_byte(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	BYTE resultingAddress = address + addedAddress;

	EXPECT_EQ(mainbus.read_byte(resultingAddress), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;
	WORD address = 0x0345;

	uint32_t cyclesNeeded = 4;

	cpu.Y = value;

	mainbus.set_byte(0xFFFC, NESsie::STYABS);
	mainbus.set_word(0xFFFD, address);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), value);
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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	cpu.A = value;

	mainbus.set_byte(0xFFFC, NESsie::TAX);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	cpu.A = value;

	mainbus.set_byte(0xFFFC, NESsie::TAX);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x81;

	cpu.A = value;

	mainbus.set_byte(0xFFFC, NESsie::TAX);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	cpu.X = value;

	mainbus.set_byte(0xFFFC, NESsie::TXA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	cpu.X = value;

	mainbus.set_byte(0xFFFC, NESsie::TXA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x81;

	cpu.X = value;

	mainbus.set_byte(0xFFFC, NESsie::TXA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	cpu.A = value;

	mainbus.set_byte(0xFFFC, NESsie::TAY);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	cpu.A = value;

	mainbus.set_byte(0xFFFC, NESsie::TAY);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x81;

	cpu.A = value;

	mainbus.set_byte(0xFFFC, NESsie::TAY);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x11;

	cpu.Y = value;

	mainbus.set_byte(0xFFFC, NESsie::TYA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x00;

	cpu.Y = value;

	mainbus.set_byte(0xFFFC, NESsie::TYA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
	NESsie::CPU cpuCopy = cpu;

	BYTE value = 0x81;

	cpu.Y = value;

	mainbus.set_byte(0xFFFC, NESsie::TYA);

	uint32_t cyclesExecuted = cpu.executeCycles(2, mainbus);

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
