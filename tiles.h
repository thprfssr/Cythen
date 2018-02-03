#ifndef TILES_H
#define TILES_H

#include <stdio.h>
#include <SDL2/SDL.h>

#define TILE_PIXEL_WIDTH 16
#define TILE_PIXEL_HEIGHT 16

#define TILE_ATLAS_WIDTH_IN_TILES 16

#define REGION_TILE_WIDTH 16
#define REGION_TILE_HEIGHT 9

SDL_Surface *load_tile(SDL_Surface *tile_atlas, int tile_position);

#endif
