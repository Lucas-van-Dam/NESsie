//
// Created by LucasVanDam on 29/07/2026.
//
#include "SDL3/SDL.h"

#include "Input.h"
namespace NESsie {
    Input::Input() {
        keys = SDL_GetKeyboardState(nullptr);
    }

    void Input::write(WORD address, BYTE value) {
        if (address == INPUT1_ADDR) {
            strobeBit = value & 1;
        }
    }

    BYTE Input::read(WORD address) {
        if (address == INPUT1_ADDR) {
            if (currentInputIndex > 7)
                return 1;
            BYTE input = (currentInputState >> currentInputIndex) & 1;
            currentInputIndex++;
            return input;
        }
        return 1;
    }

    void Input::step() {
        if (strobeBit) {
            currentInputIndex = 0x00;
            currentInputState = 0;
            currentInputState |= keys[SDL_SCANCODE_L] << 0; // A
            currentInputState |= keys[SDL_SCANCODE_K] << 1; // B
            currentInputState |= keys[SDL_SCANCODE_G] << 2; // Select
            currentInputState |= keys[SDL_SCANCODE_H] << 3; // Start
            currentInputState |= keys[SDL_SCANCODE_W] << 4; // Up
            currentInputState |= keys[SDL_SCANCODE_S] << 5; // Down
            currentInputState |= keys[SDL_SCANCODE_A] << 6; // Left
            currentInputState |= keys[SDL_SCANCODE_D] << 7; // Right
        }
    }
}
