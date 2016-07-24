#ifndef WORLD_H
#define WORLD_H

#include "econsim.h"

#define WIDTH 300
#define HEIGHT 300

#define MAX_AGENTS 20

struct shop {
    fann_type item_prices[N_ITEMS];
    int inventory[N_ITEMS];
    int space_remaining;
};

struct sector {
    double resource_densities[4];
    struct shop *shop; /* Max 1 per sector, NULL means no shop */
};

extern struct sector world[WIDTH*HEIGHT];

int sector_get_highest_resource(struct sector *sector);
void init_world();

#endif
