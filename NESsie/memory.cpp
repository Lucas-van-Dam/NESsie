#include "memory.h"
#include <random>

namespace Memory {
	void Memory::initialize()
	{
		static std::random_device rd; // obtain a random number from hardware
		static std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, 0xFF);
		for (WORD address = 0x0000; address <= 0x07FF; address++){
			memory[address] = distr(gen);
		}
		for (WORD address = 0x6000; address <= 0x7FFF; address++) {
			memory[address] = distr(gen);
		}
	}
	BYTE Memory::read_byte(WORD address) {
		return memory[address];
	}

	void Memory::set_byte(WORD address, BYTE value)
	{
		memory[address] = value;
	}

	WORD Memory::read_word(WORD address)
	{
		WORD value = memory[address];
		value = value | (memory[address + 1] << 4);
		return value;
	}
	void Memory::set_word(WORD address, WORD value)
	{
		memory[address] = (BYTE)value;
		memory[address + 1] = (BYTE)(value >> 4);
	}
}


