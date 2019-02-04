#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "movement.h"
#include "sound.h"
#include "error.h"
#include "blast.h"

static Recycle *recycle = NULL;
static int interval = BLAST_INTERVAL;

void
blast_reset (void)
{
	ListElmt *cur = recycle_list_head (recycle);

	while (cur != NULL)
		{
			ListElmt *next = list_next (cur);
			recycle_remove_list_element (recycle, cur);
			cur = next;
		}
}

ListElmt *
blast_get_list_head (void)
{
	return recycle_list_head (recycle);
}

static void
blast_setup (Blast *b, Spaceship *s)
{
	b->gone = false;
	b->heading = spaceship_get_heading (s);
	b->sx = spaceship_get_sx (s);
	b->sy = spaceship_get_sy (s);
	movement_calculate_2D_position (&b->sx, &b->sy,
			b->heading, BLAST_PADDING);
}

static Blast *
blast_new (void)
{
	Blast *b = calloc (1, sizeof (Blast));
	if (b == NULL)
		error ("Failed to create blast object");

	*b = (Blast) {
		.color  = BLAST_COLOR,
		.speed  = BLAST_SPEED,
		.radius = BLAST_RADIUS
	};

	return b;
}

static void
_blast_free (Blast *b)
{
	if (b == NULL)
		return;
	free (b);
}

void
blast_free (void)
{
	recycle_free (recycle);
}

void
blast_die (Blast *b)
{
	b->gone = true;
}

static void
_blast_calculate_position (Blast *b)
{
	movement_calculate_2D_position (&b->sx, &b->sy,
			b->heading, b->speed);
	if (movement_is_out_of_bounds (b->sx, b->sy))
		b->gone = true;
}

void
blast_calculate_position (void)
{
	ListElmt *cur = recycle_list_head (recycle);

	while (cur != NULL)
		{
			ListElmt *next = list_next (cur);

			Blast *b = list_data (cur);
			_blast_calculate_position (b);

			if (b->gone)
				recycle_remove_list_element (recycle, cur);

			cur = next;
		}
}

void
blast_fire (Spaceship *s)
{
	interval--;
	if (interval == 0)
		{
			interval = BLAST_INTERVAL;
			sound_play_sample (SOUND_FIRE);
			blast_setup (list_data (recycle_get_list_element (recycle)), s);
		}
}

static void
_blast_draw (Blast *b)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_rotate_transform (&transform, b->heading);
	al_translate_transform (&transform, b->sx, b->sy);
	al_use_transform (&transform);
	al_draw_line(0, 0, 0, -3, b->color, 3.0f);
	/*al_draw_circle (0, 0, 2, al_map_rgb (50, 50, 200), 2.0f);*/
}

void
blast_draw (void)
{
	for (ListElmt *cur = recycle_list_head (recycle); cur != NULL; cur = list_next (cur))
		_blast_draw (list_data (cur));
}

void
blast_init (void)
{
	recycle = recycle_new ((RecycleCreate)blast_new,
			(RecycleDestroy)_blast_free);
}
