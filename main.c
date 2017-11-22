#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char **argv)
{
	SDL_Window *window = NULL;

	SDL_Surface* surface = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n",
			SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow("Cythen",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n",
					SDL_GetError());
		}
		else
		{
			bool quit = false;
			SDL_Event e;

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					switch (e.type)
					{
						case SDL_QUIT:
							quit = true;
							break;
						default:
							break;
					}
				}

				surface = SDL_GetWindowSurface(window);

				SDL_FillRect(surface, NULL,
					SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));

				SDL_UpdateWindowSurface(window);

				SDL_Delay(16);

			}

		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
