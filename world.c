#include "include/econsim.h"

#define DROP_RADIUS 3

struct sector world[WIDTH*HEIGHT];

int sector_get_highest_resource(struct sector *sector) {
    fann_type max = 0.0;
    int max_idx = -1;

    for (int i = 0; i < 4; i++) {
        if (sector->resource_densities[i] > max) {
            max = sector->resource_densities[i];
            max_idx = i;
        }
    }

    return max_idx;
}

int height_map_get_random_neighbor(int *height_map, int drop_point) {
    int possible_neighbors[DROP_RADIUS*8]; /* 8 directions */
    int n = 0;

    for (int i = 1; i <= DROP_RADIUS; i++) { /* left */
        if ((drop_point % WIDTH <= (i-1)) ||
            (height_map[drop_point - i] >= height_map[drop_point - (i-1)]))
            break;

        possible_neighbors[n++] = drop_point - i;
    }

    for (int i = 1; i <= DROP_RADIUS; i++) { /* right */
        if ((drop_point % WIDTH >= (WIDTH - i)) ||
            (height_map[drop_point + i] >= height_map[drop_point + (i-1)]))
            fprintf(stderr, "fail\n");
            break;

        possible_neighbors[n++] = drop_point + i;
    }

    for (int i = 1; i <= DROP_RADIUS; i++) { /* top */
        if (drop_point / WIDTH <= i - 1 ||
           (height_map[drop_point - i*WIDTH] >= height_map[drop_point - (i-1)*WIDTH]))
            break;

        possible_neighbors[n++] = drop_point - i*WIDTH;
    }

    for (int i = 1; i <= DROP_RADIUS; i++) { /* down */
        if (((drop_point / WIDTH) >= (HEIGHT - i)) ||
            (height_map[drop_point + i*WIDTH] >= height_map[drop_point + (i-1)*WIDTH]))
            break;

        possible_neighbors[n++] = drop_point + i*WIDTH;
    }

    for (int i = 1; i <= DROP_RADIUS; i++) { /* up-left */
        if (((drop_point % WIDTH) <= (i-1)) || ((drop_point / WIDTH) <= (i-1)) ||
            (height_map[drop_point - i*(WIDTH+1)] >= height_map[drop_point - (i-1)*(WIDTH+1)]))
            break;

        possible_neighbors[n++] = drop_point - i*(WIDTH+1);
    }

    for (int i = 1; i <= DROP_RADIUS; i++) { /* up-right */
        if (drop_point % WIDTH >= WIDTH - i || drop_point / WIDTH <= i - 1 ||
            height_map[drop_point - i*(WIDTH-1)] >= height_map[drop_point - (i-1)*(WIDTH-1)])
            break;

        possible_neighbors[n++] = drop_point + i*(WIDTH-1);
    }

    for (int i = 1; i <= DROP_RADIUS; i++) { /* down-left */
        if (drop_point % WIDTH <= i - 1 || drop_point / WIDTH >= HEIGHT - i ||
            height_map[drop_point + i*(WIDTH-1)] >= height_map[drop_point + (i-1)*(WIDTH-1)])
            break;

        possible_neighbors[n++] = drop_point - i*(WIDTH+1);
    }

    for (int i = 1; i <= DROP_RADIUS; i++) { /* down-right */
        if (drop_point % WIDTH >= WIDTH - i || drop_point / WIDTH >= HEIGHT - i ||
            height_map[drop_point + i*(WIDTH+1)] >= height_map[drop_point + (i-1)*(WIDTH+1)])
            break;

        possible_neighbors[n++] = drop_point + i*(WIDTH-1);
    }

    if (n <= 0)
        die_econsim_error("height_map_get_random_neighbor(): could not find any suitable neighbors\n");

    return possible_neighbors[randrange(0, n-1)];
}

int height_map_check_stability(int *height_map, int drop_point) {
    if (((drop_point % WIDTH) > 0) && (height_map[drop_point-1] < height_map[drop_point]))
        return 0; /* Left neighbor */

    if (((drop_point % WIDTH) < WIDTH-1) && (height_map[drop_point+1] < height_map[drop_point]))
        return 0; /* Right neighbor */

    if (((drop_point / WIDTH) > 0) && (height_map[drop_point-WIDTH] < height_map[drop_point]))
        return 0; /* Up neighbor */

    if (((drop_point / WIDTH) < HEIGHT-1) && (height_map[drop_point+WIDTH] < height_map[drop_point]))
        return 0; /* Down neighbor */

    if (((drop_point % WIDTH) > 0) && ((drop_point / WIDTH) > 0) &&
         (height_map[drop_point-(WIDTH+1)] < height_map[drop_point]))
        return 0; /* Up left neighbor */

    if (((drop_point % WIDTH) < WIDTH-1) && ((drop_point / WIDTH) < HEIGHT-1) &&
         (height_map[drop_point+(WIDTH+1)] < height_map[drop_point]))
        return 0; /* Down right neighbor */

    if (((drop_point % WIDTH) > 0) && ((drop_point / WIDTH) < HEIGHT-1) &&
         (height_map[drop_point+(WIDTH-1)] < height_map[drop_point]))
        return 0; /* Down left neighbor */

    if (((drop_point % WIDTH) < WIDTH-1) && ((drop_point / WIDTH) > 0) &&
         (height_map[drop_point-(WIDTH-1)] < height_map[drop_point]))
        return 0; /* Up right neighbor */

    return 1;
}

void get_height_map(int *height_map) {
    int drop_point, n_drops, drop_neighbor;

    memset(height_map, 0, sizeof(int) * WIDTH * HEIGHT);

    for (int i = 0; i < 1800; i++) {
        drop_point = randrange(0, WIDTH*HEIGHT - 1);
        n_drops = randrange(20, 30);

        for (int j = 0; j < n_drops; j++) {
            if (!height_map_check_stability(height_map, drop_point)) {
                drop_neighbor = height_map_get_random_neighbor(height_map, drop_point);
                //fprintf(stderr, "random neighbor: %d\n", drop_neighbor);
                height_map[drop_neighbor]++;
            } else {
                height_map[drop_point]++;
            }
        }
    }

}

void print_height_map(int *height_map) {
    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        if (i > 0 && i % 50 == 0)
            putchar('\n');
        if (i > 0 && i % WIDTH == 0)
            printf("\n\n");

        printf("%02d ", height_map[i]);
    }
}

void init_world() {
    int *height_map = (int *) malloc(sizeof(int) * WIDTH * HEIGHT);

    get_height_map(height_map);


    for (int i = 0; i < WIDTH*HEIGHT; i++) {
        if (height_map[i] < 10) {
            world[i].resource_densities[ITEM_WOOD] = randfrange(.3, .4);
            world[i].resource_densities[ITEM_IRON] = randfrange(.1, .2);
            world[i].resource_densities[ITEM_CROP] = randfrange(.8, .9);
            world[i].resource_densities[ITEM_ANIMAL] = randfrange(.4, .5);
        } else if (height_map[i] >= 10 && height_map[i] < 20) {
            world[i].resource_densities[ITEM_WOOD] = randfrange(.4, .5);
            world[i].resource_densities[ITEM_IRON] = randfrange(.1, .2);
            world[i].resource_densities[ITEM_CROP] = randfrange(.8, .9);
            world[i].resource_densities[ITEM_ANIMAL] = randfrange(.1, .2);
        } else if (height_map[i] >= 20 && height_map[i] < 30) {
            world[i].resource_densities[ITEM_WOOD] = randfrange(.4, .6);
            world[i].resource_densities[ITEM_IRON] = randfrange(.1, .2);
            world[i].resource_densities[ITEM_CROP] = randfrange(.2, .3);
            world[i].resource_densities[ITEM_ANIMAL] = randfrange(.8, .9);
        } else if (height_map[i] >= 30 && height_map[i] < 40) {
            world[i].resource_densities[ITEM_WOOD] = randfrange(.8, .9);
            world[i].resource_densities[ITEM_IRON] = randfrange(.6, .7);
            world[i].resource_densities[ITEM_CROP] = randfrange(.1, .2);
            world[i].resource_densities[ITEM_ANIMAL] = randfrange(.3, .4);
        } else {
            world[i].resource_densities[ITEM_WOOD] = randfrange(.3, .4);
            world[i].resource_densities[ITEM_IRON] = randfrange(.8, .9);
            world[i].resource_densities[ITEM_CROP] = randfrange(.1, .2);
            world[i].resource_densities[ITEM_ANIMAL] = randfrange(.1, .2);
        }
    }

    //print_height_map(height_map);
    printf("hi\n");
    printf("height-map: %p\n", height_map);
    free(height_map);
}
