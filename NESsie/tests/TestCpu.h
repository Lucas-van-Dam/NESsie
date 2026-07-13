#include <gtest/gtest.h>
#include <cpu.h>

class CPUTest : public testing::Test {
protected:
	CPUTest() {
		cpu.initialize(mainbus);
	}

	~CPUTest() {

	}

	NESsie::CPU cpu;
	NESsie::MainBus mainbus;
};