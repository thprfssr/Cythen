#include <stdbool.h>
#include <SDL2/SDL.h>
#include "game.h"
#include "camera.h"
#include "controls.h"
#include "tiles.h"

/*
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
	if (is_button_pressed(BUTTON_UP) && !is_camera_colliding_up(region))//y > 0)
		y--;
	if (is_button_pressed(BUTTON_DOWN) && !is_camera_colliding_down(region))//y + SCREEN_HEIGHT < h)
		y++;
	if (is_button_pressed(BUTTON_LEFT) && !is_camera_colliding_left(region))//x > 0)
		x--;
	if (is_button_pressed(BUTTON_RIGHT) && !is_camera_colliding_right(region))//x + SCREEN_WIDTH < w)
		x++;
	
	set_camera_position(x, y);
}
*/

camera_t *create_camera(region_t *region, double x, double y, character_t *character)
{
	camera_t *camera = malloc(sizeof(camera_t));

	camera->region = region;
	camera->character = character;
	camera->x = x;
	camera->y = y;

	camera->surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT,
					       32, 0, 0, 0, 0);

	return camera;
}

int camera_get_x(camera_t *camera)
{
	return (int) round(camera->x);
}

int camera_get_y(camera_t *camera)
{
	return (int) round(camera->y);
}

void move_camera(camera_t *camera, int direction)
{
	switch (direction)
	{
		case UP:
			camera->y--;
			break;
		case DOWN:
			camera->y++;
			break;
		case LEFT:
			camera->x--;
			break;
		case RIGHT:
			camera->x++;
			break;
	}
}

/*
void update_camera_collision(camera_t *camera)
{
	Just declaring these for simplicity *
	int x = camera->x;
	int y = camera->y;
	int hs = SCREEN_HEIGHT;
	int ws = SCREEN_WIDTH;
	int hr = camera->region->height * TILE_PIXEL_HEIGHT;
	int wr = camera->region->width * TILE_PIXEL_WIDTH;

	* This takes care of deciding whether the camera collides
	 * up, down, left, or right. *
	(y <= 0) ? (camera->collision |= UP) : (camera->collision &= ~UP);
	(y + hs == hr) ? (camera->collision |= DOWN) : (camera->collision &= ~DOWN);
	(x <= 0) ? (camera->collision |= LEFT) : (camera->collision &= ~LEFT);
	(x + ws == wr) ? (camera->collision |= RIGHT) : (camera->collision &= ~RIGHT);
}
*/

bool camera_collision(camera_t *camera, int direction)
{
	/* Just declaring these for simplicity. */
	int x = camera_get_x(camera);
	int y = camera_get_y(camera);
	int hs = SCREEN_HEIGHT;
	int ws = SCREEN_WIDTH;
	int hr = camera->region->height * TILE_PIXEL_HEIGHT;
	int wr = camera->region->width * TILE_PIXEL_WIDTH;
	int collision = 0;

	/* This takes care of deciding which side of the camera is colliding
	 * against the region, and it puts that information in the collision
	 * bit field. */
	(y <= 0) ? (collision |= UP) : (collision &= ~UP);
	(y + hs >= hr) ? (collision |= DOWN) : (collision &= ~DOWN);
	(x <= 0) ? (collision |= LEFT) : (collision &= ~LEFT);
	(x + ws >= wr) ? (collision |= RIGHT) : (collision &= ~RIGHT);

	/* And now we return a boolean value for whichever case was passed into
	 * the function through the int direction. */
	switch (direction)
	{
		case UP:
			return collision & UP;
		case DOWN:
			return collision & DOWN;
		case LEFT:
			return collision & LEFT;
		case RIGHT:
			return collision & RIGHT;
		default:
			return false;
	}
}

/* This function returns true whenever the camera is strictly past
 * the region boundaries. */
bool camera_infringes(camera_t *camera, int direction)
{
	/* Just declaring these for simplicity. */
	int x = camera_get_x(camera);
	int y = camera_get_y(camera);
	int hs = SCREEN_HEIGHT;
	int ws = SCREEN_WIDTH;
	int hr = camera->region->height * TILE_PIXEL_HEIGHT;
	int wr = camera->region->width * TILE_PIXEL_WIDTH;
	int collision = 0;

	/* This takes care of deciding which side of the camera is colliding
	 * against the region, and it puts that information in the collision
	 * bit field. */
	(y < 0) ? (collision |= UP) : (collision &= ~UP);
	(y + hs > hr) ? (collision |= DOWN) : (collision &= ~DOWN);
	(x < 0) ? (collision |= LEFT) : (collision &= ~LEFT);
	(x + ws > wr) ? (collision |= RIGHT) : (collision &= ~RIGHT);

	/* And now we return a boolean value for whichever case was passed into
	 * the function through the int direction. */
	switch (direction)
	{
		case UP:
			return collision & UP;
		case DOWN:
			return collision & DOWN;
		case LEFT:
			return collision & LEFT;
		case RIGHT:
			return collision & RIGHT;
		default:
			return false;
	}
}


/* This function draws on the game screen the portion of the region that the
 * camera currently sees. */
void camera_view(camera_t *camera, SDL_Surface *game_screen)
{
	SDL_Rect *rect = malloc(sizeof(SDL_Rect));
	rect->x = camera_get_x(camera);
	rect->y = camera_get_y(camera);
	rect->w = SCREEN_WIDTH;
	rect->h = SCREEN_HEIGHT;

	SDL_BlitSurface(camera->region->ground, rect, game_screen, NULL);
	//printf("%s\n", SDL_GetError());
}

/* This function centers the camera on the character whenever it doesn't
 * collide with the region boundaries. */
void center_camera(camera_t *camera)
{
	/* These are the coordinates of the respective centers of the camera
	 * and the character. */
	//int cam_x = camera_get_x(camera) + SCREEN_WIDTH / 2;
	//int cam_y = camera_get_y(camera) + SCREEN_HEIGHT / 2;
	//int char_x = character_get_x(camera->character) + camera->character->w / 2;
	//int char_y = character_get_y(camera->character) + camera->character->h / 2;

/*
	double cam_x = camera->x + SCREEN_WIDTH / 2;
	double cam_y = camera->y + SCREEN_HEIGHT / 2;
	double char_x = camera->character->x + camera->character->w / 2;
	double char_y = camera->character->y + camera->character->h / 2;
*/
	/* If the character is left of the camera center... */
	//while (char_x < cam_x && !camera_collision(camera, LEFT))
	//	cam_x -= 0.1;
	/* Else if the character is to the right of the camera center... */
	//while (char_x > cam_x && !camera_collision(camera, RIGHT))
	//	cam_x += 0.1;
	/* If the character is above the camera center... */
	//while (char_y < cam_y && !camera_collision(camera, UP))
	//	cam_y -= 0.1;
	/* Else if the character is below the camera center... */
	//while (char_y > cam_y && !camera_collision(camera, DOWN))
	//	cam_y += 0.1;

/*
	if (char_x <= cam_x && !camera_collision(camera, LEFT))
		cam_x = char_x;
	if (char_x >= cam_x && !camera_collision(camera, RIGHT))
		cam_x = char_x;
	if (char_y <= cam_y && !camera_collision(camera, UP))
		cam_y = char_y;
	if (char_y >= cam_y && !camera_collision(camera, DOWN))
		cam_y = char_y;
*/
	//cam_x = char_x;
	//cam_y = char_y;

	//camera->x = cam_x - SCREEN_WIDTH / 2;
	//camera->y = cam_y - SCREEN_HEIGHT / 2;

	double char_x = camera->character->x;
	double char_y = camera->character->y;
	double char_w = camera->character->w;
	double char_h = camera->character->h;
	double cam_w = SCREEN_WIDTH;
	double cam_h = SCREEN_HEIGHT;
	double reg_w = camera->region->width * TILE_PIXEL_WIDTH;
	double reg_h = camera->region->height * TILE_PIXEL_HEIGHT;

	camera->x = char_x + (char_w - cam_w) / 2;
	camera->y = char_y + (char_h - cam_h) / 2;

	/* This snippet of code makes sure that the camera does not go past the
	 * region boundaries. However, if the region is smaller than the camera
	 * along one axis, then this makes sure that the camera remains
	 * centered on the region. */
	if (cam_h <= reg_h)
	{
		while (camera_infringes(camera, UP))
			camera->y += 1 - (CHARACTER_SPEED - floor(CHARACTER_SPEED));
		while (camera_infringes(camera, DOWN))
			camera->y -= 1 - (CHARACTER_SPEED - floor(CHARACTER_SPEED));
	}
	else
		camera->y = (reg_h - cam_h) / 2;

	if (cam_w <= reg_w)
	{
		while (camera_infringes(camera, LEFT))
			camera->x += 1 - (CHARACTER_SPEED - floor(CHARACTER_SPEED));
		while (camera_infringes(camera, RIGHT))
			camera->x -= 1 - (CHARACTER_SPEED - floor(CHARACTER_SPEED));
	}
	else
		camera->x = (reg_w - cam_w) / 2;
}


/* Since regions are usually larger than our gamescreen, we can only show
 * part of them. Assuming that dst is our gamescreen, a.k.a. our "camera",
 * this function places the camera over the region (which is assumed to
 * be src) such that the camera's top right corner is in the position
 * (x,y) with respect to the region. */
/*
void camera_view(SDL_Surface *src, SDL_Surface *dst, int x, int y)
{
	SDL_Rect src_rect;
	src_rect.x = x;
	src_rect.y = y;
	src_rect.w = SCREEN_WIDTH;
	src_rect.h = SCREEN_HEIGHT;

	SDL_BlitSurface(src, &src_rect, dst, NULL);
}*/

/* Notice that we concern ourselves not with the character's hitbox, but with
 * their actual frame. This is because we will use this function for the
 * transition between regions. */
bool is_character_on_camera_edge(camera_t *camera, int direction)
{
	int x = (int) round(camera->character->x - camera->x);
	int y = (int) round(camera->character->y - camera->y);
	int w = camera->character->w;
	int h = camera->character->h;
	int cam_w = SCREEN_WIDTH;
	int cam_h = SCREEN_HEIGHT;

	switch (direction)
	{
		case UP:
			return y == 0;
		case DOWN:
			return y + h == cam_h;
		case LEFT:
			return x == 0;
		case RIGHT:
			return x + w == cam_w;
		default: break;
	}
}
