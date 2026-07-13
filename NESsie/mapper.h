#pragma once
#include "defines.h"
#include "cartridge.h"
#include <memory>

namespace NESsie {

	enum class KnownMappers : BYTE {
		NROM = 0x00,
	};

	class Mapper {
	public:
		virtual ~Mapper() = default;

		Mapper(std::unique_ptr<Cartridge> cartridge) : cartridge(std::move(cartridge)) {};

		virtual void write_prg(WORD address, BYTE value) = 0;
		virtual BYTE read_prg(WORD address) = 0;

		virtual void write_chr(WORD address, BYTE value) = 0;
		virtual BYTE read_chr(WORD address) = 0;

		virtual NameTableMirroring getNameTableMirroring();

	protected:
		std::unique_ptr<Cartridge> cartridge;
	};

	std::shared_ptr<Mapper> create_test_mapper();
	std::shared_ptr<Mapper> create_nrom_mapper(std::unique_ptr<Cartridge> cartridge);
}