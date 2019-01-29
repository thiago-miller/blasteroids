#ifndef ASTEROID_H
#define ASTEROID_H

#include <allegro5/allegro.h>

typedef struct
{
	float sx;
	float sy;
	float heading;
	float twist;
	float speed;
	float rot_velocity;
	float scale;
	int gone;
	ALLEGRO_COLOR color;
} Asteroid;

#define ASTEROID_COLOR al_map_rgb (255, 255, 255)
#define ASTEROID_SPEED 1.0f
#define ASTEROID_ROT_VELOCITY ALLEGRO_PI / 270

Asteroid * asteroid_new                (void);
void       asteroid_free               (Asteroid *a);
void       asteroid_calculate_position (Asteroid *a);
void       asteroid_draw               (Asteroid *a);

#endif /* asteroid.h */
