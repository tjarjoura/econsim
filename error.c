#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include <SDL2/SDL.h>

#include "include/render.h"

void die_sdl_error(const char *str) {
    fprintf(stderr, "%s: %s", str, SDL_GetError());
    quit_sdl();
}

void die_error(const char *str) {
    perror(str);
    quit_sdl();
}

