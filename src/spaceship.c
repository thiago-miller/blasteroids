#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "error.h"
#include "blasteroids.h"
#include "movement.h"
#include "spaceship.h"

static float drift_heading = 0.0f;
static bool is_drifting = true;

Spaceship *
spaceship_new (void)
{
	Spaceship *s = calloc (1, sizeof (Spaceship));
	if (s == NULL)
		error ("Failed to create spaceship object");

	*s = (Spaceship) {
		.sx    = DISPLAY_WIDTH / 2,
		.sy    = DISPLAY_HEIGH / 2,
		.color = SPACESHIP_COLOR
	};

	return s;
}

void
spaceship_free (Spaceship *s)
{
	if (s == NULL)
		return;
	free (s);
}

void
spaceship_rotate_left (Spaceship *s)
{
	s->heading -= SPACESHIP_DEGREE_OF_ROTATION_RADIAN;
}

void
spaceship_rotate_right (Spaceship *s)
{
	s->heading += SPACESHIP_DEGREE_OF_ROTATION_RADIAN;
}

float
spaceship_get_heading (Spaceship *s)
{
	return s->heading;
}

void
spaceship_calculate_position (Spaceship *s)
{
	float current_heading;

	current_heading = is_drifting
		? drift_heading
		: s->heading;

	movement_calculate_2D_position (&s->sx, &s->sy, current_heading, s->speed);
	movement_teleport (&s->sx, &s->sy);
}

void
spaceship_drift (Spaceship *s)
{
	if (s->speed > 0)
		s->speed -= SPACESHIP_DRIFTING_GRADIENT;

	if (s->speed < 0)
		s->speed = 0;

	is_drifting = true;
}

void
spaceship_set_pos (Spaceship *s, float sx, float sy)
{
	s->sx = sx;
	s->sy = sy;
}

void
spaceship_get_pos (Spaceship *s, float *sx, float *sy)
{
	*sx = s->sx;
	*sy = s->sy;
}

void
spaceship_accelerate (Spaceship *s)
{
	s->speed += SPACESHIP_ACCELERATION_GRADIENT;
	if (s->speed > SPACESHIP_MAX_SPEED)
		s->speed = SPACESHIP_MAX_SPEED;

	drift_heading = s->heading;
	is_drifting = false;
}

void
spaceship_decelerate (Spaceship *s)
{
	s->speed -= SPACESHIP_ACCELERATION_GRADIENT;
	if (s->speed < 0.0f)
		s->speed = 0.0f;
}

void
spaceship_draw_ship (Spaceship *s)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_rotate_transform (&transform, s->heading);
	al_translate_transform (&transform, s->sx, s->sy);
	al_use_transform (&transform);
	al_draw_line (-8, 9, 0, -11, s->color, 3.0f);
	al_draw_line (0, -11, 8, 9, s->color, 3.0f);
	al_draw_line (-6, 4, -1, 4, s->color, 3.0f);
	al_draw_line (6, 4, 1, 4, s->color, 3.0f);
	/*al_draw_circle (0, 0, 10, al_map_rgb (50, 50, 200), 2.0f);*/
}
