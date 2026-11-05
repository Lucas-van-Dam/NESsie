//
// Created by LucasVanDam on 08/07/2026.
//

#include "VirtualScreen.h"

#include <iostream>

namespace NESsie {
    VirtualScreen::VirtualScreen() {
        const int SCREEN_W = 256;
        const int SCREEN_H = 240;

        SDL_SetAppMetadata("NESsie", "1.0.0", "com.nessie");

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("Could not initialize SDL: %s", SDL_GetError());
            return;
        }

        if (!SDL_CreateWindowAndRenderer("NESsie", SCREEN_W, SCREEN_H, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
            SDL_Log("Could not create window/renderer: %s", SDL_GetError());
            return;
        }

        texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STREAMING,
            SCREEN_W,
            SCREEN_H
        );

        if (!texture) {
            SDL_Log("couldnt create texture: %s", SDL_GetError());
            return;
        }

        SDL_SetRenderLogicalPresentation(renderer, SCREEN_W, SCREEN_H, SDL_LOGICAL_PRESENTATION_LETTERBOX);
    }

    void VirtualScreen::display() const {
        SDL_RenderPresent(renderer);
    }

    void VirtualScreen::clear_screen(const SDL_Color color) const {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);

        SDL_RenderClear(renderer);
    }

    void VirtualScreen::set_pixel(const int x, const int y, const SDL_Color color) const {
        SDL_FRect pixel;
        pixel.w = 1;
        pixel.h = 1;
        pixel.x = x;
        pixel.y = y;

        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);

        SDL_RenderRect(renderer, &pixel);
    }

    void VirtualScreen::set_tile_pixels(int x, int y, BYTE tileLow, BYTE tileHigh) const {
        for (int i = 0; i < 8; i++) {
            BYTE bit = 7 - i;

            BYTE patternValue =
                    ((tileLow >> bit) & 1) |
                    (((tileHigh >> bit) & 1) << 1);



            //set_pixel(x + i, y, (tile & (0b10000000 >> i)) ? SDL_Color{255,255,255} : SDL_Color{255,0,255});
        }
    }

    void VirtualScreen::set_screen(std::vector<Uint32> &pixels, int width, int height, int frame) {
        void *texPixels = nullptr;
        int pitch = 0;

        if (!SDL_LockTexture(texture, nullptr, &texPixels, &pitch)) {
            std::cerr << "Couldn't lock texture: " << SDL_GetError() << std::endl;
            return;
        }

        // Copy row-by-row to respect pitch
        Uint8 *dst = static_cast<Uint8*>(texPixels);

        memcpy(dst, pixels.data(), pixels.size() * sizeof(pixels[0]));



        SDL_UnlockTexture(texture);

        SDL_RenderTexture(renderer, texture, nullptr, nullptr);
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderDebugText(renderer, 20, 20, std::to_string(frame).c_str());
        SDL_RenderPresent(renderer);
    }

    void VirtualScreen::show_pattern_table(const std::vector<BYTE> &patternData) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_FRect pixel;
        pixel.w = 1;
        pixel.h = 1;

        for (int patternindex = 0; patternindex < 2; patternindex++) {
            for (int i = 0; i < 16; i++) {
                pixel.y = i;
                for (int j = 0; j < 16; j++) {
                    pixel.x = j;

                    for (int y = 0; y < 8; y++) {
                        int index = i * 256 + j * 16 + y + patternindex * 256 * 16;
                        BYTE plane1 = patternData[index];
                        BYTE plane2 = patternData[index + 8];
                        // 00 = 0, 01 = 255/3, 10 = (255/3)*2, 11 = 255
                        pixel.y = i * 8 + y * pixel.h;
                        for (int x = 0; x < 8; x++) {
                            pixel.x = j * 8 + x * pixel.w + patternindex * 16 * 8 + patternindex;

                            bool plane1set = plane1 & 0b10000000 >> x;
                            bool plane2set = plane2 & 0b10000000 >> x;

                            float greyscale = 1;

                            if (!plane1set && !plane2set) {
                                greyscale = 0;
                            }
                            else if (plane1set && !plane2set) {
                                greyscale = 255/3;
                            }
                            else if (!plane1set && plane2set) {
                                greyscale = (255/3) * 2;
                            }
                            else if (plane1set && plane2set) {
                                greyscale = 255;
                            }

                            SDL_SetRenderDrawColor(renderer, greyscale, greyscale, greyscale, SDL_ALPHA_OPAQUE);

                            SDL_RenderRect(renderer, &pixel);
                        }
                    }
                }
            }
        }

        SDL_RenderPresent(renderer);
    }
}
