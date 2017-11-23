#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

static SDL_Window *MAIN_WINDOW = NULL;
static SDL_Surface *MAIN_SURFACE = NULL;
static bool QUIT = false;

bool init()
{
	bool success;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize!SDL_Error: %s\n",
				SDL_GetError());
		success = false;
	}
	else
	{
		MAIN_WINDOW = SDL_CreateWindow("Cythen",
				SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED,
				400, 400,
				SDL_WINDOW_SHOWN);

		if (MAIN_WINDOW == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n",
					SDL_GetError());
			success = false;
		}
		else
		{
			MAIN_SURFACE = SDL_GetWindowSurface(MAIN_WINDOW);
			success = true;
		}
	}

	return success;
}

void handle_event(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_QUIT:
			QUIT = true;
			break;
		default:
			break;
	}
}


int main(int argc, char **argv)
{
	if (!init())
	{
		printf("Could not initialize!\n");
	}
	else
	{
		SDL_Event event;

		while (!QUIT)
		{
			while(SDL_PollEvent(&event) != 0)
			{
				handle_event(event);
			}

			SDL_FillRect(MAIN_SURFACE, NULL,
					SDL_MapRGB(MAIN_SURFACE->format, 0x00, 0x00, 0x00));
			SDL_UpdateWindowSurface(MAIN_WINDOW);

			SDL_Delay(16);
		}
	}

	SDL_DestroyWindow(MAIN_WINDOW);
	SDL_Quit();

	return 0;
}
