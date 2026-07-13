#include <tests/TestCpu.h>

#pragma region AND
#pragma region Immediate
TEST_F(CPUTest, ANDImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDIM);
	mainbus.set_byte(0xFFFD, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDIM);
	mainbus.set_byte(0xFFFD, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDIM);
	mainbus.set_byte(0xFFFD, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01011101;

	BYTE zeroPageAddress = 0x07;

	BYTE ANDvalue = 0b10110101;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

#pragma region Absolute
TEST_F(CPUTest, ANDAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ANDABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

#pragma region AbsoluteX
TEST_F(CPUTest, ANDAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ANDABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ANDABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ANDABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDAbsoluteXCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0xF7;

	mainbus.set_byte(0xFFFC, NESsie::ANDABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

#pragma region AbsoluteY
TEST_F(CPUTest, ANDAbsoluteYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ANDABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDAbsoluteYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ANDABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDAbsoluteYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ANDABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDAbsoluteYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0xF7;

	mainbus.set_byte(0xFFFC, NESsie::ANDABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

#pragma region IndirectX
TEST_F(CPUTest, ANDIndirectXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::ANDINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDIndirectXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::ANDINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDIndirectXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::ANDINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

#pragma region IndirectY
TEST_F(CPUTest, ANDIndirectYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ANDINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDIndirectYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b01010101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ANDINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDIndirectYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b11011101;
	BYTE ANDvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ANDINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, ANDIndirectYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b01011101;
	BYTE ANDvalue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0xF0;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ANDINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, ANDvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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
#pragma endregion
#pragma endregion

#pragma region ORA
#pragma region Immediate
TEST_F(CPUTest, ORAImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00110101;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAIM);
	mainbus.set_byte(0xFFFD, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAImmediateCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b00000000;
	BYTE ORAvalue = 0b00000000;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAIM);
	mainbus.set_byte(0xFFFD, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAImmediateCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b10101010;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAIM);
	mainbus.set_byte(0xFFFD, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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
TEST_F(CPUTest, ORAZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01011101;

	BYTE zeroPageAddress = 0x07;

	BYTE ORAvalue = 0b00110101;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b00000000;
	BYTE ORAvalue = 0b00000000;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b11011101;
	BYTE ORAvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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
TEST_F(CPUTest, ORAZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b00000000;
	BYTE ORAvalue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ORAvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

#pragma region Absolute
TEST_F(CPUTest, ORAAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b00000000;
	BYTE ORAvalue = 0b00000000;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ORAvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ORAABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

#pragma region AbsoluteX
TEST_F(CPUTest, ORAAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ORAABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b00000000;
	BYTE ORAvalue = 0b00000000;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ORAABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ORAvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ORAABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAAbsoluteXCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0xF7;

	mainbus.set_byte(0xFFFC, NESsie::ORAABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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
#pragma endregion

#pragma region AbsoluteY
TEST_F(CPUTest, ORAAbsoluteYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ORAABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAAbsoluteYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b00000000;
	BYTE ORAvalue = 0b00000000;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ORAABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAAbsoluteYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE ORAvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::ORAABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAAbsoluteYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b11011101;
	BYTE ORAvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0xF7;

	mainbus.set_byte(0xFFFC, NESsie::ORAABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

#pragma region IndirectX
TEST_F(CPUTest, ORAIndirectXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::ORAINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAIndirectXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b00000000;
	BYTE ORAvalue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::ORAINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAIndirectXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b11011101;
	BYTE ORAvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::ORAINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

#pragma region IndirectY
TEST_F(CPUTest, ORAIndirectYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ORAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAIndirectYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b00000000;
	BYTE ORAvalue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ORAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAIndirectYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b11011101;
	BYTE ORAvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ORAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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

TEST_F(CPUTest, ORAIndirectYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b01011101;
	BYTE ORAvalue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0xF0;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ORAINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, ORAvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue | ORAvalue);
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
#pragma endregion
#pragma endregion

#pragma region EOR
#pragma region Immediate
TEST_F(CPUTest, EORImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00110101;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORIM);
	mainbus.set_byte(0xFFFD, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORImmediateCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b00000000;
	BYTE EORvalue = 0b00000000;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORIM);
	mainbus.set_byte(0xFFFD, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORImmediateCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b10101010;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORIM);
	mainbus.set_byte(0xFFFD, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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
TEST_F(CPUTest, EORZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01011101;

	BYTE zeroPageAddress = 0x07;

	BYTE EORvalue = 0b00110101;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b00000000;
	BYTE EORvalue = 0b00000000;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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
TEST_F(CPUTest, EORZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b00000000;
	BYTE EORvalue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress + addedAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

#pragma region Absolute
TEST_F(CPUTest, EORAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b00000000;
	BYTE EORvalue = 0b00000000;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::EORABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

#pragma region AbsoluteX
TEST_F(CPUTest, EORAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::EORABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b00000000;
	BYTE EORvalue = 0b00000000;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::EORABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::EORABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORAbsoluteXCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = 0xF7;

	mainbus.set_byte(0xFFFC, NESsie::EORABSX);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.X, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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
#pragma endregion

#pragma region AbsoluteY
TEST_F(CPUTest, EORAbsoluteYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::EORABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORAbsoluteYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b00000000;
	BYTE EORvalue = 0b00000000;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::EORABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORAbsoluteYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::EORABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORAbsoluteYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b11011101;
	BYTE EORvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = 0xF7;

	mainbus.set_byte(0xFFFC, NESsie::EORABSY);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address + cpu.Y, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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
#pragma endregion

#pragma region IndirectX
TEST_F(CPUTest, EORIndirectXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::EORINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORIndirectXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b00000000;
	BYTE EORvalue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::EORINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORIndirectXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedzeroPageAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.X = addedzeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedzeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::EORINDX);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);

	mainbus.set_byte(address, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

#pragma region IndirectY
TEST_F(CPUTest, EORIndirectYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::EORINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORIndirectYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b00000000;
	BYTE EORvalue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::EORINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORIndirectYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x40;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::EORINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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

TEST_F(CPUTest, EORIndirectYCorrectlyUsesExtraCycleAtPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0b01011101;
	BYTE EORvalue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0xF0;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	cpu.Y = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::EORINDY);
	mainbus.set_word(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);

	mainbus.set_byte(address + addedAddress, EORvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, accumulatorValue ^ EORvalue);
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
#pragma endregion
#pragma endregion

#pragma region BIT
#pragma region ZeroPage
TEST_F(CPUTest, BITZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01011101;

	BYTE zeroPageAddress = 0x07;

	BYTE BITvalue = 0b10110101;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::BITZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, BITvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, BITZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b01010101;
	BYTE BITvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::BITZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, BITvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, BITZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0b11011101;
	BYTE BITvalue = 0b10101010;

	BYTE zeroPageAddress = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::BITZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);

	mainbus.set_byte(zeroPageAddress, BITvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

#pragma region Absolute
TEST_F(CPUTest, BITAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01011101;
	BYTE BITvalue = 0b10110101;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::BITABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, BITvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, BITAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b01010101;
	BYTE BITvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::BITABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, BITvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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

TEST_F(CPUTest, BITAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0b11011101;
	BYTE BITvalue = 0b10101010;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::BITABS);
	mainbus.set_word(0xFFFD, address);

	mainbus.set_byte(address, BITvalue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

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