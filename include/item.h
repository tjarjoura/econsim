#ifndef ITEM_H
#define ITEM_H

#define N_ITEMS 12

#define ITEM_WOOD 0
#define ITEM_IRON 1
#define ITEM_CROP 2
#define ITEM_ANIMAL 3
#define ITEM_AXE 4
#define ITEM_KNIFE 5
#define ITEM_SHOVEL 6
#define ITEM_SICKLE 7
#define ITEM_VEGETABLE 8
#define ITEM_MEAT 9
#define ITEM_COOKER 10
#define ITEM_HAMMER 11

#include "econsim.h"

struct item {
    const char name[20];
    int required[N_ITEMS]; /* Amount of each item required to make or harvest this */
};

extern struct item items[];

void init_items();

#endif
