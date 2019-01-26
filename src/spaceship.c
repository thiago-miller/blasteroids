#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <allegro5/allegro_primitives.h>
#include <error.h>
#include <spaceship.h>

Spaceship *
spaceship_new (float sx, float sy, ALLEGRO_COLOR color)
{
	Spaceship *s = calloc (1, sizeof (Spaceship));
	if (s == NULL)
		error ("Failed to create spaceship object");

	*s = (Spaceship) {
		.sx    = sx,
		.sy    = sy,
		.color = color
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
spaceship_rotate_left (Spaceship *s, float degrees)
{
	s->heading -= degrees;
}

void
spaceship_rotate_right (Spaceship *s, float degrees)
{
	s->heading += degrees;
}

float
spaceship_get_heading (Spaceship *s)
{
	return s->heading;
}

void
spaceship_move (Spaceship *s)
{
	s->sy -= s->speed * cos (s->heading);
	s->sx += s->speed * sin (s->heading);
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
spaceship_accelerate (Spaceship *s, float speed)
{
	s->speed += speed;
}

void
spaceship_decelerate (Spaceship *s, float speed)
{
	s->speed -= speed;
}

float
spaceship_get_speed (Spaceship *s)
{
	return s->speed;
}

void
spaceship_set_speed (Spaceship *s, float speed)
{
	s->speed = speed;
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
}
