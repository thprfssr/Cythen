#include <stdbool.h>
#include <SDL2/SDL.h>
#include "controls.h"

int g_controller_status = 0;

void button_pressed(int button)
{
	g_controller_status |= button;
}

void button_released(int button)
{
	g_controller_status &= ~button;
}

bool is_button_pressed(int button)
{
	return g_controller_status & button;
}

void handle_input(SDL_KeyboardEvent event)
{
	if (event.type == SDL_KEYDOWN)
	{
		switch (event.keysym.scancode)
		{
			case SDL_SCANCODE_W:
				button_pressed(BUTTON_UP);
				break;
			case SDL_SCANCODE_S:
				button_pressed(BUTTON_DOWN);
				break;
			case SDL_SCANCODE_A:
				button_pressed(BUTTON_LEFT);
				break;
			case SDL_SCANCODE_D:
				button_pressed(BUTTON_RIGHT);
				break;
			case SDL_SCANCODE_B:
				button_pressed(BUTTON_START);
				break;
			case SDL_SCANCODE_V:
				button_pressed(BUTTON_SELECT);
				break;
			case SDL_SCANCODE_L:
				button_pressed(BUTTON_A);
				break;
			case SDL_SCANCODE_K:
				button_pressed(BUTTON_B);
				break;
			case SDL_SCANCODE_I:
				button_pressed(BUTTON_X);
				break;
			case SDL_SCANCODE_J:
				button_pressed(BUTTON_Y);
				break;
			case SDL_SCANCODE_E:
				button_pressed(BUTTON_L);
				break;
			case SDL_SCANCODE_U:
				button_pressed(BUTTON_R);
				break;
			default:
				break;
		}
	}
	else if (event.type == SDL_KEYUP)
	{
		switch (event.keysym.scancode)
		{
			case SDL_SCANCODE_W:
				button_released(BUTTON_UP);
				break;
			case SDL_SCANCODE_S:
				button_released(BUTTON_DOWN);
				break;
			case SDL_SCANCODE_A:
				button_released(BUTTON_LEFT);
				break;
			case SDL_SCANCODE_D:
				button_released(BUTTON_RIGHT);
				break;
			case SDL_SCANCODE_B:
				button_released(BUTTON_START);
				break;
			case SDL_SCANCODE_V:
				button_released(BUTTON_SELECT);
				break;
			case SDL_SCANCODE_L:
				button_released(BUTTON_A);
				break;
			case SDL_SCANCODE_K:
				button_released(BUTTON_B);
				break;
			case SDL_SCANCODE_I:
				button_released(BUTTON_X);
				break;
			case SDL_SCANCODE_J:
				button_released(BUTTON_Y);
				break;
			case SDL_SCANCODE_E:
				button_released(BUTTON_L);
				break;
			case SDL_SCANCODE_U:
				button_released(BUTTON_R);
				break;
			default:
				break;
		}
	}
}

/*
 * BUTTON_UP		SDL_SCANCODE_W
 * BUTTON_DOWN		SDL_SCANCODE_S
 * BUTTON_LEFT		SDL_SCANCODE_A
 * BUTTON_RIGHT		SDL_SCANCODE_D
 * BUTTON_START		SDL_SCANCODE_B
 * BUTTON_SELECT	SDL_SCANCODE_V
 * BUTTON_A		SDL_SCANCODE_L
 * BUTTON_B		SDL_SCANCODE_K
 * BUTTON_X		SDL_SCANCODE_I
 * BUTTON_Y		SDL_SCANCODE_J
 * BUTTON_L		SDL_SCANCODE_E
 * BUTTON_R		SDL_SCANCODE_U
 */
