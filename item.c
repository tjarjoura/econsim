#include "include/econsim.h"

struct item items[12] = {
    { .name = "Wood", .required = {0}},
    { .name = "Iron", .required = {0}},
    { .name = "Crop", .required = {0}},
    { .name = "Animal", .required = {0}},
    { .name = "Axe", .required = {0}},
    { .name = "Knife", .required = {0}},
    { .name = "Shovel", .required = {0}},
    { .name = "Sickle", .required = {0}},
    { .name = "Vegetable", .required = {0}},
    { .name = "Meat", .required = {0}},
    { .name = "Oven", .required = {0}},
    { .name = "Hammer", .required = {0}},
};

void init_items() {
    items[ITEM_WOOD].required[ITEM_AXE] = 1;

    items[ITEM_IRON].required[ITEM_SHOVEL] = 1;

    items[ITEM_CROP].required[ITEM_SICKLE] = 1;

    items[ITEM_ANIMAL].required[ITEM_KNIFE] = 1;

    items[ITEM_AXE].required[ITEM_WOOD] = 5;
    items[ITEM_AXE].required[ITEM_IRON] = 3;

    items[ITEM_SHOVEL].required[ITEM_WOOD] = 5;
    items[ITEM_SHOVEL].required[ITEM_IRON] = 3;

    items[ITEM_SICKLE].required[ITEM_WOOD] = 5;
    items[ITEM_SICKLE].required[ITEM_IRON] = 3;

    items[ITEM_VEGETABLE].required[ITEM_CROP] = 1;
    items[ITEM_VEGETABLE].required[ITEM_COOKER] = 1;

    items[ITEM_MEAT].required[ITEM_ANIMAL] = 1;
    items[ITEM_MEAT].required[ITEM_COOKER] = 1;

    items[ITEM_COOKER].required[ITEM_WOOD] = 2;
    items[ITEM_COOKER].required[ITEM_IRON] = 5;
}

