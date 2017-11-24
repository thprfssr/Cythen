#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 144
#define DESIRED_FPS 60

static bool QUIT = false;

SDL_Window* open_window()
{
	SDL_Window *window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("SDL could not initialize! SDL_Error: %s\n",
				SDL_GetError());
		exit(1);
	}
	else
	{
		window = SDL_CreateWindow("Cythen",
					  SDL_WINDOWPOS_UNDEFINED,
					  SDL_WINDOWPOS_UNDEFINED,
					  300, 300,
					  SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			SDL_Log("Window could not be created! SDL_Error: %s\n",
			       SDL_GetError());
			exit(1);
		}
	}

	return window;
}

SDL_Surface* create_game_surface()
{
	SDL_Surface *surface;
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

	surface = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
				       rmask, gmask, bmask, amask);
	if (surface == NULL)
	{
		SDL_Log("SDL_CreateRGBSurface() failed: %s\n",
			SDL_GetError());
		exit(1);
	}
}

void handle_event(SDL_Event event)
{
	switch (event.type)
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
	SDL_Window *window = open_window();

		SDL_Surface *surface = SDL_GetWindowSurface(window);
		SDL_Event event;

		int frame_counter = 0;

	while (!QUIT)
	{
		while(SDL_PollEvent(&event) != 0)
		{
			handle_event(event);
		}

		SDL_FillRect(surface, NULL,
			     SDL_MapRGB(surface->format,
					0x00, 0x00, 0x00));
		SDL_UpdateWindowSurface(window);

		frame_counter++;
		SDL_Delay(1000 / DESIRED_FPS);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
