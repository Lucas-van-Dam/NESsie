#include <tests/TestCpu.h>

#pragma region ADC
#pragma region Immediate
TEST_F(CPUTest, ADCImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCIM);
	mainbus.set_byte(0xFFFD, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCImmediateCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0xFF;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCIM);
	mainbus.set_byte(0xFFFD, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCImmediateCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x00;
	BYTE Addedvalue = 0x00;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCIM);
	mainbus.set_byte(0xFFFD, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCImmediateCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x70;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCIM);
	mainbus.set_byte(0xFFFD, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ADCImmediateCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x80;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCIM);
	mainbus.set_byte(0xFFFD, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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
TEST_F(CPUTest, ADCZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	BYTE zeroPageAddress = 0x47;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCZeroPageCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0xFF;

	BYTE zeroPageAddress = 0x47;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x00;
	BYTE Addedvalue = 0x00;

	BYTE zeroPageAddress = 0x47;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCZeroPageCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x70;

	BYTE zeroPageAddress = 0x47;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ADCZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x80;

	BYTE zeroPageAddress = 0x47;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

#pragma region ZeroPageX
TEST_F(CPUTest, ADCZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;
	
	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCZeroPageXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0xFF;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x00;
	BYTE Addedvalue = 0x00;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCZeroPageXCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x70;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ADCZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x80;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

#pragma region Absolute
TEST_F(CPUTest, ADCAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0xFF;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x00;
	BYTE Addedvalue = 0x00;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x70;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ADCAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x80;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

#pragma region AbsoluteX
TEST_F(CPUTest, ADCAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0xFF;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x00;
	BYTE Addedvalue = 0x00;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteXCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x70;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ADCAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x80;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteXCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x40;

	WORD address = 0x0345;
	BYTE addedAddress = 0xF0;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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
#pragma endregion

#pragma region AbsoluteY
TEST_F(CPUTest, ADCAbsoluteYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteYCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0xFF;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x00;
	BYTE Addedvalue = 0x00;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteYCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x70;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ADCAbsoluteYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x80;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCAbsoluteYCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x40;

	WORD address = 0x0345;
	BYTE addedAddress = 0xF0;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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
#pragma endregion

#pragma region IndirectX
TEST_F(CPUTest, ADCIndirectXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCIndirectXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0xFF;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCIndirectXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x00;
	BYTE Addedvalue = 0x00;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCIndirectXCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x70;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ADCIndirectXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x80;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

#pragma region IndirectY
TEST_F(CPUTest, ADCIndirectYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCIndirectYCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0xFF;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCIndirectYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x00;
	BYTE Addedvalue = 0x00;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCIndirectYCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x70;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, ADCIndirectYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x20;
	BYTE Addedvalue = 0x80;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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

TEST_F(CPUTest, ADCIndirectYCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x07;
	BYTE Addedvalue = 0x46;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0xF7;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::ADCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, Addedvalue);

	BYTE result = accumulatorValue + Addedvalue;

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
#pragma endregion
#pragma endregion

#pragma region SBC
#pragma region Immediate
TEST_F(CPUTest, SBCImmediateBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCImmediateCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0xFF;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCImmediateCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x00;
	BYTE SubtractedValue = 0x00;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCImmediateCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0x80;
	BYTE SubtractedValue = 0x70;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCImmediateCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE accumulatorValue = 0xF0;
	BYTE SubtractedValue = 0x20;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCIM);
	mainbus.set_byte(0xFFFD, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
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
TEST_F(CPUTest, SBCZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	BYTE zeroPageAddress = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::SBCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCZeroPageCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0xFF;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x00;
	BYTE SubtractedValue = 0x00;

	BYTE zeroPageAddress = 0x47;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCZeroPageCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0x80;
	BYTE SubtractedValue = 0x70;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	BYTE accumulatorValue = 0xF0;
	BYTE SubtractedValue = 0x20;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
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
TEST_F(CPUTest, SBCZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCZeroPageXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0xFF;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x00;
	BYTE SubtractedValue = 0x00;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.PS.C = 1;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCZeroPageXCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x80;
	BYTE SubtractedValue = 0x70;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0xF0;
	BYTE SubtractedValue = 0x20;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
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
TEST_F(CPUTest, SBCAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	WORD address = 0x0345;

	mainbus.set_byte(0xFFFC, NESsie::SBCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCAbsoluteCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0xFF;

	cpu.PS.C = 1;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x00;
	BYTE SubtractedValue = 0x00;

	WORD address = 0x0345;

	cpu.PS.C = 1;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCAbsoluteCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x80;
	BYTE SubtractedValue = 0x70;

	cpu.PS.C = 1;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0xF0;
	BYTE SubtractedValue = 0x20;

	cpu.PS.C = 1;

	WORD address = 0x0345;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
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
TEST_F(CPUTest, SBCAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCAbsoluteXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0xFF;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x00;
	BYTE SubtractedValue = 0x00;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.PS.C = 1;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCAbsoluteXCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x80;
	BYTE SubtractedValue = 0x70;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0xF0;
	BYTE SubtractedValue = 0x20;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCAbsoluteXCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0xF0;

	cpu.X = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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
#pragma endregion

#pragma region AbsoluteY
TEST_F(CPUTest, SBCAbsoluteYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCAbsoluteYCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0xFF;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCAbsoluteYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x00;
	BYTE SubtractedValue = 0x00;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.PS.C = 1;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCAbsoluteYCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0x80;
	BYTE SubtractedValue = 0x70;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCAbsoluteYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 4;

	BYTE accumulatorValue = 0xF0;
	BYTE SubtractedValue = 0x20;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCAbsoluteYCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	WORD address = 0x0345;
	BYTE addedAddress = 0xF0;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCABSY);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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
#pragma endregion

#pragma region IndirectX
TEST_F(CPUTest, SBCIndirectXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCIndirectXCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0xFF;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCIndirectXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x00;
	BYTE SubtractedValue = 0x00;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.PS.C = 1;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCIndirectXCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x80;
	BYTE SubtractedValue = 0x70;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCIndirectXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0xF0;
	BYTE SubtractedValue = 0x20;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	WORD address = 0x0345;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(totalAddress, address);
	mainbus.set_byte(address, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
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

#pragma region IndirectY
TEST_F(CPUTest, SBCIndirectYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCIndirectYCorrectlySetsCarryFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x07;
	BYTE SubtractedValue = 0xFF;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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

TEST_F(CPUTest, SBCIndirectYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x00;
	BYTE SubtractedValue = 0x00;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.PS.C = 1;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCIndirectYCorrectlySetsOverflowFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0x80;
	BYTE SubtractedValue = 0x70;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCIndirectYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE accumulatorValue = 0xF0;
	BYTE SubtractedValue = 0x20;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0x27;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.A, result);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}

TEST_F(CPUTest, SBCIndirectYCorrectlyUsesExtraCycleOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE accumulatorValue = 0x46;
	BYTE SubtractedValue = 0x07;

	cpu.PS.C = 1;

	BYTE zeroPageAddress = 0x47;

	WORD address = 0x0345;
	BYTE addedAddress = 0xF7;

	cpu.Y = addedAddress;

	cpu.A = accumulatorValue;

	mainbus.set_byte(0xFFFC, NESsie::SBCINDY);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_word(zeroPageAddress, address);
	mainbus.set_byte(address + addedAddress, SubtractedValue);

	BYTE result = accumulatorValue - SubtractedValue;

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
#pragma endregion
#pragma endregion

#pragma region INC
#pragma region ZeroPage
TEST_F(CPUTest, INCZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE zeroPageAddress = 0x47;

	BYTE startValue = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::INCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	mainbus.read_byte(zeroPageAddress);

	BYTE result = startValue + 1;

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

TEST_F(CPUTest, INCZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0xFF;

	BYTE zeroPageAddress = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::INCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	mainbus.read_byte(zeroPageAddress);

	BYTE result = startValue + 1;

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

TEST_F(CPUTest, INCZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0x7F;

	BYTE zeroPageAddress = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::INCZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	mainbus.read_byte(zeroPageAddress);

	BYTE result = startValue + 1;

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
TEST_F(CPUTest, INCZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x07;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::INCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue + 1;

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

TEST_F(CPUTest, INCZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0xFF;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	cpu.X = addedZeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::INCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue + 1;

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

TEST_F(CPUTest, INCZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x7F;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::INCZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue + 1;

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

#pragma region Absolute
TEST_F(CPUTest, INCAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x07;

	WORD address = 0x0345;

	mainbus.set_byte(0xFFFC, NESsie::INCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue + 1;

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

TEST_F(CPUTest, INCAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0xFF;

	WORD address = 0x0345;

	mainbus.set_byte(0xFFFC, NESsie::INCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue + 1;

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

TEST_F(CPUTest, INCAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x7F;

	WORD address = 0x0345;

	mainbus.set_byte(0xFFFC, NESsie::INCABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue + 1;

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
TEST_F(CPUTest, INCAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0x07;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::INCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + cpu.X, startValue);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + cpu.X), result);
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

TEST_F(CPUTest, INCAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0xFF;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::INCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + cpu.X, startValue);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + cpu.X), result);
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

TEST_F(CPUTest, INCAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0x7F;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::INCABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + cpu.X, startValue);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + cpu.X), result);
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

#pragma region DEC
#pragma region ZeroPage
TEST_F(CPUTest, DECZeroPageBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE zeroPageAddress = 0x47;

	BYTE startValue = 0x07;

	mainbus.set_byte(0xFFFC, NESsie::DECZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	mainbus.read_byte(zeroPageAddress);

	BYTE result = startValue - 1;

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

TEST_F(CPUTest, DECZeroPageCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0x01;

	BYTE zeroPageAddress = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::DECZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	mainbus.read_byte(zeroPageAddress);

	BYTE result = startValue - 1;

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

TEST_F(CPUTest, DECZeroPageCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	BYTE startValue = 0x87;

	BYTE zeroPageAddress = 0x47;

	mainbus.set_byte(0xFFFC, NESsie::DECZP);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(zeroPageAddress, startValue);

	mainbus.read_byte(zeroPageAddress);

	BYTE result = startValue - 1;

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
TEST_F(CPUTest, DECZeroPageXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x07;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::DECZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue - 1;

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

TEST_F(CPUTest, DECZeroPageXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x01;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	cpu.X = addedZeroPageAddress;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::DECZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue - 1;

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

TEST_F(CPUTest, DECZeroPageXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x87;

	BYTE zeroPageAddress = 0x47;
	BYTE addedZeroPageAddress = 0x27;

	BYTE totalAddress = zeroPageAddress + addedZeroPageAddress;

	cpu.X = addedZeroPageAddress;

	mainbus.set_byte(0xFFFC, NESsie::DECZPX);
	mainbus.set_byte(0xFFFD, zeroPageAddress);
	mainbus.set_byte(totalAddress, startValue);

	BYTE result = startValue - 1;

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

#pragma region Absolute
TEST_F(CPUTest, DECAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x07;

	WORD address = 0x0345;

	mainbus.set_byte(0xFFFC, NESsie::DECABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue - 1;

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

TEST_F(CPUTest, DECAbsoluteCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x01;

	WORD address = 0x0345;

	mainbus.set_byte(0xFFFC, NESsie::DECABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue - 1;

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

TEST_F(CPUTest, DECAbsoluteCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	BYTE startValue = 0x87;

	WORD address = 0x0345;

	mainbus.set_byte(0xFFFC, NESsie::DECABS);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address, startValue);

	BYTE result = startValue - 1;

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
TEST_F(CPUTest, DECAbsoluteXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0x07;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::DECABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + cpu.X, startValue);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + cpu.X), result);
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

TEST_F(CPUTest, DECAbsoluteXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0x01;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::DECABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + cpu.X, startValue);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + cpu.X), result);
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

TEST_F(CPUTest, DECAbsoluteXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 7;

	BYTE startValue = 0x87;

	WORD address = 0x0345;
	BYTE addedAddress = 0x30;

	cpu.X = addedAddress;

	mainbus.set_byte(0xFFFC, NESsie::DECABSX);
	mainbus.set_word(0xFFFD, address);
	mainbus.set_byte(address + cpu.X, startValue);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(mainbus.read_byte(address + cpu.X), result);
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

#pragma region INX
TEST_F(CPUTest, INXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x07;

	cpu.X = startValue;

	mainbus.set_byte(0xFFFC, NESsie::INX);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.X, result);
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

TEST_F(CPUTest, INXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0xFF;

	cpu.X = startValue;

	mainbus.set_byte(0xFFFC, NESsie::INX);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.X, result);
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

TEST_F(CPUTest, INXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x7F;

	cpu.X = startValue;

	mainbus.set_byte(0xFFFC, NESsie::INX);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.X, result);
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

#pragma region DEX
TEST_F(CPUTest, DEXBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x07;

	cpu.X = startValue;

	mainbus.set_byte(0xFFFC, NESsie::DEX);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.X, result);
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

TEST_F(CPUTest, DEXCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x01;

	cpu.X = startValue;

	mainbus.set_byte(0xFFFC, NESsie::DEX);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.X, result);
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

TEST_F(CPUTest, DEXCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x87;

	cpu.X = startValue;

	mainbus.set_byte(0xFFFC, NESsie::DEX);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.X, result);
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

#pragma region INY
TEST_F(CPUTest, INYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x07;

	cpu.Y = startValue;

	mainbus.set_byte(0xFFFC, NESsie::INY);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.Y, result);
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

TEST_F(CPUTest, INYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0xFF;

	cpu.Y = startValue;

	mainbus.set_byte(0xFFFC, NESsie::INY);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.Y, result);
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

TEST_F(CPUTest, INYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x7F;

	cpu.Y = startValue;

	mainbus.set_byte(0xFFFC, NESsie::INY);

	BYTE result = startValue + 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.Y, result);
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

#pragma region DEY
TEST_F(CPUTest, DEYBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x07;

	cpu.Y = startValue;

	mainbus.set_byte(0xFFFC, NESsie::DEY);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.Y, result);
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

TEST_F(CPUTest, DEYCorrectlySetsZeroFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x01;

	cpu.Y = startValue;

	mainbus.set_byte(0xFFFC, NESsie::DEY);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.Y, result);
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

TEST_F(CPUTest, DEYCorrectlySetsNegativeFlag) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	BYTE startValue = 0x87;

	cpu.Y = startValue;

	mainbus.set_byte(0xFFFC, NESsie::DEY);

	BYTE result = startValue - 1;

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.Y, result);
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