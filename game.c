#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "window.h"
#include "game.h"
#include "controls.h"
#include "camera.h"
#include "character.h"

#include "tiles.h"

bool g_is_quitting = false;

void quit()
{
	g_is_quitting = true;
}

bool is_quitting()
{
	return g_is_quitting;
}

void handle_event(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_QUIT:
			quit();
			break;
		case SDL_KEYDOWN:
			handle_input(event.key);
			break;
		case SDL_KEYUP:
			handle_input(event.key);
		default:
			break;
	}
}

void play()
{
	SDL_Window *window = open_window(GAME_TITLE);
	SDL_Surface *window_surface = NULL;

	/* This is the representation of the gamescreen. It has the
	 * proper pixel dimensions. We will scale this surface to
	 * fit within the window. */
	SDL_Surface *game_screen = create_game_screen(SCREEN_WIDTH, SCREEN_HEIGHT);

	SDL_Surface *tile_atlas = load_resource(TILE_ATLAS_PATH);
	SDL_Surface *title_screen = load_resource(TITLE_SCREEN_PATH);
	region_t *region = create_region(0, tile_atlas);
	character_t *protagonist = character_init(100, 60, 16, 16);

	SDL_Event event;
	int frame_counter = 0;

	int x, y;
	bool is_on_title = true;
	while (!is_quitting())
	{
		while (SDL_PollEvent(&event) != 0)
		{
			handle_event(event);
		}

		window_surface = SDL_GetWindowSurface(window);
		SDL_FillRect(window_surface, NULL,
			     SDL_MapRGB(window_surface->format,
					0x00, 0x00, 0x00));
		SDL_FillRect(game_screen, NULL,
			     SDL_MapRGB(game_screen->format,
					0x00, 0x00, 0xff));

		//draw_region(0, game_screen, tile_atlas);

		move_camera(region);
		x = get_camera_x();
		y = get_camera_y();
		camera_view(region->surface, game_screen, x, y);
		
		draw_region(region, tile_atlas);
		control_character(protagonist);
		draw_character(protagonist, region);

		if (is_on_title && !is_button_pressed(BUTTON_START))
		{
			letterbox(title_screen, window_surface);
		}
		else if (is_button_pressed(BUTTON_SELECT))
		{
			quit();
		}
		else
		{
			is_on_title = false;
			letterbox(game_screen, window_surface);
		}

		//letterbox(game_screen, window_surface);
		//letterbox(title_screen, window_surface);
		//letterbox(region->surface, window_surface);
		SDL_UpdateWindowSurface(window);

		frame_counter++;
		SDL_Delay(1000 / DESIRED_FPS);
	}

	destroy_region(region);
	SDL_DestroyWindow(window);
	SDL_Quit();
}
