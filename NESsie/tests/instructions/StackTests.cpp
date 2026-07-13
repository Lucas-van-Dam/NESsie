#include <tests/TestCpu.h>

#include <bit>

#pragma region TSX
TEST_F(CPUTest, TSXBehavesCorrectly) {
	uint32_t cyclesNeeded = 2;

	cpu.S = 0x07;

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::TSX);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(cpu.X, cpu.S);
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

TEST_F(CPUTest, TSXCorrectlySetsZeroFlag) {
	uint32_t cyclesNeeded = 2;

	cpu.S = 0x00;

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::TSX);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(cpu.X, cpu.S);
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

TEST_F(CPUTest, TSXCorrectlySetsNegativeFlag) {
	uint32_t cyclesNeeded = 2;

	cpu.S = 0x87;

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::TSX);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(cpu.X, cpu.S);
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

#pragma region TXS
TEST_F(CPUTest, TXSBehavesCorrectly) {
	uint32_t cyclesNeeded = 2;

	cpu.X = 0x07;

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::TXS);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(cpu.S, cpu.X);
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

#pragma region PHA
TEST_F(CPUTest, PHABehavesCorrectly) {
	uint32_t cyclesNeeded = 3;

	cpu.A = 0x07;

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::PHA);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(cpu.peek_byte_from_stack(mainbus), cpu.A);
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

#pragma region PHP
TEST_F(CPUTest, PHPBehavesCorrectly) {
	uint32_t cyclesNeeded = 3;

	NESsie::CPU cpuCopy = cpu;

	mainbus.set_byte(0xFFFC, NESsie::PHP);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	NESsie::ProcessorStatus pushedStatus = cpu.PS;
	pushedStatus.pad_ = 1;
	pushedStatus.B = 1;
	BYTE expectedStackValue = std::bit_cast<BYTE>(pushedStatus);

	EXPECT_EQ(cpu.peek_byte_from_stack(mainbus), expectedStackValue);
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

#pragma region PLA
TEST_F(CPUTest, PLABehavesCorrectly) {
	uint32_t cyclesNeeded = 4;

	NESsie::CPU cpuCopy = cpu;

	cpu.push_byte_to_stack(mainbus, 0x07);

	mainbus.set_byte(0xFFFC, NESsie::PLA);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(cpu.A, 0x07);
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

TEST_F(CPUTest, PLACorrectlySetsZeroFlag) {
	uint32_t cyclesNeeded = 4;

	NESsie::CPU cpuCopy = cpu;

	cpu.A = 0x07;

	cpu.push_byte_to_stack(mainbus, 0x00);

	mainbus.set_byte(0xFFFC, NESsie::PLA);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(cpu.A, 0x00);
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

TEST_F(CPUTest, PLACorrectlySetsNegativeFlag) {
	uint32_t cyclesNeeded = 4;

	NESsie::CPU cpuCopy = cpu;

	cpu.push_byte_to_stack(mainbus, 0x87);

	mainbus.set_byte(0xFFFC, NESsie::PLA);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	EXPECT_EQ(cpu.A, 0x87);
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

#pragma region PLP
TEST_F(CPUTest, PLPBehavesCorrectly) {
	uint32_t cyclesNeeded = 4;

	NESsie::CPU cpuCopy = cpu;

	BYTE PS = 0xB4; // N = 1, I = 1, B and pad_ are pushed as 1 (simulated PHP instruction)

	cpu.push_byte_to_stack(mainbus, PS);

	mainbus.set_byte(0xFFFC, NESsie::PLP);

	uint32_t cyclesExecuted = cpu.executeCycles(cyclesNeeded, mainbus);

	BYTE ProcessorStatusAfterPLP = std::bit_cast<BYTE>(cpu.PS);

	EXPECT_EQ(ProcessorStatusAfterPLP, 0x80); // N = 1, I = 1, B and pad_ are ignored, but I takes 1 more instruction to apply

	mainbus.set_byte(0xFFFD, NESsie::NOP);

	cpu.executeCycles(2, mainbus);

	ProcessorStatusAfterPLP = std::bit_cast<BYTE>(cpu.PS);

	EXPECT_EQ(ProcessorStatusAfterPLP, 0x84); // Test if I is actually applied
	EXPECT_EQ(cyclesExecuted, cyclesNeeded);
}
#pragma endregion
