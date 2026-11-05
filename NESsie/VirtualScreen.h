//
// Created by LucasVanDam on 08/07/2026.
//

#pragma once
#include <memory>
#include <vector>

#include "defines.h"

#include <SDL3/SDL.h>

#include <ranges>

#include "mapper.h"

namespace NESsie {
    class VirtualScreen {
    public:
        VirtualScreen();

        void display() const;

        void clear_screen(SDL_Color color) const;

        void set_pixel(int x, int y, SDL_Color color) const;
        void set_tile_pixels(int x, int y, BYTE tileLow, BYTE tileHigh) const;

        void set_screen(std::vector<Uint32>& pixels, int width, int height, int frame);

        void show_pattern_table(const std::vector<BYTE>& patternData);
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;

    };
}
