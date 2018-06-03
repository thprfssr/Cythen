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

int character_get_x(character_t *character)
{
	return (int) round(character->x);
}

int character_get_y(character_t *character)
{
	return (int) round(character->y);
}

void draw_character(character_t *character, region_t *region)
{
	SDL_Rect *rect = malloc(sizeof(SDL_Rect));
	rect->x = character_get_x(character);
	rect->y = character_get_y(character);
	rect->h = character->h;
	rect->w = character->w;

	SDL_FillRect(region->ground, rect, SDL_MapRGB(region->ground->format,
						       0x00, 0x00, 0x00));


}
/*
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

void move_character_up_right(character_t *character)
{
	character->x += CHARACTER_SPEED / sqrt(2);
	character->y -= CHARACTER_SPEED / sqrt(2);
}

void move_character_up_left(character_t *character)
{
	character->x -= CHARACTER_SPEED / sqrt(2);
	character->y -= CHARACTER_SPEED / sqrt(2);
}

void move_character_down_right(character_t *character)
{
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
*/
void control_character(character_t *character)
{
	bool up = is_button_pressed(BUTTON_UP);
	bool down = is_button_pressed(BUTTON_DOWN);
	bool left = is_button_pressed(BUTTON_LEFT);
	bool right = is_button_pressed(BUTTON_RIGHT);

	if (up && left)
	{
		character->x -= CHARACTER_SPEED / sqrt(2);
		character->y -= CHARACTER_SPEED / sqrt(2);
	}
	else if (up && right)
	{
		character->x += CHARACTER_SPEED / sqrt(2);
		character->y -= CHARACTER_SPEED / sqrt(2);
	}
	else if (down && left)
	{
		character->x -= CHARACTER_SPEED / sqrt(2);
		character->y += CHARACTER_SPEED / sqrt(2);
	}	
	else if (down && right)
	{
		character->x += CHARACTER_SPEED / sqrt(2);
		character->y += CHARACTER_SPEED / sqrt(2);
	}
	else
	{
		if (up)
			character->y -= CHARACTER_SPEED;
		if (down)
			character->y += CHARACTER_SPEED;
		if (left)
			character->x -= CHARACTER_SPEED;
		if (right)
			character->x += CHARACTER_SPEED;
	}
}
