#include <SDL2/SDL.h>
#include "tiles.h"
#include "character.h"
#include "controls.h"

character_t *character_init(int x, int y, int h, int w)
{
	character_t *character = malloc(sizeof(character_t));
	character->x = x;
	character->y = y;
	character->h = h;
	character->w = w;

	return character;
}

void draw_character(character_t *character, region_t *region)
{
	SDL_Rect *rect = malloc(sizeof(SDL_Rect));
	rect->x = character->x;
	rect->y = character->y;
	rect->h = character->h;
	rect->w = character->w;

	SDL_FillRect(region->surface, rect, SDL_MapRGB(region->surface->format,
						       0x00, 0x00, 0x00));

	//SDL_FillRect(region->surface, NULL, SDL_MapRGB(region->surface->format,
	//					       0x00, 0x00, 0x00));
	/*
	SDL_FillRect(window_surface, NULL,
			     SDL_MapRGB(window_surface->format,
					0x00, 0x00, 0x00));
		SDL_FillRect(game_screen, NULL,
			     SDL_MapRGB(game_screen->format,
					0x00, 0x00, 0xff));	
					*/
}

void move_character_up(character_t *character)
{
	character->y--;
}

void move_character_down(character_t *character)
{
	character->y++;
}

void move_character_left(character_t *character)
{
	character->x--;
}

void move_character_right(character_t *character)
{
	character->x++;
}

void control_character(character_t *character)
{
	if (is_button_pressed(BUTTON_UP))
		move_character_up(character);
	if (is_button_pressed(BUTTON_DOWN))
		move_character_down(character);
	if (is_button_pressed(BUTTON_LEFT))
		move_character_left(character);
	if (is_button_pressed(BUTTON_RIGHT))
		move_character_right(character);
}
