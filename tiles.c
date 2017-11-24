#include <stdio.h>
#include <SDL2/SDL.h>

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

char ***parse_csv(FILE* csv);

SDL_Surface* load_tile(SDL_Surface* tile_atlas, FILE* tile_catalog, int tile_id, int frame_count);
