#include "include/econsim.h"

static void handle_key_event(SDL_Event *event) {
    switch(event->key.keysym.sym) {
        case SDLK_UP:
            scroll_up();
            break;
        case SDLK_DOWN:
            scroll_down();
            break;
        case SDLK_LEFT:
            scroll_left();
            break;
        case SDLK_RIGHT:
            scroll_right();
            break;
        case SDLK_z:
            zoom_in();
            break;
        case SDLK_x:
            zoom_out();
            break;
        case SDLK_q:
            quit_sdl();
            break;
    }
}

void handle_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit_sdl();
                break;
            case SDL_KEYDOWN:
                handle_key_event(&event);
                break;
        }
    }
}
