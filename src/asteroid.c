#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "blasteroids.h"
#include "movement.h"
#include "error.h"
#include "asteroid.h"

static List *asteroid_trash = NULL;
static List *asteroid_live = NULL;
static long tick_acm = 0;

List *
asteroid_get_list (void)
{
	return asteroid_live;
}

static Asteroid *
asteroid_new (void)
{
	Asteroid *a = calloc (1, sizeof (Asteroid));
	if (a == NULL)
		error ("Failed to create asteroid object");

	*a = (Asteroid) {
		.color = ASTEROID_COLOR,
		.speed = ASTEROID_SPEED
	};

	return a;
}

static List *
asteroid_trash_recycle (void)
{
	List *shift = asteroid_trash;
	asteroid_trash = list_remove_link (asteroid_trash, shift);
	return shift;
}

static void
asteroid_setup (Asteroid *a)
{
	float sx = 0;
	float sy = 0;
	float heading = 0;
	float rot_velocity = 0;

	// Raffle which boundary the
	// asteroid will come from
	if (rand () % 2)
		{
			// asteroid will come from left/right
			if (rand () % 2)
				sx = 0;
			else
				sx = DISPLAY_WIDTH;

			// draw the height position
			sy = rand () % (DISPLAY_HEIGH + 1);
		}
	else
		{
			// asteroid will come from up/down
			if (rand () % 2)
				sy = 0;
			else
				sy = DISPLAY_HEIGH;

			// draw the width position
			sx = rand () % (DISPLAY_WIDTH + 1);
		}

	// Raffle the angle
	heading = rand () % 360 * ALLEGRO_PI / 180;

	// Raffle the rotation velocity and
	// clockwise direction
	rot_velocity = ASTEROID_ROT_VELOCITY;
	if (rand () % 2)
		rot_velocity *= -1;

	a->sx = sx;
	a->sy = sy;
	a->radius = ASTEROID_RADIUS;
	a->scale = 1;
	a->heading = heading;
	a->rot_velocity = rot_velocity;
	a->gone = false;
}

static void
asteroid_split (Asteroid *a1)
{
	Asteroid *a2 = NULL;

	if (asteroid_trash == NULL)
		{
			a2 = asteroid_new ();
			asteroid_live = list_ins_prev (asteroid_live, a2);
		}
	else
		{
			List *l = asteroid_trash_recycle ();
			a2 = list_data (l);
			asteroid_live = list_concat (l, asteroid_live);
		}

	a2->gone = false;
	a2->heading = a1->heading - ALLEGRO_PI/12;
	a2->scale = 0.5;
	a2->radius = ASTEROID_RADIUS/2;
	a2->rot_velocity = a1->rot_velocity * - 1;
	a2->sx = a1->sx;
	a2->sy = a1->sy;
	movement_calculate_2D_position (&a2->sx, &a2->sy,
			a2->heading, -11);

	a1->gone = false;
	a1->heading += ALLEGRO_PI/12;
	a1->scale = 0.5;
	a1->radius = ASTEROID_RADIUS/2;
	movement_calculate_2D_position (&a1->sx, &a1->sy,
			a1->heading, 11);
}

static void
_asteroid_free (Asteroid *a)
{
	if (a == NULL)
		return;
	free (a);
}

void
asteroid_free (void)
{
	list_free (asteroid_live, (list_clean_data_fun) _asteroid_free);
	list_free (asteroid_trash, (list_clean_data_fun) _asteroid_free);
}

void
asteroid_die (Asteroid *a)
{
	a->gone = true;
}

void
asteroid_control (void)
{
	// Update ticks
	tick_acm ++;

	if (!(tick_acm % ASTEROID_RATE_SEC) || asteroid_live == NULL)
		{
			tick_acm = 0;
			if (asteroid_trash == NULL)
				{
					Asteroid *a = asteroid_new ();
					asteroid_setup (a);
					asteroid_live = list_ins_prev (asteroid_live, a);
				}
			else
				{
					List *l = asteroid_trash_recycle ();
					asteroid_setup (list_data (l));
					asteroid_live = list_concat (l, asteroid_live);
				}
		}
}

static void
_asteroid_calculate_position (Asteroid *a)
{
	movement_calculate_2D_position (&a->sx, &a->sy, a->heading, a->speed);
	a->twist += a->rot_velocity;
	movement_teleport (&a->sx, &a->sy);
}

void
asteroid_calculate_position (void)
{
	List *cur = asteroid_live;

	while (cur != NULL)
		{
			List *next = list_next (cur);

			Asteroid *a = list_data (cur);
			_asteroid_calculate_position (a);

			if (a->gone)
				{
					if (a->scale == 1)
						asteroid_split (a);
					else
						{
							asteroid_live = list_remove_link (asteroid_live, cur);
							asteroid_trash = list_concat (cur, asteroid_trash);
						}
				}

			cur = next;
		}
}

static void
_asteroid_draw (Asteroid *a)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_scale_transform(&transform, a->scale, a->scale);
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
	/*al_draw_circle (0, 0, 25, al_map_rgb (200, 50, 200), 2.0f);*/
}

void
asteroid_draw (void)
{
	for (List *cur = asteroid_live; cur != NULL; cur = list_next (cur))
		_asteroid_draw (list_data (cur));
}
