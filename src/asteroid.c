#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <stdlib.h>
#include "blasteroids.h"
#include "movement.h"
#include "error.h"
#include "asteroid.h"

static Recycle *recycle = NULL;
static ALLEGRO_SAMPLE *bang_large = NULL;
static ALLEGRO_SAMPLE *bang_medium = NULL;
static ALLEGRO_SAMPLE *bang_small = NULL;
static long tick_acm = 0;

void
asteroid_reset (void)
{
	tick_acm = 0;
	ListElmt *cur = recycle_list_head (recycle);

	while (cur != NULL)
		{
			ListElmt *next = list_next (cur);
			recycle_remove_list_element (recycle, cur);
			cur = next;
		}
}

ListElmt *
asteroid_get_list_head (void)
{
	return recycle_list_head (recycle);
}

static Asteroid *
asteroid_new (void)
{
	Asteroid *a = calloc (1, sizeof (Asteroid));
	if (a == NULL)
		error ("Failed to create asteroid object");

	return a;
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
	a->speed = ASTEROID_SPEED;
	a->color = ASTEROID_COLOR;
}

static void
asteroid_split (Asteroid *a1)
{
	Asteroid *a2 = list_data (recycle_get_list_element (recycle));
	*a2 = *a1;

	// Setup child asteroid
	a2->gone = false;
	a2->heading -= ASTEROID_ROT_SPLIT;
	a2->scale /= 2;
	a2->radius /= 2;
	a2->rot_velocity *= -2;
	a2->speed /= 2;
	movement_calculate_2D_position (&a2->sx, &a2->sy,
			a2->heading, -ASTEROID_PADDING_SPLIT);

	// Setup parent asteroid
	a1->gone = false;
	a1->heading += ASTEROID_ROT_SPLIT;
	a1->scale /= 2;
	a1->radius /= 2;
	a1->rot_velocity *= 2;
	a1->speed /= 2;
	movement_calculate_2D_position (&a1->sx, &a1->sy,
			a1->heading, ASTEROID_PADDING_SPLIT);
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
	if (bang_large)
		al_destroy_sample (bang_large);

	if (bang_medium)
		al_destroy_sample (bang_medium);

	if (bang_small)
		al_destroy_sample (bang_small);

	recycle_free (recycle);
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

	if (tick_acm == ASTEROID_RATE_SEC || recycle_list_empty (recycle))
		{
			tick_acm = 0;
			asteroid_setup (list_data (recycle_get_list_element (recycle)));
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
	ListElmt *cur = recycle_list_head (recycle);

	while (cur != NULL)
		{
			ListElmt *next = list_next (cur);

			Asteroid *a = list_data (cur);
			_asteroid_calculate_position (a);

			if (a->gone)
				{
					if (a->scale > ASTEROID_MIN_SCALE)
						{
							if (a->scale == 1)
								al_play_sample (bang_large, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
							else
								al_play_sample (bang_medium, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);

							asteroid_split (a);
						}
					else
						{
							recycle_remove_list_element (recycle, cur);
							al_play_sample (bang_small, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
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
	al_scale_transform(&transform, a->scale * 1.5, a->scale * 1.5);
	al_rotate_transform (&transform, a->twist);
	al_translate_transform (&transform, a->sx, a->sy);
	al_use_transform (&transform);
	al_draw_line (-20, 20, -25, 5, a->color, 2.0f);
	al_draw_line (-25, 5, -25, -10, a->color, 2.0f);
	al_draw_line (-25, -10, -5, -10, a->color, 2.0f);
	al_draw_line (-5, -10, -10, -20, a->color, 2.0f);
	al_draw_line (-10, -20, 5, -20, a->color, 2.0f);
	al_draw_line (5, -20, 20, -10, a->color, 2.0f);
	al_draw_line (20, -10, 20, -5, a->color, 2.0f);
	al_draw_line (20, -5, 0, 0, a->color, 2.0f);
	al_draw_line (0, 0, 20, 10, a->color, 2.0f);
	al_draw_line (20, 10, 10, 20, a->color, 2.0f);
	al_draw_line (10, 20, 0, 15, a->color, 2.0f);
	al_draw_line (0, 15, -20, 20, a->color, 2.0f);
	/*al_draw_circle (0, 0, 25, al_map_rgb (200, 50, 200), 2.0f);*/
}

void
asteroid_draw (void)
{
	for (ListElmt *cur = recycle_list_head (recycle); cur != NULL; cur = list_next (cur))
		_asteroid_draw (list_data (cur));
}

void
asteroid_init (void)
{
	bang_large = al_load_sample ("../assets/sound/bangLarge.wav");
	if (!bang_large)
		error ("Failed to load 'bangLarge.wav' sample");

	bang_medium = al_load_sample ("../assets/sound/bangMedium.wav");
	if (!bang_medium)
		error ("Failed to load 'bangMedium.wav' sample");

	bang_small = al_load_sample ("../assets/sound/bangSmall.wav");
	if (!bang_small)
		error ("Failed to load 'bangSmall.wav' sample");

	recycle = recycle_new ((RecycleCreate)asteroid_new,
			(RecycleDestroy)_asteroid_free);
}
