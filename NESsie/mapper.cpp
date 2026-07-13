#include "mapper.h"

namespace NESsie {

	NameTableMirroring NESsie::Mapper::getNameTableMirroring()
	{
		return cartridge->getNametableMirroring();
	}
}
