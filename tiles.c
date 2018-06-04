#include <stdlib.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "tiles.h"

/* DISCUSSION: Each character is responsible for drawing itself in its region.
 * However, they draw themselves on a "dynamic layer" of the region. This is
 * nothing more than a transparent surface that will be overlayed over the
 * tiles of the region. And thus, the camera will show first the region tiles,
 * and then the dynamic surface.
 * Thus, each character has a region associated with it (and not the other way
 * around), but he is responsible for drawing himself in his region. */

/* NOTE: Whenever you call this function, remember to free the SDL_Surface */
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

/* NOTE: Whenever you call this function,
 * remember to destroy the region afterwards. */
/* NOTE: This function almost made me insane when I was debugging it.
 * Therefore, it's quite messy, so remember to clean it up in the future. */
region_t *create_region(int region_id, SDL_Surface *tile_atlas)
{
	region_t *region = malloc(sizeof(region_t));
	region->id = region_id;

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
	rewind(file);

	//region->height = get_line_count(file);
	//region->width = i / region->height;

	int *tile_layout = NULL;
	bool *walkability = NULL;
	size_t size_int = 0;
	size_t size_bool = 0;
	char *token;
	token = strtok(file_contents, REGION_TILE_LAYOUT_DELIMITER);
	int i = 0;
	while (token != NULL)
	{
		size_int += sizeof(int);
		tile_layout = realloc(tile_layout, size_int);
		tile_layout[i] = atoi(token);

		int x = tile_layout[i] % TILE_ATLAS_WIDTH_IN_TILES;
		int y = tile_layout[i] / TILE_ATLAS_WIDTH_IN_TILES;
		size_bool += sizeof(bool);
		walkability = realloc(walkability, size_bool);
		walkability[i] = ((x + y) % 2 == 1);
		token = strtok(NULL, REGION_TILE_LAYOUT_DELIMITER);
		i++;
	}

	region->height = get_line_count(file);
	region->width = i / region->height;
	region->layout = tile_layout;
	region->walkability = walkability;

	int region_pixel_width = region->width * TILE_PIXEL_WIDTH;
	int region_pixel_height = region->height * TILE_PIXEL_HEIGHT;
	region->background = SDL_CreateRGBSurface(0, region_pixel_width,
					      region_pixel_height,
					      32, 0, 0, 0, 0);
	draw_region_background(region, tile_atlas);

	/* region->foreground = SDL_CreateRGBSurface(0, region_pixel_width,
						  region_pixel_height,
						  32, 0, 0, 0, 0xFF); */

	region->ground = SDL_CreateRGBSurface(0, region_pixel_width,
					      region_pixel_height,
					      32, 0, 0, 0, 0);

	//update_region(region);
	//clear_region(region);

	fclose(file);
	free(file_contents);
	
	return region;
}

void draw_region_background(region_t *region, SDL_Surface *tile_atlas)
{
	SDL_Rect dst_rect;
	for(int i = 0; i < region->width * region->height; i++)
	{
		int x_coordinate = i % region->width;
		int y_coordinate = i / region->width;
		x_coordinate *= TILE_PIXEL_WIDTH;
		y_coordinate *= TILE_PIXEL_HEIGHT;
		dst_rect.x = x_coordinate;
		dst_rect.y = y_coordinate;

		SDL_Surface *tile = NULL;
		tile = load_tile(tile_atlas, region->layout[i]);
		SDL_BlitSurface(tile, NULL, region->background, &dst_rect);
		SDL_FreeSurface(tile);
	}
}

/*
void clear_foreground(region_t *region)
{
	SDL_FillRect(region->foreground, NULL,
		     SDL_MapRGBA(region->foreground->format, 0, 0, 0, 0xFF));
}
*/

/* This function draws the background and foreground on the ground surface. */
//void update_region(region_t *region)
//{
	/*
	SDL_SetSurfaceBlendMode(region->foreground, SDL_BLENDMODE_BLEND);
	SDL_SetSurfaceBlendMode(region->ground, SDL_BLENDMODE_BLEND);
	*/
//	SDL_BlitSurface(region->background, NULL, region->ground, NULL);
	//SDL_BlitSurface(region->foreground, NULL, region->ground, NULL);
//}

void clear_region(region_t *region)
{
	SDL_BlitSurface(region->background, NULL, region->ground, NULL);
}

void destroy_region(region_t *region)
{
	free(region->layout);
	SDL_FreeSurface(region->background);
	SDL_FreeSurface(region->ground);
}

int get_line_count(FILE *file)
{
	if (file == NULL)
	{
		printf("File is NULL!\n");
	}

	char ch;
	int i = 0;
	while (!feof(file))
	{
		ch = fgetc(file);
		if(ch == '\n')
		{
			i++;
		}
	}

	return i;
}
