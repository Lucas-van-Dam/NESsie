#include "cpu.h"
#include <iostream>
#include <bit>

namespace CPU {
	CPU::CPU() {

	}
	void CPU::initialize(Memory::Memory& memory)
	{
		A = 0;
		X = 0;
		Y = 0;
		PC = 0xFFFC;
		S = 0xFD;
		PS.C = 0;
		PS.Z = 0;
		PS.I = 1;
		PS.D = 0;
		PS.V = 0;
		PS.N = 0;
		PS.pad_ = 0;

		memory.initialize();
	}

	uint32_t CPU::executeCycles(uint32_t cycles, Memory::Memory& memory)
	{
		uint32_t cyclesRan = 0;
		while (cycles > 0) {
			BYTE instruction = fetch_byte(memory);
			uint32_t executed = executeInstruction(instruction, cycles, memory);
			if (executed > cycles) {
				std::cerr << "executed more cycles than requested, executed: " << executed << ", left:" << cycles << std::endl;
				cycles = 0;
			}
			else {
				cycles -= executed;
			}

			cyclesRan += executed;

		}

		return cyclesRan;
	}
	uint32_t CPU::executeInstruction(BYTE instruction, uint32_t cyclesLeft, Memory::Memory& memory)
	{
		static bool setInteruptFlagAtNextInstruction = false;

		if (setInteruptFlagAtNextInstruction) {
			PS.I = 1;
			setInteruptFlagAtNextInstruction = false;
		}

		switch (instruction) {
		case LDAIM: {
			BYTE constant = fetch_byte(memory);
			A = constant;

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 2;
		}
		case LDAZP: {
			BYTE address = fetch_byte(memory);
			A = memory.read_byte(address);

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 3;
		}
		case LDAZPX: {
			BYTE address = fetch_byte(memory);
			address += X;
			BYTE value = memory.read_byte(address);
			A = value;

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 4;
		}
		case LDAABS: {
			WORD address = fetch_word(memory);
			A = memory.read_byte(address);

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 4;
		}
		case LDAABSX: {
			bool crossedPageBoundary = false;
			WORD address = fetch_word(memory);
			if ((BYTE)address + X > 0xFF)
				crossedPageBoundary = true;
			A = memory.read_byte(address + X);

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return crossedPageBoundary ? 5 : 4;
		}
		case LDAABSY: {
			bool crossedPageBoundary = false;
			WORD address = fetch_word(memory);
			if ((BYTE)address + Y > 0xFF)
				crossedPageBoundary = true;
			A = memory.read_byte(address + Y);

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return crossedPageBoundary ? 5 : 4;
		}
		case LDAINDX: {
			BYTE zeroPageAddress = fetch_byte(memory);
			BYTE zeroPageAddressPlusX = zeroPageAddress + X;
			WORD address = memory.read_byte(zeroPageAddressPlusX);
			address |= memory.read_byte(zeroPageAddressPlusX + 1) << 4;

			A = memory.read_byte(address);

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 6;
		}
		case LDAINDY: {
			bool crossedPageBoundary = false;
			BYTE zeroPageAddress = fetch_byte(memory);
			WORD address = memory.read_byte(zeroPageAddress);
			address |= memory.read_byte(zeroPageAddress + 1) << 4;

			if ((address & 0xFF) + Y > 0xFF)
				crossedPageBoundary = true;

			A = memory.read_byte(address + Y);

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return crossedPageBoundary ? 6 : 5;
		}

		case LDXIM: {
			BYTE constant = fetch_byte(memory);
			X = constant;

			if (X == 0x00)
				PS.Z = 1;
			if (X & 0x80)
				PS.N = 1;

			return 2;
		}
		case LDXZP: {
			BYTE address = fetch_byte(memory);
			X = memory.read_byte(address);

			if (X == 0x00)
				PS.Z = 1;
			if (X & 0x80)
				PS.N = 1;

			return 3;
		}
		case LDXZPY: {
			BYTE address = fetch_byte(memory);
			address += Y;
			BYTE value = memory.read_byte(address);
			X = value;

			if (X == 0x00)
				PS.Z = 1;
			if (X & 0x80)
				PS.N = 1;

			return 4;
		}
		case LDXABS: {
			WORD address = fetch_word(memory);
			X = memory.read_byte(address);

			if (X == 0x00)
				PS.Z = 1;
			if (X & 0x80)
				PS.N = 1;

			return 4;
		}
		case LDXABSY: {
			bool crossedPageBoundary = false;
			WORD address = fetch_word(memory);
			if ((BYTE)address + Y > 0xFF)
				crossedPageBoundary = true;
			X = memory.read_byte(address + Y);

			if (X == 0x00)
				PS.Z = 1;
			if (X & 0x80)
				PS.N = 1;

			return crossedPageBoundary ? 5 : 4;
		}

		case LDYIM: {
			BYTE constant = fetch_byte(memory);
			Y = constant;

			if (Y == 0x00)
				PS.Z = 1;
			if (Y & 0x80)
				PS.N = 1;

			return 2;
		}
		case LDYZP: {
			BYTE address = fetch_byte(memory);
			Y = memory.read_byte(address);

			if (Y == 0x00)
				PS.Z = 1;
			if (Y & 0x80)
				PS.N = 1;

			return 3;
		}
		case LDYZPX: {
			BYTE address = fetch_byte(memory);
			address += X;
			BYTE value = memory.read_byte(address);
			Y = value;

			if (Y == 0x00)
				PS.Z = 1;
			if (Y & 0x80)
				PS.N = 1;

			return 4;
		}
		case LDYABS: {
			WORD address = fetch_word(memory);
			Y = memory.read_byte(address);

			if (Y == 0x00)
				PS.Z = 1;
			if (Y & 0x80)
				PS.N = 1;

			return 4;
		}
		case LDYABSX: {
			bool crossedPageBoundary = false;
			WORD address = fetch_word(memory);
			if ((BYTE)address + X > 0xFF)
				crossedPageBoundary = true;
			Y = memory.read_byte(address + X);

			if (Y == 0x00)
				PS.Z = 1;
			if (Y & 0x80)
				PS.N = 1;

			return crossedPageBoundary ? 5 : 4;
		}

		case STAZP: {
			BYTE zeroPageAddress = fetch_byte(memory);
			memory.set_byte(zeroPageAddress, A);

			return 3;
		}
		case STAZPX: {
			BYTE zeroPageAddress = fetch_byte(memory);
			zeroPageAddress += X;

			memory.set_byte(zeroPageAddress, A);

			return 4;
		}
		case STAABS: {
			WORD address = fetch_word(memory);
			memory.set_byte(address, A);

			return 4;
		}
		case STAABSX: {
			WORD address = fetch_word(memory);
			memory.set_byte(address + X, A);

			return 5;
		}
		case STAABSY: {
			WORD address = fetch_word(memory);
			memory.set_byte(address + Y, A);

			return 5;
		}
		case STAINDX: {
			BYTE zeroPageAddress = fetch_byte(memory);
			BYTE zeroPageAddressPlusX = zeroPageAddress + X;
			WORD address = memory.read_byte(zeroPageAddressPlusX);
			address |= memory.read_byte(zeroPageAddressPlusX + 1) << 4;

			memory.set_byte(address, A);

			return 6;
		}
		case STAINDY: {
			BYTE zeroPageAddress = fetch_byte(memory);
			WORD address = memory.read_byte(zeroPageAddress);
			address |= memory.read_byte(zeroPageAddress + 1) << 4;

			memory.set_byte(address + Y, A);

			return 6;
		}

		case STXZP: {
			BYTE zeroPageAddress = fetch_byte(memory);
			memory.set_byte(zeroPageAddress, X);

			return 3;
		}
		case STXZPY: {
			BYTE zeroPageAddress = fetch_byte(memory);
			zeroPageAddress += Y;

			memory.set_byte(zeroPageAddress, X);

			return 4;
		}
		case STXABS: {
			WORD address = fetch_word(memory);
			memory.set_byte(address, X);

			return 4;
		}

		case STYZP: {
			BYTE zeroPageAddress = fetch_byte(memory);
			memory.set_byte(zeroPageAddress, Y);

			return 3;
		}
		case STYZPX: {
			BYTE zeroPageAddress = fetch_byte(memory);
			zeroPageAddress += X;

			memory.set_byte(zeroPageAddress, Y);

			return 4;
		}
		case STYABS: {
			WORD address = fetch_word(memory);
			memory.set_byte(address, Y);

			return 4;
		}

		case TAX: {
			X = A;

			if (X == 0x00)
				PS.Z = 1;
			if (X & 0x80)
				PS.N = 1;

			return 2;
		}

		case TXA: {
			A = X;

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 2;
		}

		case TAY: {
			Y = A;

			if (Y == 0x00)
				PS.Z = 1;
			if (Y & 0x80)
				PS.N = 1;

			return 2;
		}

		case TYA: {
			A = Y;

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 2;
		}

		case TSX: {
			X = S;

			if (X == 0x00)
				PS.Z = 1;
			if (X & 0x80)
				PS.N = 1;

			return 2;
		}

		case TXS: {
			S = X;

			return 2;
		}

		case PHA: {
			push_byte_to_stack(memory, A);

			return 3;
		}

		case PHP: {
			ProcessorStatus pushedStatus = PS;
			pushedStatus.B = 1;
			pushedStatus.pad_ = 1;
			BYTE pushedStatusByte = std::bit_cast<BYTE>(pushedStatus);
			push_byte_to_stack(memory, pushedStatusByte);

			return 3;
		}

		case PLA: {
			BYTE value = fetch_byte_from_stack(memory);

			A = value;

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 4;
		}

		case PLP: {
			ProcessorStatus pulledPS = std::bit_cast<ProcessorStatus>(fetch_byte_from_stack(memory));
			pulledPS.B = 0;
			pulledPS.pad_ = 0;

			if (pulledPS.I) {
				pulledPS.I = 0;
				setInteruptFlagAtNextInstruction = true;
			}

			PS = pulledPS;

			return 4;
		}

		case ANDIM: {
			BYTE andValue = fetch_byte(memory);

			BYTE result = A & andValue;
			A = result;

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 2;
		}
		case ANDZP: {
			BYTE zeroPageAddress = fetch_byte(memory);
			BYTE andValue = memory.read_byte(zeroPageAddress);

			BYTE result = A & andValue;
			A = result;

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 3;
		}
		case ANDZPX: {
			BYTE zeroPageAddress = fetch_byte(memory);
			BYTE andValue = memory.read_byte(zeroPageAddress + X);

			BYTE result = A & andValue;
			A = result;

			if (A == 0x00)
				PS.Z = 1;
			if (A & 0x80)
				PS.N = 1;

			return 4;
		}

		case NOP: {
			return 2;
		}

		default:
			return 0;
		}
	}

	BYTE CPU::fetch_byte(Memory::Memory& memory)
	{
		BYTE byte = memory.read_byte(PC);
		PC++;
		return byte;
	}

	WORD CPU::fetch_word(Memory::Memory& memory) {
		WORD word = memory.read_word(PC);
		PC += 2;
		return word;
	}

	BYTE CPU::fetch_byte_from_stack(Memory::Memory& memory)
	{
		WORD stackAddress = 0x0100;
		S++;
		BYTE value = memory.read_byte(stackAddress + S);
		return value;
	}

	void CPU::push_byte_to_stack(Memory::Memory& memory, BYTE value)
	{
		WORD stackAddress = 0x0100;
		memory.set_byte(stackAddress + S, value);
		S--;
	}

	BYTE CPU::peek_byte_from_stack(Memory::Memory& memory)
	{
		WORD stackAddress = 0x0100;
		BYTE value = memory.read_byte(stackAddress + S + 1);
		return value;
	}
}