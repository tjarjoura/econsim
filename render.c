#include "include/econsim.h"

SDL_Window *window;
SDL_Surface *world_surface;
SDL_Rect view_rect;

void quit_sdl() {
    SDL_DestroyWindow(window);
    SDL_Quit();
    exit(1);
}

void init_graphics() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
        die_sdl_error("SDL_Init()");

    if ((window = SDL_CreateWindow("Economy Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                  SCREEN_WIDTH, SCREEN_HEIGHT, 0)) == NULL)
        die_sdl_error("SDL_CreateWindow()");

    if ((world_surface = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0)) == NULL)
        die_sdl_error("SDL_CreateRGBSurface()");

    view_rect.x = 0;
    view_rect.y = 0;
    view_rect.w = 50;
    view_rect.h = 50;
}

void scroll_left() {
    if (view_rect.x > 0)
        --view_rect.x;
}

void scroll_right() {
    if ((view_rect.x + view_rect.w) < (WIDTH-1))
        ++view_rect.x;
}

void scroll_up() {
    if (view_rect.y > 0)
        --view_rect.y;
}

void scroll_down() {
    if ((view_rect.y + view_rect.h) < (HEIGHT-1))
        ++view_rect.y;
}

void zoom_in() {
    if (view_rect.w > 1 && view_rect.h > 1) {
        --view_rect.w;
        --view_rect.h;
    }
}

void zoom_out() {
    if (view_rect.w < (WIDTH - 1) && view_rect.h < (HEIGHT - 1)) {
        ++view_rect.w;
        ++view_rect.h;
    }

    if (view_rect.x + view_rect.w >= WIDTH)
        view_rect.x = WIDTH - view_rect.w - 1;

    if (view_rect.y + view_rect.h >= HEIGHT)
        view_rect.y = HEIGHT - view_rect.h - 1;
}

void render() {
    uint32_t *pixels = world_surface->pixels;

    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        int highest_resource = sector_get_highest_resource(&world[i]);

        switch (highest_resource) {
            case ITEM_WOOD: /* Brown */
                pixels[i] = SDL_MapRGB(world_surface->format, 187, 153, 102);
                break;
            case ITEM_IRON: /* Grey */
                pixels[i] = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 115, 115, 115);
                break;
            case ITEM_CROP: /* Green */
                pixels[i] = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 152, 251, 152);
                break;
            case ITEM_ANIMAL: /* Pink */
                pixels[i] = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 220, 156, 219);
                break;
            default: /* Tan */
                pixels[i] = SDL_MapRGB(SDL_GetWindowSurface(window)->format, 210, 180, 140);
        }
    }

    if (SDL_BlitScaled(world_surface, &view_rect, SDL_GetWindowSurface(window), NULL) < 0)
        die_sdl_error("SDL_BlitScaled()");

    if (SDL_UpdateWindowSurface(window) < 0)
        die_sdl_error("SDL_UpdateWindowSurface()");
}

