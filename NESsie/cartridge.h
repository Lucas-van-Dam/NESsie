#pragma once
#include "defines.h"
#include <vector>
#include <filesystem>

namespace NESsie {
	enum class NameTableMirroring
	{
		Horizontal = 0,
		Vertical = 1,
	};

	enum class FLAGS6 : BYTE {
		nametable = 1,
		battery = 1 << 1,
		trainer = 1 << 2,
		altNametableLayout = 1 << 3,
		mapperNumber = 0b11110000,
	};

	enum class FLAGS7 : BYTE {
		vsunisystem = 1,
		playchoice10 = 1 << 1,
		useNES2Format = 0b1100,
		mapperNumber = 0b11110000,
	};
	
	class Cartridge {
	public:
		bool loadCartridgeFromFile(const std::filesystem::path& path);

		NameTableMirroring getNametableMirroring() { return mirroring; }

		const std::vector<BYTE>& getPRGRom();
		const std::vector<BYTE>& getCHRRom();

		BYTE getMapper() { return mapper; }

	private:
		std::vector<BYTE> PRG_ROM;
		std::vector<BYTE> CHR_ROM;
		BYTE mapper;
		NameTableMirroring mirroring;
	};

}
