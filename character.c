#include <SDL2/SDL.h>
#include "tiles.h"
#include "character.h"
#include "controls.h"

character_t *create_character(double x, double y, int h, int w)
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
	rect->x = (int) floor(character->x);
	rect->y = (int) floor(character->y);
	rect->h = character->h;
	rect->w = character->w;

	SDL_FillRect(region->ground, rect, SDL_MapRGB(region->ground->format,
						       0x00, 0x00, 0x00));


}

void move_character_up(character_t *character)
{
	character->y -= CHARACTER_SPEED;
}

void move_character_down(character_t *character)
{
	character->y += CHARACTER_SPEED;
}

void move_character_left(character_t *character)
{
	character->x -= CHARACTER_SPEED;
}

void move_character_right(character_t *character)
{
	character->x += CHARACTER_SPEED;
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
