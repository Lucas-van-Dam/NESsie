#include "NROMMapper.h"
#include <iostream>

namespace NESsie {

	NROMMapper::NROMMapper(std::unique_ptr<Cartridge> cartridge)
		: Mapper(std::move(cartridge))
	{
		if (this->cartridge->getPRGRom().size() > 16384)
			doubleBank = true;
		else
			doubleBank = false;

		if (this->cartridge->getCHRRom().empty())
			std::cerr << "dont know what to do yet" << std::endl;
	}

	void NROMMapper::write_prg(WORD address, BYTE value)
	{
		std::cerr << "Tried to write to PRG ROM" << std::endl;
	}

	BYTE NROMMapper::read_prg(WORD address)
	{
		if (doubleBank)
			return cartridge->getPRGRom()[address - 0x8000];
		else
			return cartridge->getPRGRom()[(address - 0x8000) & 0x3FFF];
	}

	void NROMMapper::write_chr(WORD address, BYTE value)
	{
	}

	BYTE NROMMapper::read_chr(WORD address)
	{
		return 0;
	}

	std::shared_ptr<Mapper> NESsie::create_nrom_mapper(std::unique_ptr<Cartridge> cartridge)
	{
		return std::make_shared<NROMMapper>(std::move(cartridge));
	}
}