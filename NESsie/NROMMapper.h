#pragma once
#include "Mapper.h"

namespace NESsie {

	class NROMMapper : public Mapper {
	public:
		NROMMapper(std::unique_ptr<Cartridge> cartridge);

		virtual void write_prg(WORD address, BYTE value) override;
		virtual BYTE read_prg(WORD address) override;

		virtual void write_chr(WORD address, BYTE value) override;
		virtual BYTE read_chr(WORD address) override;

	private:
		bool doubleBank;
	};

}