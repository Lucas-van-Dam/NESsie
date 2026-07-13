#include <tests/TestCpu.h>

#pragma region ASL
#pragma region Accumulator
TEST_F(CPUTest, ASLAccumulatorBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b00110101;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ASLAC);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAccumulatorCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b10110101;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ASLAC);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAccumulatorCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b00000000;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ASLAC);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAccumulatorCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b01010101;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ASLAC);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, ASLZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b00110101;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ASLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLZeroPageCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b10110101;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ASLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b00000000;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ASLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b01010101;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ASLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, ASLZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ASLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLZeroPageXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ASLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ASLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b01010101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ASLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, ASLAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00110101;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ASLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAbsoluteCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b10110101;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ASLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00000000;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ASLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b01010101;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ASLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region AbsoluteX
TEST_F(CPUTest, ASLAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b00110101;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ASLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAbsoluteXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b10110101;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ASLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b00000000;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ASLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ASLAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b01010101;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ASLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion
#pragma endregion

#pragma region LSR
#pragma region Accumulator
TEST_F(CPUTest, LSRAccumulatorBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b00110100;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::LSRAC);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRAccumulatorCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b10110101;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::LSRAC);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRAccumulatorCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b00000000;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::LSRAC);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, LSRZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b00110100;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::LSRZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRZeroPageCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b10110101;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::LSRZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b00000000;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::LSRZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, LSRZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00110100;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::LSRZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRZeroPageXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::LSRZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::LSRZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, LSRAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00110100;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::LSRABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRAbsoluteCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b10110101;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::LSRABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00000000;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::LSRABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region AbsoluteX
TEST_F(CPUTest, LSRAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b00110100;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::LSRABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRAbsoluteXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b10110101;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::LSRABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, LSRAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b00000000;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::LSRABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion
#pragma endregion

#pragma region ROL
#pragma region Accumulator
TEST_F(CPUTest, ROLAccumulatorBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b00110101;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ROLAC);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAccumulatorCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b10110101;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ROLAC);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAccumulatorCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b00000000;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ROLAC);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAccumulatorCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b01010101;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ROLAC);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAccumulatorCorrectlyRollsInCarry) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.C = 1;

	BYTE startValue = 0b01010100;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::ROLAC);

	BYTE result = startValue << 1;
	result |= 0x01;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, ROLZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b00110101;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLZeroPageCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b10110101;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b00000000;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b01010101;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLZeroPageCorrectlyRollsInCarry) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	cpu.PS.C = 1;

	BYTE startValue = 0b01010100;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue << 1;
	result |= 0x01;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, ROLZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLZeroPageXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b01010101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLZeroPageXCorrectlyRollsInCarry) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	cpu.PS.C = 1;

	BYTE startValue = 0b01010100;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue << 1;
	result |= 0x01;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, ROLAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00110101;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAbsoluteCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b10110101;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00000000;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b01010101;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAbsoluteCorrectlyRollsInCarry) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b01010100;

	cpu.PS.C = 1;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::ROLABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue << 1;
	result |= 0x01;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region AbsoluteX
TEST_F(CPUTest, ROLAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b00110101;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAbsoluteXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b10110101;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b00000000;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b01010101;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ROLAbsoluteXCorrectlyRollsInCarry) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b01010100;

	cpu.PS.C = 1;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::ROLABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue << 1;
	result |= 0x01;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion
#pragma endregion

#pragma region ROR
#pragma region Accumulator
TEST_F(CPUTest, RORAccumulatorBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b01110100;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::RORAC);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAccumulatorCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b10110101;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::RORAC);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAccumulatorCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b00000000;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::RORAC);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAccumulatorCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0b01010100;

	cpu.PS.C = 1;

	cpu.A = startValue;

	mainbus.set_byte(0xFFFC, NESsie::RORAC);

	BYTE result = startValue >> 1;
	result |= 0x80;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPage
TEST_F(CPUTest, RORZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b01110100;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::RORZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORZeroPageCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b10110101;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::RORZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b00000000;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::RORZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0b01010100;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::RORZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	BYTE result = startValue >> 1;
	result |= 1 << 7;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region ZeroPageX
TEST_F(CPUTest, RORZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00110100;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::RORZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORZeroPageXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b10110101;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::RORZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00000000;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::RORZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b01010100;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::RORZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress + addedAddress, startValue);

	BYTE result = startValue >> 1;
	result |= 1 << 7;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(zeroPageAddress + addedAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region Absolute
TEST_F(CPUTest, RORAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00110100;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::RORABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAbsoluteCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b10110101;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::RORABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b00000000;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::RORABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0b01010100;

	cpu.PS.C = 1;

	WORD address = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::RORABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue >> 1;
	result |= 1 << 7;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region AbsoluteX
TEST_F(CPUTest, RORAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b00110100;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::RORABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAbsoluteXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b10110101;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::RORABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b00000000;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::RORABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue >> 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, RORAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0b01010100;

	cpu.PS.C = 1;

	WORD address = 0x07;
	BYTE addedAddress = 0x14;

	cpu.X = addedAddress;

	WORD totalAddress = address + addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::RORABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue >> 1;
	result |= 1 << 7;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(totalAddress), result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion
#pragma endregion