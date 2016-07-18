#include "include/econsim.h"

void die_sdl_error(const char *str) {
    fprintf(stderr, "%s: %s", str, SDL_GetError());
    quit_sdl();
}

void die_error(const char *str) {
    perror(str);
    quit_sdl();
}

void die_econsim_error(const char *str) {
    fprintf(stderr, str);
    quit_sdl();
}
