// NESsie.cpp : Defines the entry point for the application.
//

#include "NESsie.h"

#include "cpu.h"

int main()
{
	CPU::CPU cpu;
	Memory::Memory mem;

	cpu.initialize(mem);

	mem.set_byte(0xFFFC, CPU::LDAIM);
	mem.set_byte(0xFFFD, 0x11);

	cpu.executeCycles(2, mem);

	return 0;
}
