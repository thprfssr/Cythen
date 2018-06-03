#ifndef CHARACTER_H
#define CHARACTER_H

#define CHARACTER_SPEED (1.5)

typedef struct
{
	double x;
	double y;
	int w;
	int h;
} character_t;

character_t *create_character(double x, double y, int w, int h);
void draw_character(character_t *character, region_t *region);

void move_character_up(character_t *character);
void move_character_down(character_t *character);
void move_character_left(character_t *character);
void move_character_right(character_t *character);
void control_character(character_t *character);

#endif
