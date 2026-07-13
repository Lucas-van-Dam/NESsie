#include "mainbus.h"
#include <random>
#include <iostream>

#include "ppu.h"

#include "TestMapper.h"

namespace NESsie {
	MainBus::MainBus() {
		std::cout << "no mapper assigned, creating default test mapper" << std::endl;
		mapper = create_test_mapper();
	}

	void MainBus::initialize(ppu* ppu)
	{
		static std::random_device rd; // obtain a random number from hardware
		static std::mt19937 gen(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, 0xFF);
		for (WORD address = 0x0000; address <= 0x07FF; address++){
			set_byte(address,distr(gen));
		}
		if (std::dynamic_pointer_cast<TestMapper>(mapper))
			return;
		for (WORD address = 0x6000; address <= 0x7FFF; address++) {
			set_byte(address, distr(gen));
		}

		ppu_ = ppu;
	}

	void MainBus::initialize(const std::vector<BYTE>& initialMainBus)
	{
		memcpy(mainbus.data(), initialMainBus.data(), initialMainBus.size());
	}

	BYTE MainBus::read_byte(WORD address) {
		if (address < 0x2000)
			return mainbus[address & 0x7FF];
		
		if (address < 0x4020) {
			return ppu_->read_from_ppu(address);
		}

		if (address < 0x6000) {
			std::cerr << "Idk whats supposed to be here, isnt specified really well" << std::endl;
			return 0;
		}

		if (address < 0x8000) {
			return memory[address - 0x6000];
		}
		
		return mapper->read_prg(address);
	}

	void MainBus::set_byte(WORD address, BYTE value)
	{
		if (address < 0x2000) {
			mainbus[address & 0x7FF] = value;
			return;
		}


		if (address < 0x4020) {
			ppu_->write_to_ppu(address, value);
			return;
		}

		if (address < 0x6000) {
			std::cerr << "Idk whats supposed to be here, isnt specified really well" << std::endl;
			return;
		}

		if (address < 0x8000) {
			memory[address - 0x6000] = value;
			return;
		}

		mapper->write_prg(address, value);
	}

	WORD MainBus::read_word(WORD address)
	{
		WORD value = read_byte(address);
		value = value | (read_byte(address + 1) << 8);
		return value;
	}

	void MainBus::set_word(WORD address, WORD value)
	{
		set_byte(address, (BYTE)value);
		set_byte(address + 1, (BYTE)(value >> 8));
	}
}



