#include <stdbool.h>
#include <SDL2/SDL.h>
#include "tiles.h"
#include "character.h"
#include "controls.h"
#include "camera.h"

character_t *create_character(double x, double y, int h, int w, int hitbox_x,
			      int hitbox_y, int hitbox_w, int hitbox_h)
{
	character_t *character = malloc(sizeof(character_t));
	character->x = x;
	character->y = y;
	character->h = h;
	character->w = w;
	character->hitbox_x = hitbox_x;
	character->hitbox_y = hitbox_y;
	character->hitbox_w = hitbox_w;
	character->hitbox_h = hitbox_h;

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
void control_character(character_t *character, region_t *region)
{
	bool up = is_button_pressed(BUTTON_UP);
	bool down = is_button_pressed(BUTTON_DOWN);
	bool left = is_button_pressed(BUTTON_LEFT);
	bool right = is_button_pressed(BUTTON_RIGHT);
	
	int buttons = (up << 0) | (down << 1) | (left << 2) | (right << 3);

	switch (buttons)
	{
		case UP:
			if (~character_collision(character, region, UP))
				character->y -= CHARACTER_SPEED;
			break;
		case DOWN:
			if (~character_collision(character, region, DOWN))
				character->y += CHARACTER_SPEED;
			break;
		case LEFT:
			if (~character_collision(character, region, LEFT))
				character->x -= CHARACTER_SPEED;
			break;
		case RIGHT:
			if (~character_collision(character, region, RIGHT))
				character->x += CHARACTER_SPEED;
			break;
		case UP | LEFT:
			if (~character_collision(character, region, LEFT))
				character->x -= CHARACTER_SPEED / sqrt(2);
			if (~character_collision(character, region, UP))
				character->y -= CHARACTER_SPEED / sqrt(2);
			break;
		case UP | RIGHT:
			if (~character_collision(character, region, RIGHT))
				character->x += CHARACTER_SPEED / sqrt(2);
			if (~character_collision(character, region, UP))
				character->y -= CHARACTER_SPEED / sqrt(2);
			break;
		case DOWN | LEFT:
			if (~character_collision(character, region, LEFT))
				character->x -= CHARACTER_SPEED / sqrt(2);
			if (~character_collision(character, region, DOWN))
				character->y += CHARACTER_SPEED / sqrt(2);
			break;
		case DOWN | RIGHT:
			if (~character_collision(character, region, RIGHT))
				character->x += CHARACTER_SPEED / sqrt(2);
			if (~character_collision(character, region, DOWN))
				character->y += CHARACTER_SPEED / sqrt(2);
			break;
		case DOWN | LEFT | RIGHT:
			if (~character_collision(character, region, DOWN))
				character->y += CHARACTER_SPEED / sqrt(2);
			break;
		case UP | LEFT | RIGHT:
			if (~character_collision(character, region, UP))
				character->y -= CHARACTER_SPEED / sqrt(2);
			break;
		case UP | DOWN | RIGHT:
			if (~character_collision(character, region, RIGHT))
				character->x += CHARACTER_SPEED / sqrt(2);
			break;
		case UP | DOWN | LEFT:
			if (~character_collision(character, region, LEFT))
				character->x -= CHARACTER_SPEED / sqrt(2);
			break;
		default:
			break;
	}
/*
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
*/
}

bool character_collision(character_t *character, region_t *region, int direction)
{
	/* Here are the four sides of the hitbox. */
	int hitbox_up = character_get_y(character) + character->hitbox_y;
	int hitbox_down = hitbox_up + character->hitbox_h;
	int hitbox_left = character_get_x(character) + character->hitbox_x;
	int hitbox_right = hitbox_left + character->hitbox_w;

	/* And here we "scale down" the coordinates so that we can work with
	 * tile collisions. */
	int up = hitbox_up / TILE_PIXEL_HEIGHT;
	int down = hitbox_down / TILE_PIXEL_HEIGHT;
	int left = hitbox_left / TILE_PIXEL_WIDTH;
	int right = hitbox_right / TILE_PIXEL_WIDTH;

	bool tmp = false;
	/* We check the corners of the hitbox to see whether they are on an
	 * unwalkable tile. */
	switch (direction)
	{
		case UP:
			tmp = tmp || ~get_walkability(region, left, up);
			tmp = tmp || ~get_walkability(region, right, up);
			return tmp;
		case DOWN:
			tmp = tmp || ~get_walkability(region, left, down);
			tmp = tmp || ~get_walkability(region, right, down);
			return tmp;
		case LEFT:
			tmp = tmp || ~get_walkability(region, left, up);
			tmp = tmp || ~get_walkability(region, left, down);
			return tmp;
		case RIGHT:
			tmp = tmp || ~get_walkability(region, right, up);
			tmp = tmp || ~get_walkability(region, right, down);
			return tmp;
	}
}
