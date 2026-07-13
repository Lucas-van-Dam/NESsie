#include <tests/TestCpu.h>

#pragma region BCC
TEST_F(CPUTest, BCCBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	cpu.PS.C = 0;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BCC);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2 + offset);
	EXPECT_EQ(cpu.PS.C, 0);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, BCCCorrectlyUses2CyclesOnNotTakingBranch) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.C = 1;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BCC);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2);
	EXPECT_EQ(cpu.PS.C, 1);
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

#pragma region BCS
TEST_F(CPUTest, BCSBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	cpu.PS.C = 1;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BCS);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2 + offset);
	EXPECT_EQ(cpu.PS.C, 1);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, BCSCorrectlyUses2CyclesOnNotTakingBranch) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.C = 0;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BCS);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2);
	EXPECT_EQ(cpu.PS.C, 0);
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

#pragma region BEQ
TEST_F(CPUTest, BEQBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	cpu.PS.Z = 1;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BEQ);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2 + offset);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, BEQCorrectlyUses2CyclesOnNotTakingBranch) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.Z = 0;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BEQ);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
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

#pragma region BNE
TEST_F(CPUTest, BNEBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	cpu.PS.Z = 0;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BNE);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2 + offset);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 0);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, BNECorrectlyUses2CyclesOnNotTakingBranch) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.Z = 1;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BNE);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, 1);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region BPL
TEST_F(CPUTest, BPLBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	cpu.PS.N = 1;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BPL);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2 + offset);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, BPLCorrectlyUses2CyclesOnNotTakingBranch) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.N = 0;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BPL);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region BMI
TEST_F(CPUTest, BMIBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	cpu.PS.N = 0;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BMI);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2 + offset);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 0);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, BMICorrectlyUses2CyclesOnNotTakingBranch) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.N = 1;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BMI);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, cpuCopy.PS.V);
	EXPECT_EQ(cpu.PS.N, 1);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region BVC
TEST_F(CPUTest, BVCBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	cpu.PS.V = 0;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BVC);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2 + offset);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, BVCCorrectlyUses2CyclesOnNotTakingBranch) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.V = 1;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BVC);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion

#pragma region BVS
TEST_F(CPUTest, BVSBehavesCorrectly) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 3;

	cpu.PS.V = 1;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BVS);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PC, cpuCopy.PC + 2 + offset);
	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 1);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
TEST_F(CPUTest, BVSCorrectlyUses2CyclesOnNotTakingBranch) {
	NESsie::CPU cpuCopy = cpu;
	uint32_t expectedCycles = 2;

	cpu.PS.V = 0;

	SIGNEDBYTE offset = -55;

	mainbus.set_byte(0xFFFC, NESsie::BVS);
	mainbus.set_byte(0xFFFD, offset);

	uint32_t cyclesExecuted = cpu.executeCycles(expectedCycles, mainbus);

	EXPECT_EQ(cpu.PS.C, cpuCopy.PS.C);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.Z, cpuCopy.PS.Z);
	EXPECT_EQ(cpu.PS.I, cpuCopy.PS.I);
	EXPECT_EQ(cpu.PS.D, cpuCopy.PS.D);
	EXPECT_EQ(cpu.PS.B, cpuCopy.PS.B);
	EXPECT_EQ(cpu.PS.V, 0);
	EXPECT_EQ(cpu.PS.N, cpuCopy.PS.N);
	EXPECT_EQ(cpu.PS.pad_, cpuCopy.PS.pad_);
	EXPECT_EQ(cyclesExecuted, expectedCycles);
}
#pragma endregion