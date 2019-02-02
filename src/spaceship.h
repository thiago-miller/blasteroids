#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <allegro5/allegro.h>

typedef struct
{
	float         sx;
	float         sy;
	float         radius;
	int           lives;
	long          score;
	float         heading;
	float         speed;
	int           gone;
	ALLEGRO_COLOR color;
} Spaceship;


#define SPACESHIP_LIVES 3
#define SPACESHIP_COLOR al_map_rgb (0, 100, 0)
#define SPACESHIP_RADIUS 10
#define SPACESHIP_MAX_SPEED 4.0f
#define SPACESHIP_ACCELERATION_GRADIENT 0.05f
#define SPACESHIP_DRIFTING_GRADIENT 0.025f
#define SPACESHIP_BRAKE_GRADIENT 0.1f
#define SPACESHIP_DEGREE_OF_ROTATION_RADIAN (ALLEGRO_PI / 30)
#define SPACESHIP_INVINCIBILITY_TICKS (4 * FPS)

Spaceship * spaceship_new                (void);
void        spaceship_free               (Spaceship *s);
void        spaceship_die                (Spaceship *s);
void        spaceship_add_points         (Spaceship *s, int points);
void        spaceship_draw_ship          (Spaceship* s);
void        spaceship_rotate_left        (Spaceship *s);
void        spaceship_rotate_right       (Spaceship *s);
void        spaceship_calculate_position (Spaceship *s);
void        spaceship_drift              (Spaceship *s);
void        spaceship_accelerate         (Spaceship *s);
void        spaceship_decelerate         (Spaceship *s);

#define spaceship_get_sx(s) (s->sx)
#define spaceship_get_sy(s) (s->sy)
#define spaceship_get_heading(s) (s->heading)
#define spaceship_get_speed(s) (s->speed)
#define spaceship_get_radius(s) (s->radius)
#define spaceship_get_score(s) (s->score)
#define spaceship_get_lives(s) (s->lives)

#endif /* spaceship.h */
