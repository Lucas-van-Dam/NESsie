#include <tests/TestCpu.h>

#pragma region JMP
#pragma region Absolute
TEST_F(CPUTest, JMPAbsoluteBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	WORD newProgramCounter = 0xF7F7;

	mainbus.set_byte(0xFFFC, NESsie::JMPABS);
	mainbus.set_word(0xFFFD, newProgramCounter);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, newProgramCounter);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region Indirect
TEST_F(CPUTest, JMPIndirectBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	WORD indirectPointer = 0x1357;
	WORD newProgramCounter = 0xF7F7;

	mainbus.set_byte(0xFFFC, NESsie::JMPIND);
	mainbus.set_word(0xFFFD, indirectPointer);

	mainbus.set_word(indirectPointer, newProgramCounter);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, newProgramCounter);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, JMPIndirectCorrectlyPerformsHardwareBugOnPageBoundaryCrossing) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 5;

	WORD indirectPointer = 0x13FF;
	WORD newProgramCounter = 0xF7F7;

	mainbus.set_byte(0xFFFC, NESsie::JMPIND);
	mainbus.set_word(0xFFFD, indirectPointer);

	mainbus.set_byte(indirectPointer, newProgramCounter);
	mainbus.set_word(0x12FF, newProgramCounter);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, newProgramCounter);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion
#pragma endregion

#pragma region JSR
TEST_F(CPUTest, JSRBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	WORD newProgramCounter = 0xF7F7;

	mainbus.set_byte(0xFFFC, NESsie::JSR);
	mainbus.set_word(0xFFFD, newProgramCounter);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, newProgramCounter);
	EXPECT_EQ(cpu.fetch_byte_from_stack(mainbus), 0xFE);
	EXPECT_EQ(cpu.fetch_byte_from_stack(mainbus), 0xFF);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region RTS
TEST_F(CPUTest, RTSBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 6;

	mainbus.set_byte(0xFFFC, NESsie::JSR);
	mainbus.set_word(0xFFFD, 0xF7F7);

	cpu.executeCycles(6, mainbus);

	cpu.PC = 0xFFFC;

	mainbus.set_byte(0xFFFC, NESsie::RTS);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, 0xFFFF);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region BRK
TEST_F(CPUTest, BRKBehavesCorrectly) {
	uint32_t cyclesNeeded = 7;

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::BRK);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	NESsie::ProcessorStatus pushedStatus = cpu.PS;
	pushedStatus.pad_ = 1;
	pushedStatus.B = 1;
	BYTE expectedStackValue = std::bit_cast<BYTE>(pushedStatus);

	EXPECT_EQ(cpu.fetch_byte_from_stack(mainbus), expectedStackValue);
	EXPECT_EQ(cpu.fetch_byte_from_stack(mainbus), 0xFE);
	EXPECT_EQ(cpu.fetch_byte_from_stack(mainbus), 0xFF);
	EXPECT_EQ(cpu.PC, 0xFFFE);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, 1);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion

#pragma region RTI
TEST_F(CPUTest, RTIBehavesCorrectly) {
	uint32_t cyclesNeeded = 6;

	NESsie::CPU cpuCopy = cpu;

	cpu.PC = 0xF7F7;

	mainbus.set_byte(0xF7F7, NESsie::BRK);

	NESsie::ProcessorStatus pushedStatus = cpu.PS;
	pushedStatus.pad_ = 0;
	pushedStatus.B = 0;

	cpu.executeCycles(7, mainbus);

	cpu.PC = 0xFFFC;

	mainbus.set_byte(0xFFFC, NESsie::RTI);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ((BYTE)cpu.PS, (BYTE)pushedStatus);
	EXPECT_EQ(cpu.PC, 0xF7F9);
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion