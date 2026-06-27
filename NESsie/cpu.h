#include "defines.h"
#include "memory.h"

namespace CPU {

	enum OpCodes : BYTE {
		// LDA
		LDAIM = 0xA9,
		LDAZP = 0xA5,
		LDAZPX = 0xB5,
		LDAABS = 0xAD,
		LDAABSX = 0xBD,
		LDAABSY = 0xB9,
		LDAINDX = 0xA1,
		LDAINDY = 0xB1,
		// LDX
		LDXIM = 0xA2,
		LDXZP = 0xA6,
		LDXZPY = 0xB6,
		LDXABS = 0xAE,
		LDXABSY = 0xBE,
		// LDY
		LDYIM = 0xA0,
		LDYZP = 0xA4,
		LDYZPX = 0xB4,
		LDYABS = 0xAC,
		LDYABSX = 0xBC,
		// STA
		STAZP = 0x85,
		STAZPX = 0x95,
		STAABS = 0x8D,
		STAABSX = 0x9D,
		STAABSY = 0x99,
		STAINDX = 0x81,
		STAINDY = 0x91,
		// STX
		STXZP = 0x86,
		STXZPY = 0x96,
		STXABS = 0x8E,
		// STY
		STYZP = 0x84,
		STYZPX = 0x94,
		STYABS = 0x8C,
		// TAX
		TAX = 0xAA,
		// TXA
		TXA = 0x8A,
		// TAY
		TAY = 0xA8,
		// TYA
		TYA = 0x98,
		// TSX
		TSX = 0xBA,
		// TXS
		TXS = 0x9A,
		// PHA
		PHA = 0x48,
		// PHP
		PHP = 0x08,
		// PLA
		PLA = 0x68,
		// PLP
		PLP = 0x28,
		// AND
		ANDIM = 0x29,
		ANDZP = 0x25,
		ANDZPX = 0x35,
		ANDABS = 0x2D,
		ANDABSX = 0x3D,
		ANDABSY = 0x39,
		ANDINDX = 0x21,
		ANDINDY = 0x31,


		// NOP
		NOP = 0xEA,
	};

	struct ProcessorStatus {
		BYTE C : 1;
		BYTE Z : 1;
		BYTE I : 1;
		BYTE D : 1;
		BYTE B : 1;
		BYTE pad_ : 1;
		BYTE V : 1;
		BYTE N : 1;
	};
	static_assert(sizeof(ProcessorStatus) == sizeof(BYTE), "Processor status needs to be exactly 1 BYTE long");

	class CPU {
	public:
		CPU();

		void initialize(Memory::Memory& memory);

		// returns amount of cycles ran
		uint32_t executeCycles(uint32_t cycles, Memory::Memory& memory);
		// returns amount of cycles ran
		uint32_t executeInstruction(BYTE instruction, uint32_t cyclesLeft, Memory::Memory& memory);

		BYTE fetch_byte(Memory::Memory& memory);

		WORD fetch_word(Memory::Memory& memory);

		BYTE fetch_byte_from_stack(Memory::Memory& memory);
		void push_byte_to_stack(Memory::Memory& memory, BYTE value);

		// Mostly used for debugging/testing top stack value without affecting stack pointer
		BYTE peek_byte_from_stack(Memory::Memory& memory);

		//WORD fetch_word_from_stack(Memory::Memory& memory);
		//void push_word_to_stack(Memory::Memory& memory, WORD value);

		BYTE A;
		BYTE X;
		BYTE Y;
		WORD PC;
		BYTE S;
		ProcessorStatus PS;
	};

}