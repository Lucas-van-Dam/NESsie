#pragma once
#include "defines.h"
#include <array>
#include <utility>
#include <vector>
#include "mapper.h"

namespace NESsie {
	class ppu;
	class Input;
	static constexpr std::size_t MAINBUS_SIZE = 0x800;

	class MainBus {
	public:
		MainBus();
		MainBus(std::shared_ptr<Mapper> mapper) : mapper(std::move(mapper)) {}

		void initialize(ppu* ppu, Input* input); // delaying ppu setting due to ppu needing mainbus as well
		void initialize(const std::vector<BYTE>& initialMainBus);

		BYTE read_byte(WORD address);
		void set_byte(WORD address, BYTE value);

		WORD read_word(WORD address);
		void set_word(WORD address, WORD value);

	private:
		std::array<BYTE, MAINBUS_SIZE> mainbus{};

		std::array<BYTE, 0x2000> memory{};

		std::shared_ptr<Mapper> mapper;
		ppu* ppu_;
		Input* input_;
	};
}