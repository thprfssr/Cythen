#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define TILE_PIXEL_WIDTH 16
#define TILE_PIXEL_HEIGHT 16

#define TILE_ATLAS_WIDTH_IN_TILES 16

#define REGION_TILE_WIDTH 16
#define REGION_TILE_HEIGHT 9

#define REGION_TILE_LAYOUT_DELIMITER " \n\t"

typedef struct
{
	int id;
	int width_in_tiles;
	int height_in_tiles;
	int *layout;
	SDL_Surface surface;
} region_t;

void destroy_region(region_t region);

SDL_Surface *load_tile(SDL_Surface *tile_atlas, int tile_position);
int *get_tile_layout(int region_id);
void draw_region(int region_id, SDL_Surface *game_screen, SDL_Surface *tile_atlas);

int get_line_count(char *file_name);

#endif
