#include "include/econsim.h"

SDL_Window *window;

void quit_sdl() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
}

void init_graphics() {
    signal(SIGINT, quit_sdl);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
        die_sdl_error("SDL_Init()");

    if ((window = SDL_CreateWindow("Economy Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  WIDTH*10, HEIGHT*10, 0)) == NULL)
        die_sdl_error("SDL_CreateWindow()");
}

void render() {
    uint32_t color;
    SDL_Rect curr_rect;

    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        int highest_resource = sector_get_highest_resource(&world[i]);

        switch (highest_resource) {
            case ITEM_WOOD: /* Brown */
                color = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 187, 153, 102);
                break;
            case ITEM_IRON: /* Grey */
                color = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 115, 115, 115);
                break;
            case ITEM_CROP: /* Green */
                color = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 152, 251, 152);
                break;
            case ITEM_ANIMAL: /* Pink */
                color = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 220, 156, 219);
                break;
            default: /* Tan */
                color = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 210, 180, 140);
        }

        curr_rect.x = (i % WIDTH) * 10;
        curr_rect.y = (i / WIDTH) * 10;
        curr_rect.w = 10;
        curr_rect.h = 10;

        if (SDL_FillRect(SDL_GetWindowSurface(window), &curr_rect, color) < 0)
            die_sdl_error("SDL_FillRect()");
    }

    if (SDL_UpdateWindowSurface(window) < 0)
        die_sdl_error("SDL_UpdateWindowSurface()");
}

