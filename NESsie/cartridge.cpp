#include "cartridge.h"
#include <fstream>
#include <iostream>

namespace NESsie {



	bool Cartridge::loadCartridgeFromFile(const std::filesystem::path& path)
	{
		std::ifstream romData(path, std::ios_base::binary);
		if (!romData.is_open()) {
			std::cerr << "couldnt open rom file" << std::endl;
			return false;
		}

		std::vector<BYTE> header(0x10);
		if (!romData.read(reinterpret_cast<char*>(header.data()), 0x10)) {
			std::cerr << "couldnt read rom file" << std::endl;
			return false;
		}

		if (std::string{ &header[0], &header[4] } != "NES\x1a") {
			std::cerr << "incorrect magic" << std::endl;
			return false;
		}

		uint64_t banks = header[4];
		if (banks <= 0) {
			std::cerr << "no PRG rom banks indicated" << std::endl;
			return false;
		}

		PRG_ROM.resize(banks * 16384);

		banks = header[5];
		if (banks <= 0) {
			std::cerr << "no CHR rom banks indicated" << std::endl;
			return false;
		}

		CHR_ROM.resize(banks * 8192);

		FLAGS6 flags6 = static_cast<FLAGS6>(header[6]);

		FLAGS7 flags7 = static_cast<FLAGS7>(header[7]);

		BYTE mapper = ((BYTE)flags6 & (BYTE)FLAGS6::mapperNumber) >> 4;
		mapper |= ((BYTE)flags7 & (BYTE)FLAGS7::mapperNumber);

		if ((BYTE)flags6 & (BYTE)FLAGS6::nametable) {
			mirroring = NameTableMirroring::Horizontal;
		}
		else {
			mirroring = NameTableMirroring::Vertical;
		}

		romData.read(reinterpret_cast<char*>(PRG_ROM.data()), PRG_ROM.size());

		romData.read(reinterpret_cast<char*>(CHR_ROM.data()), CHR_ROM.size());

		return true;
	}

	const std::vector<BYTE>& Cartridge::getPRGRom()
	{
		return PRG_ROM;
	}

	const std::vector<BYTE>& Cartridge::getCHRRom()
	{
		return CHR_ROM;
	}

}