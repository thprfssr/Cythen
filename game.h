#ifndef GAME_H
#define GAME_H

SDL_Window* open_window();
SDL_Surface* create_game_screen();
SDL_Surface* load_resource(char* path);
void handle_event(SDL_Event event);
void end();
void letterbox(SDL_Surface* src, SDL_Surface* dst);

#endif
