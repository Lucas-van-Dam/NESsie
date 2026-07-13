//
// Created by LucasVanDam on 08/07/2026.
//

#include "VirtualScreen.h"

namespace NESsie {
    VirtualScreen::VirtualScreen() {
        SDL_SetAppMetadata("NESsie", "1.0.0", "com.nessie");

        if (!SDL_Init(SDL_INIT_VIDEO)) {
            SDL_Log("Could not initialize SDL: %s", SDL_GetError());
            return;
        }

        if (!SDL_CreateWindowAndRenderer("NESsie", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
            SDL_Log("Could not create window/renderer: %s", SDL_GetError());
            return;
        }

        SDL_SetRenderLogicalPresentation(renderer, 300, 300, SDL_LOGICAL_PRESENTATION_LETTERBOX);
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
