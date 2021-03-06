#ifndef WINDOW_H
#define WINDOW_H

SDL_Window *open_window(const char *name);
SDL_Surface *create_game_screen();
SDL_Surface *load_resource(char *path);
void handle_event(SDL_Event event);
void end();
void letterbox(SDL_Surface *src, SDL_Surface *dst);
void play();

#endif
