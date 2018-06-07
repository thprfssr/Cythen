#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <SDL2/SDL.h>

#define GAME_TITLE "Cythen"
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 144
#define DESIRED_FPS 60

#define TILE_ATLAS_PATH "resources/tile_atlas.png"
#define TILE_WALKABILITY_PATH "resources/tile_walkability.txt"
#define TITLE_SCREEN_PATH "resources/title_screen.png"

bool g_is_quitting;
void quit();
bool is_quitting();

void handle_event(SDL_Event event);
void play();

#endif
