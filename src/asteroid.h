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
#define ASTEROID_RADIUS 25
#define ASTEROID_SPEED 1.0f
#define ASTEROID_RATE_SEC 5
#define ASTEROID_ROT_VELOCITY ALLEGRO_PI / 270

void asteroid_control            (void);
void asteroid_free               (void);
void asteroid_calculate_position (void);
void asteroid_draw               (void);

#endif /* asteroid.h */
