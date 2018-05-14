#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "tiles.h"
#include "character.h"

#define UP	(1 << 0)
#define DOWN	(1 << 1)
#define LEFT	(1 << 2)
#define RIGHT	(1 << 3)

//int g_camera_x_coordinate;
//int g_camera_y_coordinate;

typedef struct
{
	int x;
	int y;
	region_t *region;
	character_t *character;
	SDL_Surface *surface;

	/* This is a bit field that tells us if the camera is colliding against
	 * the boundaries of the region. */
	//int collision;
} camera_t;

camera_t *create_camera(region_t *region, int x, int y, character_t *character);
void move_camera(camera_t *camera, int direction);
//void update_camera_collision(camera_t *camera);
bool camera_collision(camera_t *camera, int direction);
void camera_view(camera_t *camera, SDL_Surface *game_screen);


//void camera_view(SDL_Surface *src, SDL_Surface *dst, int x, int y);
//int get_camera_x();
//int get_camera_y();
//void set_camera_position(int x, int y);
//void move_camera(region_t *region);

//bool is_camera_colliding_up(region_t *region);
//bool is_camera_colliding_down(region_t *region);
//bool is_camera_colliding_left(region_t *region);
//bool is_camera_colliding_right(region_t *region);

#endif
