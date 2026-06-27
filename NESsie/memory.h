#include "defines.h"
#include <array>

namespace Memory {
	static constexpr std::size_t MEMORY_SIZE = 1u << 16;

	class Memory {
	public:
		void initialize();

		BYTE read_byte(WORD address);
		void set_byte(WORD address, BYTE value);

		WORD read_word(WORD address);
		void set_word(WORD address, WORD value);

	private:
		std::array<BYTE, MEMORY_SIZE> memory{};
	};
}