#include <SDL2/SDL.h>
#include "tiles.h"

SDL_Surface *load_tile(SDL_Surface *tile_atlas, int tile_position)
{
	int x_coordinate = tile_position % TILE_ATLAS_WIDTH_IN_TILES;
	int y_coordinate = tile_position / TILE_ATLAS_WIDTH_IN_TILES;
	x_coordinate *= TILE_PIXEL_WIDTH;
	y_coordinate *= TILE_PIXEL_HEIGHT;


	SDL_Rect src_rect;
	src_rect.x = x_coordinate;
	src_rect.y = y_coordinate;
	src_rect.w = TILE_PIXEL_WIDTH;
	src_rect.h = TILE_PIXEL_HEIGHT;

	SDL_Surface *dst_surface = SDL_CreateRGBSurface(0, TILE_PIXEL_WIDTH,
							TILE_PIXEL_HEIGHT, 32,
							0, 0, 0, 0);
	SDL_BlitSurface(tile_atlas, &src_rect, dst_surface, NULL);

	if(dst_surface == NULL)
	{
		SDL_Log("Could not load tile! SDL_Error: %s\n",
			SDL_GetError());
		exit(-1);
	}

	return dst_surface;
}
