#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

typedef struct
{
	float         sx;
	float         sy;
	float         heading;
	float         speed;
	int           gone;
	ALLEGRO_COLOR color;
} Spaceship;

Spaceship * spaceship_new          (float sx, float sy, ALLEGRO_COLOR color);
void        spaceship_free         (Spaceship *s);
void        spaceship_draw_ship    (Spaceship* s);
void        spaceship_rotate_left  (Spaceship *s, float degrees);
void        spaceship_rotate_right (Spaceship *s, float degrees);
float       spaceship_get_heading  (Spaceship *s);
void        spaceship_move         (Spaceship *s);
void        spaceship_set_pos      (Spaceship *s, float sx, float sy);
void        spaceship_get_pos      (Spaceship *s, float *sx, float *sy);
void        spaceship_accelerate   (Spaceship *s, float speed);
void        spaceship_decelerate   (Spaceship *s, float speed);
float       spaceship_get_speed    (Spaceship *s);
void        spaceship_set_speed    (Spaceship *s, float speed);

#endif /* spaceship.h */
