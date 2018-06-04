#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define TILE_PIXEL_WIDTH 16
#define TILE_PIXEL_HEIGHT 16

#define TILE_ATLAS_WIDTH_IN_TILES 16

#define REGION_TILE_LAYOUT_DELIMITER " \n\t"

typedef struct
{
	int id;
	int width;
	int height;
	int *layout;
	int *walkability;
	SDL_Surface *background; //This is where the tiles are drawn.
	//SDL_Surface *foreground; //This is where the entities go.
	SDL_Surface *ground;
	/* The ground is the surface shown to the player, being the surface in
	 * which both the background and foreground are shown. */
} region_t;

region_t *create_region(int region_id, SDL_Surface *tile_atlas);
void draw_region_background(region_t *region, SDL_Surface *tile_atlas);
//void update_region(region_t *region);
void clear_region(region_t *region);
void destroy_region(region_t *region);

SDL_Surface *load_tile(SDL_Surface *tile_atlas, int tile_position);

int get_line_count(FILE *file);


#endif
