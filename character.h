#ifndef CHARACTER_H
#define CHARACTER_H

typedef struct
{
	int x;
	int y;
	int w;
	int h;
} character_t;

character_t character_init(int x, int y, int w, int h);

#endif
