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
static int inv_ticks = 0;

static void
spaceship_setup (Spaceship *s)
{
	*s = (Spaceship) {
		.sx         = DISPLAY_WIDTH / 2,
		.sy         = DISPLAY_HEIGH / 2,
		.radius     = SPACESHIP_RADIUS,
		.color      = SPACESHIP_COLOR,
		.lives      = SPACESHIP_LIVES,
		.score      = 0,
		.invincible = false
	};
}

Spaceship *
spaceship_new (void)
{
	Spaceship *s = calloc (1, sizeof (Spaceship));
	if (s == NULL)
		error ("Failed to create spaceship object");

	spaceship_setup (s);

	return s;
}

void
spaceship_reset (Spaceship *s)
{
	spaceship_setup (s);
}

void
spaceship_free (Spaceship *s)
{
	if (s == NULL)
		return;
	free (s);
}

void
spaceship_die (Spaceship *s)
{
	s->gone = true;
}

void
spaceship_add_points (Spaceship *s, int points)
{
	s->score += points;
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

void
spaceship_calculate_invencibility (Spaceship *s)
{
	static bool flip_color = true;
	if (s->invincible)
		{
			if (inv_ticks >= SPACESHIP_INVINCIBILITY_TICKS)
				{
					inv_ticks = 0;
					s->invincible = false;
				}
			else
				inv_ticks++;

			if (flip_color)
				{
					s->color = SPACESHIP_INVINCIBLE_COLOR;
					flip_color = false;
				}
			else
				{
					s->color = SPACESHIP_COLOR;
					flip_color = true;
				}
		}
	else
		s->color = SPACESHIP_COLOR;
}

void
spaceship_calculate_position (Spaceship *s)
{
	if (s->gone)
		{
			s->lives --;
			s->invincible = true;
			s->gone = false;
		}

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
