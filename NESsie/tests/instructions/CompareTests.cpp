#include <tests/TestCpu.h>

#pragma region CMP
#pragma region Immediate
TEST_F(CPUTest, CMPImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPImmediateCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPImmediateCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, CMPZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	BYTE zeroPageValue = 0x14;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, CMPZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	BYTE resultingAddress = zeroPageValue + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPZPX);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(resultingAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	BYTE resultingAddress = zeroPageValue + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPZPX);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(resultingAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	BYTE resultingAddress = zeroPageValue + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPZPX);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(resultingAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, CMPAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CMPABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region AbsoluteX
TEST_F(CPUTest, CMPAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	WORD address = 0x0345;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;
	BYTE addedAddress = 0x16;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPAbsoluteXCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;
	BYTE addedAddress = 0xF6;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
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
TEST_F(CPUTest, CMPAbsoluteYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	WORD address = 0x0345;
	BYTE addedAddress = 0x16;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPAbsoluteYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;
	BYTE addedAddress = 0x16;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPAbsoluteYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;
	BYTE addedAddress = 0x16;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPAbsoluteYCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;
	BYTE addedAddress = 0xF6;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
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
TEST_F(CPUTest, CMPIndirectXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	WORD address = 0x0345;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	BYTE resultingAddress = zeroPageValue + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPINDX);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_word(resultingAddress, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPIndirectXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	WORD address = 0x0345;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	BYTE resultingAddress = zeroPageValue + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPINDX);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_word(resultingAddress, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPIndirectXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	WORD address = 0x0345;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	BYTE resultingAddress = zeroPageValue + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPINDX);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_word(resultingAddress, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region IndirectY
TEST_F(CPUTest, CMPIndirectYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	WORD address = 0x0345;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	WORD resultingAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPINDY);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_word(zeroPageValue, address);
	mainbus.set_byte(resultingAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPIndirectYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	WORD address = 0x0345;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	WORD resultingAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPINDY);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_word(zeroPageValue, address);
	mainbus.set_byte(resultingAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPIndirectYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0x43;

	WORD address = 0x0345;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	WORD resultingAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPINDY);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_word(zeroPageValue, address);
	mainbus.set_byte(resultingAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CMPIndirectYCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;
	BYTE addedAddress = 0xF3;

	WORD address = 0x0345;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	WORD resultingAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::CMPINDY);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_word(zeroPageValue, address);
	mainbus.set_byte(resultingAddress, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
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

#pragma region CPX
#pragma region Immediate
TEST_F(CPUTest, CPXImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPXImmediateCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPXImmediateCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, CPXZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	BYTE zeroPageValue = 0x14;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPXZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPXZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, CPXAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	WORD address = 0x0345;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPXAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPXAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;

	cpu.X = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPXABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
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

#pragma region CPY
#pragma region Immediate
TEST_F(CPUTest, CPYImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPYImmediateCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPYImmediateCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, CPYZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	BYTE zeroPageValue = 0x14;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPYZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPYZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	BYTE zeroPageValue = 0x14;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYZP);
	mainbus.set_byte(0xFFFD, zeroPageValue);
	mainbus.set_byte(zeroPageValue, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, CPYAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	WORD address = 0x0345;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPYAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, CPYAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x10;
	BYTE SubtractedValue = 0x10;

	WORD address = 0x0345;

	cpu.Y = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::CPYABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
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
