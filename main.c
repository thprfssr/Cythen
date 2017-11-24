#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#define DESIRED_FPS 60

static bool QUIT = false;

SDL_Window* open_window()
{
	SDL_Window *window = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize!SDL_Error: %s\n",
				SDL_GetError());
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
			printf("Window could not be created! SDL_Error: %s\n",
			       SDL_GetError());
		}
	}

	return window;
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
	SDL_Window *window = open_window();

	if(window != NULL)
	{
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
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
