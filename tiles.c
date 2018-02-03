#include <stdlib.h>
#include <SDL2/SDL.h>
#include "tiles.h"

/* NOTE: I am not sure whether this will cause a memory leak due to the fact
 * that we're not destroying these SDL_Surface's. If a memory leak does happen,
 * then try to destroy the surface outside the function, right after it is
 * called (and after you're done doing whatever you need to do with it,
 * obviously). If that doesn't work, then rewrite the function in such a way
 * that you don't imprudently create surfaces.
 */
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

int *get_tile_layout(int region_id)
{
	char *file_contents;
	long file_size;
	FILE *file = NULL;
	if((file = fopen("regions/0", "r")) == NULL)
	{
		printf("Could not open regions file!\n");
		exit(-1);
	}

	fseek(file, 0, SEEK_END);
	file_size = ftell(file);
	rewind(file);
	file_contents = malloc(file_size * sizeof(char));
	fread(file_contents, sizeof(char), file_size, file);
	fclose(file);

	int *tile_layout;
	int tile_count = REGION_TILE_WIDTH * REGION_TILE_HEIGHT;
	tile_layout = malloc(tile_count * sizeof(int));

	char *token;
	token = strtok(file_contents, REGION_TILE_LAYOUT_DELIMITER);
	for(int i = 0; token != NULL; i++)
	{
		tile_layout[i] = atoi(token);
		token = strtok(NULL, REGION_TILE_LAYOUT_DELIMITER);
	}



/*
	for(int i = 0; i < tile_count; i++)
	{
		tile_layout[i] = atoi(strtok(file_contents, " \n\t"));
		printf("%i\n", tile_layout[i]);
	}
*/
//	return tile_layout;


	//return NULL;
	
	return tile_layout;
}

/*
#include <string.h>
#include <stdio.h>

int main () {
   char str[80] = "This is - www.tutorialspoint.com - website";
   const char s[2] = "-";
   char *token;

   get the first token
   token = strtok(str, s);

   walk through other tokens
   while( token != NULL ) {
      printf( " %s\n", token );

      token = strtok(NULL, s);
   }

   return(0);
}
*/

void draw_region(int region_id, SDL_Surface *game_screen, SDL_Surface *tile_atlas)
{
	int *tile_layout = get_tile_layout(region_id);

	SDL_Rect dst_rect;
	for(int i = 0; i < REGION_TILE_WIDTH * REGION_TILE_HEIGHT; i++)
	{
		int x_coordinate = i % REGION_TILE_WIDTH;
		int y_coordinate = i / REGION_TILE_WIDTH;
		x_coordinate *= TILE_PIXEL_WIDTH;
		y_coordinate *= TILE_PIXEL_HEIGHT;
		dst_rect.x = x_coordinate;
		dst_rect.y = y_coordinate;

		SDL_Surface *tile = NULL;
		tile = load_tile(tile_atlas, tile_layout[i]);
		SDL_BlitSurface(tile, NULL, game_screen, &dst_rect);
	}
}
