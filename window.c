#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"

SDL_Window *open_window(const char *name)
{
	SDL_Window *window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL could not initialize! SDL_Error: %s\n",
			SDL_GetError());
		exit(-1);
	}
	else
	{
		Uint32 window_flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE;
		window = SDL_CreateWindow(name,
					  SDL_WINDOWPOS_UNDEFINED,
					  SDL_WINDOWPOS_UNDEFINED,
					  300, 300,
					  window_flags);

		if (window == NULL)
		{
			SDL_Log("Window could not be created! SDL_Error: %s\n",
			       SDL_GetError());
			exit(-1);
		}
		else
		{
			SDL_SetWindowMinimumSize(window, 200, 200);

			int img_flags = IMG_INIT_PNG;
			if (!(IMG_Init(img_flags) & img_flags))
			{
				SDL_Log("SDL_image could not initialize! SDL_image error: %s\n",
					IMG_GetError());
				exit(-1);
			}
		}
	}

	return window;
}

SDL_Surface *create_game_screen(int pixel_width, int pixel_height)
{
	SDL_Surface *surface = NULL;
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
#endif

	surface = SDL_CreateRGBSurface(0, pixel_width, pixel_height, 32,
				       rmask, gmask, bmask, amask);
	if (surface == NULL)
	{
		SDL_Log("SDL_CreateRGBSurface() failed: %s\n",
			SDL_GetError());
		exit(-1);
	}

	return surface;
}

SDL_Surface *load_resource(char *path)
{
	SDL_Surface *surface = IMG_Load(path);
	if (surface == NULL)
	{
		SDL_Log("Unable to load image %s ! SDL_image error: %s\n",
			path, IMG_GetError());
		exit(-1);
	}

	return surface;
}

/* This function scales 'src' to its maximum possible size
 * inside 'dst', while preserving its aspect ratio,
 * giving a letterbox effect.
 */
void letterbox(SDL_Surface *src, SDL_Surface *dst)
{
	double src_w = (double) src->w;
	double src_h = (double) src->h;
	double dst_w = (double) dst->w;
	double dst_h = (double) dst->h;

	double src_ratio = src_w / src_h;
	double dst_ratio = dst_w / dst_h;

	double new_w, new_h;
	int new_x, new_y;

	if (dst_ratio == src_ratio)
	{
		new_w = dst_w;
		new_h = dst_h;

		new_x = 0;
		new_y = 0;
	}
	else if (dst_ratio < src_ratio)
	{
		new_w = dst_w;
		new_h = new_w / src_ratio;

		new_x = 0;
		new_y = (int) round((dst_h - new_h) / 2);
	}
	else if (dst_ratio > src_ratio)
	{
		new_h = dst_h;
		new_w = new_h * src_ratio;

		new_x = (int) round((dst_w - new_w) / 2);
		new_y = 0;
	}

	SDL_Rect rect;
	rect.x = new_x;
	rect.y = new_y;
	rect.w = new_w;
	rect.h = new_h;

	SDL_BlitScaled(src, NULL, dst, &rect);
}
