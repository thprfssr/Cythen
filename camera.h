#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "tiles.h"

int g_camera_x_coordinate;
int g_camera_y_coordinate;

void camera_view(SDL_Surface *src, SDL_Surface *dst, int x, int y);
int get_camera_x();
int get_camera_y();
void set_camera_position(int x, int y);
void move_camera(region_t *region);

#endif
