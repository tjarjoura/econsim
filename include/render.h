#ifndef RENDER_H
#define RENDER_H

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 1200

void init_graphics();
void render();
void quit_sdl();

void scroll_up();
void scroll_down();
void scroll_left();
void scroll_right();

void zoom_in();
void zoom_out();

#endif
