#ifndef ASTEROID_H
#define ASTEROID_H

#include <allegro5/allegro.h>
#include "recycle.h"

typedef struct
{
	float         sx;
	float         sy;
	float         radius;
	float         heading;
	float         twist;
	float         speed;
	float         rot_velocity;
	float         scale;
	int           gone;
	ALLEGRO_COLOR color;
} Asteroid;

#define ASTEROID_REWARD_POINTS 100
#define ASTEROID_COLOR al_map_rgb (255, 255, 255)
#define ASTEROID_RADIUS 25
#define ASTEROID_SPEED 1.0f
#define ASTEROID_RATE_SEC (FPS * 5)
#define ASTEROID_ROT_VELOCITY (ALLEGRO_PI / 270)
#define ASTEROID_ROT_SPLIT (ASTEROID_ROT_VELOCITY * 100)
#define ASTEROID_PADDING_SPLIT 20
#define ASTEROID_MIN_SCALE 0.25

ListElmt * asteroid_get_list_head      (void);
void       asteroid_reset              (void);
void       asteroid_die                (Asteroid *a);
void       asteroid_control            (void);
void       asteroid_free               (void);
void       asteroid_calculate_position (void);
void       asteroid_draw               (void);
void       asteroid_init               (void);

#define asteroid_get_sx(a) (a->sx)
#define asteroid_get_sy(a) (a->sy)
#define asteroid_get_radius(a) (a->radius)
#define asteroid_get_heading(a) (a->heading)
#define asteroid_get_twist(a) (a->twist)
#define asteroid_get_speed(a) (a->speed)
#define asteroid_get_rot_velocity(a) (a->rot_velocity)
#define asteroid_get_scale(a) (a->scale)

#endif /* asteroid.h */
