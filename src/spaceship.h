#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

#define SPACESHIP_COLOR al_map_rgb (0, 100, 0)
#define SPACESHIP_MAX_SPEED 4.0f
#define SPACESHIP_ACCELERATION_GRADIENT 0.05f
#define SPACESHIP_DRIFTING_GRADIENT 0.025f
#define SPACESHIP_BRAKE_GRADIENT 0.1f
#define SPACESHIP_DEGREE_OF_ROTATION_RADIAN (ALLEGRO_PI / 30) // 6 degrees
#define SPACESHIP_INVINCIBILITY_TICKS (4 * FPS)

typedef struct
{
	float         sx;
	float         sy;
	float         heading;
	float         speed;
	int           gone;
	ALLEGRO_COLOR color;
} Spaceship;

Spaceship * spaceship_new                (void);
void        spaceship_free               (Spaceship *s);
void        spaceship_draw_ship          (Spaceship* s);
void        spaceship_rotate_left        (Spaceship *s);
void        spaceship_rotate_right       (Spaceship *s);
float       spaceship_get_heading        (Spaceship *s);
void        spaceship_calculate_position (Spaceship *s);
void        spaceship_drift              (Spaceship *s);
void        spaceship_set_pos            (Spaceship *s, float sx, float sy);
void        spaceship_get_pos            (Spaceship *s, float *sx, float *sy);
void        spaceship_accelerate         (Spaceship *s);
void        spaceship_decelerate         (Spaceship *s);
float       spaceship_get_speed          (Spaceship *s);
void        spaceship_set_speed          (Spaceship *s, float speed);

#endif /* spaceship.h */
