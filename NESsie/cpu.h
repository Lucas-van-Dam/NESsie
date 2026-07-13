#pragma once
#include "defines.h"
#include "mainbus.h"
#include <bit>
#include <vector>

namespace NESsie {

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
		// ORA
		ORAIM = 0x09,
		ORAZP = 0x05,
		ORAZPX = 0x15,
		ORAABS = 0x0D,
		ORAABSX = 0x1D,
		ORAABSY = 0x19,
		ORAINDX = 0x01,
		ORAINDY = 0x11,
		// EOR
		EORIM = 0x49,
		EORZP = 0x45,
		EORZPX = 0x55,
		EORABS = 0x4D,
		EORABSX = 0x5D,
		EORABSY = 0x59,
		EORINDX = 0x41,
		EORINDY = 0x51,
		// BIT
		BITZP = 0x24,
		BITABS = 0x2C,
		// ADC
		ADCIM = 0x69,
		ADCZP = 0x65,
		ADCZPX = 0x75,
		ADCABS = 0x6D,
		ADCABSX = 0x7D,
		ADCABSY = 0x79,
		ADCINDX = 0x61,
		ADCINDY = 0x71,
		// SBC
		SBCIM = 0xE9,
		SBCZP = 0xE5,
		SBCZPX = 0xf5,
		SBCABS = 0xED,
		SBCABSX = 0xFD,
		SBCABSY = 0xF9,
		SBCINDX = 0xE1,
		SBCINDY = 0xF1,
		// INC
		INCZP = 0xE6,
		INCZPX = 0xF6,
		INCABS = 0xEE,
		INCABSX = 0xFE,
		// DEC
		DECZP = 0xC6,
		DECZPX = 0xD6,
		DECABS = 0xCE,
		DECABSX = 0xDE,
		// INX
		INX = 0xE8,
		// DEX
		DEX = 0xCA,
		// INY
		INY = 0xC8,
		// DEY
		DEY = 0x88,
		// ASL
		ASLAC = 0x0A,
		ASLZP = 0x06,
		ASLZPX = 0x16,
		ASLABS = 0x0E,
		ASLABSX = 0x1E,
		// LSR
		LSRAC = 0x4A,
		LSRZP = 0x46,
		LSRZPX = 0x56,
		LSRABS = 0x4E,
		LSRABSX = 0x5E,
		// ROL
		ROLAC = 0x2A,
		ROLZP = 0x26,
		ROLZPX = 0x36,
		ROLABS = 0x2E,
		ROLABSX = 0x3E,
		// ROR
		RORAC = 0x6A,
		RORZP = 0x66,
		RORZPX = 0x76,
		RORABS = 0x6E,
		RORABSX = 0x7E,
		// CMP
		CMPIM = 0xC9,
		CMPZP = 0xC5,
		CMPZPX = 0xD5,
		CMPABS = 0xCD,
		CMPABSX = 0xDD,
		CMPABSY = 0xD9,
		CMPINDX = 0xC1,
		CMPINDY = 0xD1,
		// CPX
		CPXIM = 0xE0,
		CPXZP = 0xE4,
		CPXABS = 0xEC,
		// CPY
		CPYIM = 0xC0,
		CPYZP = 0xC4,
		CPYABS = 0xCC,
		// BCC
		BCC = 0x90,
		// BCS
		BCS = 0xB0,
		// BEQ
		BEQ = 0xF0,
		// BNE
		BNE = 0xD0,
		// BPL
		BPL = 0x10,
		// BMI
		BMI = 0x30,
		// BVC
		BVC = 0x50,
		// BVS
		BVS = 0x70,
		// JMP
		JMPABS = 0x4C,
		JMPIND = 0x6C,
		// JSR
		JSR = 0x20,
		// RTS
		RTS = 0x60,
		// BRK
		BRK = 0x00,
		// RTI
		RTI = 0x40,
		// CLC
		CLC = 0x18,
		// SEC
		SEC = 0x38,
		// CLI
		CLI = 0x58,
		// SEI
		SEI = 0x78,
		// CLD
		CLD = 0xD8,
		// SED
		SED = 0xF8,
		// CLV
		CLV = 0xB8,
		// NOP
		NOP = 0xEA,
	};

	struct ProcessorStatus {
		bool C : 1;
		bool Z : 1;
		bool I : 1;
		bool D : 1;
		bool B : 1;
		bool pad_ : 1;
		bool V : 1;
		bool N : 1;

		operator BYTE() {
			return std::bit_cast<BYTE>(*this);
		}

		bool operator ==(const ProcessorStatus& other) {
			return std::bit_cast<BYTE>(*this) == std::bit_cast<BYTE>(other);
		}
	};
	static_assert(sizeof(ProcessorStatus) == sizeof(BYTE), "Processor status needs to be exactly 1 BYTE long");

	class CPU {
	public:
		CPU();

		void initialize(MainBus& mainbus, ppu* ppu);
		void initialize(MainBus& mainbus, const std::vector<BYTE>& initialMainBus);

		// returns amount of cycles ran
		uint32_t executeCycles(uint32_t cycles, MainBus& mainbus);
		// returns amount of cycles ran
		uint32_t executeInstruction(BYTE instruction, MainBus& mainbus);

		void step(MainBus& mainbus);

		void start(MainBus& mainbus);

		BYTE fetch_byte(MainBus& mainbus);

		WORD fetch_word(MainBus& mainbus);

		BYTE fetch_byte_from_stack(NESsie::MainBus& mainbus);
		void push_byte_to_stack(MainBus& mainbus, BYTE value);

		// Mostly used for debugging/testing top stack value without affecting stack pointer
		BYTE peek_byte_from_stack(MainBus& mainbus);

		//WORD fetch_word_from_stack(MainBus::MainBus& mainbus);
		//void push_word_to_stack(MainBus::MainBus& mainbus, WORD value);

		BYTE A;
		BYTE X;
		BYTE Y;
		WORD PC;
		BYTE S;
		ProcessorStatus PS;

		uint32_t skipCycles = 0;
	};

}