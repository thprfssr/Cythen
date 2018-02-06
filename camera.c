#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "camera.h"
#include "controls.h"
#include "tiles.h"

int g_camera_x_coordinate = 0;
int g_camera_y_coordinate = 0;

int get_camera_x()
{
	return g_camera_x_coordinate;
}

int get_camera_y()
{
	return g_camera_y_coordinate;
}

void set_camera_position(int x, int y)
{
	g_camera_x_coordinate = x;
	g_camera_y_coordinate = y;
}

void move_camera(region_t *region)
{
	int x = get_camera_x();
	int y = get_camera_y();
	int w = region->width * TILE_PIXEL_WIDTH;
	int h = region->height * TILE_PIXEL_HEIGHT;
	if (is_button_pressed(BUTTON_UP) && y > 0)
		y--;
	if (is_button_pressed(BUTTON_DOWN) && y + SCREEN_HEIGHT < h)
		y++;
	if (is_button_pressed(BUTTON_LEFT) && x > 0)
		x--;
	if (is_button_pressed(BUTTON_RIGHT) && x + SCREEN_WIDTH < w)
		x++;
	
	set_camera_position(x, y);
}

/* Since regions are usually larger than our gamescreen, we can only show
 * part of them. Assuming that dst is our gamescreen, a.k.a. our "camera",
 * this function places the camera over the region (which is assumed to
 * be src) such that the camera's top right corner is in the position
 * (x,y) with respect to the region. */
void camera_view(SDL_Surface *src, SDL_Surface *dst, int x, int y)
{
	SDL_Rect src_rect;
	src_rect.x = x;
	src_rect.y = y;
	src_rect.w = SCREEN_WIDTH;
	src_rect.h = SCREEN_HEIGHT;

	SDL_BlitSurface(src, &src_rect, dst, NULL);
}
