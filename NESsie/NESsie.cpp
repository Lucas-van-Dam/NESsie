#include "NESsie.h"

#include "cpu.h"

#include <filesystem>
#include <fstream>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include "ppu.h"
#include "VirtualScreen.h"

static std::vector<BYTE> loadMainBusFromFile(const std::filesystem::path& binFile) {
	std::ifstream file(binFile, std::ios_base::binary);

	if (!file.is_open()) {
		std::cerr << "Couldnt open file: " << binFile.generic_string() << std::endl;
		return {};
	}

	std::vector<BYTE> mainbus;
	mainbus.reserve(0xFFFF);

	while (file.good()) {
		BYTE value;
		if (file.read(reinterpret_cast<char*>(&value), 1))
			mainbus.push_back(value);
	}
}

int main(int argc, char **argv)
{
	//auto initialMainBus = loadMainBusFromFile("C:\\testROMs\\6502_functional_test.bin");

	std::unique_ptr<NESsie::Cartridge> cartridge = std::make_unique<NESsie::Cartridge>();

	cartridge->loadCartridgeFromFile("C:\\Users\\lucas\\Downloads\\Donkey Kong.nes");

	std::vector<BYTE> temp_copy = cartridge->getCHRRom();
	
	std::shared_ptr<NESsie::Mapper> mapper;

	switch (static_cast<NESsie::KnownMappers>(cartridge->getMapper())) {
	case NESsie::KnownMappers::NROM:
		mapper = NESsie::create_nrom_mapper(std::move(cartridge));
	}

	NESsie::VirtualScreen virtual_screen;
	NESsie::MainBus mem(mapper);
	NESsie::ppu ppu(mapper, mem);
	NESsie::CPU cpu;


	cpu.initialize(mem, &ppu);

	cpu.start(mem);

	bool running = true;
	SDL_Event event;
	while (running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
					running = false;
					break;
				default:
					//SDL_Log("unhandled event type %d", event.type);
					break;
			}
		}

		//virtual_screen.show_pattern_table(temp_copy);

		ppu.step();
		ppu.step();
		ppu.step();

		cpu.step(mem);
	}

	return 0;
}
