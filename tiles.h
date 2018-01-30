#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

SDL_Surface* load_tile(SDL_Surface* tile_atlas, FILE* tile_catalog,
		       int tile_id, int frame_count);

#endif
