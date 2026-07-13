//
// Created by LucasVanDam on 08/07/2026.
//

#pragma once
#include <memory>
#include <vector>

#include "defines.h"

#include <SDL3/SDL.h>

#include "mapper.h"

namespace NESsie {
    class VirtualScreen {
    public:
        VirtualScreen();

        void show_pattern_table(const std::vector<BYTE>& patternData);
    private:
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;

    };
}
