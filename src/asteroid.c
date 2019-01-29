#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "blasteroids.h"
#include "movement.h"
#include "list.h"
#include "error.h"
#include "asteroid.h"

void
asteroid_setup (Asteroid *a)
{
	float sx = 0;
	float sy = 0;
	float heading = 0;
	float rot_velocity = 0;

	srand (time (NULL));

	if (rand () % 2)
		{
			if (rand () % 2)
				sx = 0;
			else
				sx = DISPLAY_WIDTH;

			sy = rand () % (DISPLAY_HEIGH + 1);
		}
	else
		{
			if (rand () % 2)
				sy = 0;
			else
				sy = DISPLAY_HEIGH;

			sx = rand () % (DISPLAY_WIDTH + 1);
		}

	heading = rand () % 360 * ALLEGRO_PI / 180;
	rot_velocity = ASTEROID_ROT_VELOCITY;
	if (rand () % 2)
		rot_velocity *= -1;

	*a = (Asteroid) {
		.sx           = sx,
		.sy           = sy,
		.heading      = heading,
		.rot_velocity = rot_velocity,
		.speed        = ASTEROID_SPEED,
		.color        = ASTEROID_COLOR
	};
}

Asteroid *
asteroid_new (void)
{
	Asteroid *a = calloc (1, sizeof (Asteroid));
	if (a == NULL)
		error ("Failed to create asteroid object");

	asteroid_setup (a);
	return a;
}

void
asteroid_free (Asteroid *a)
{
	if (a == NULL)
		return;
	free (a);
}

void
asteroid_calculate_position (Asteroid *a)
{
	movement_calculate_2D_position (&a->sx, &a->sy, a->heading, a->speed);
	a->twist += a->rot_velocity;
	movement_teleport (&a->sx, &a->sy);
}

void
asteroid_draw (Asteroid *a)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_rotate_transform (&transform, a->twist);
	al_translate_transform (&transform, a->sx, a->sy);
	al_use_transform (&transform);
	al_draw_line(-20, 20, -25, 5, a->color, 2.0f);
	al_draw_line(-25, 5, -25, -10, a->color, 2.0f);
	al_draw_line(-25, -10, -5, -10, a->color, 2.0f);
	al_draw_line(-5, -10, -10, -20, a->color, 2.0f);
	al_draw_line(-10, -20, 5, -20, a->color, 2.0f);
	al_draw_line(5, -20, 20, -10, a->color, 2.0f);
	al_draw_line(20, -10, 20, -5, a->color, 2.0f);
	al_draw_line(20, -5, 0, 0, a->color, 2.0f);
	al_draw_line(0, 0, 20, 10, a->color, 2.0f);
	al_draw_line(20, 10, 10, 20, a->color, 2.0f);
	al_draw_line(10, 20, 0, 15, a->color, 2.0f);
	al_draw_line(0, 15, -20, 20, a->color, 2.0f);
}
