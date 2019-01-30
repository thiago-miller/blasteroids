#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "blasteroids.h"
#include "movement.h"
#include "list.h"
#include "error.h"
#include "blast.h"

static List *blast_trash = NULL;
static List *blast_live = NULL;

static void
blast_setup (Blast *b, Spaceship *s)
{
	b->gone = false;
	b->heading = spaceship_get_heading (s);
	spaceship_get_pos (s, &b->sx, &b->sy);
	movement_calculate_2D_position (&b->sx, &b->sy,
			b->heading, BLAST_PADDING);
}

static Blast *
blast_new (Spaceship *s)
{
	Blast *b = calloc (1, sizeof (Blast));
	if (b == NULL)
		error ("Failed to create blast object");

	b->color = BLAST_COLOR;
	b->speed = BLAST_SPEED;

	blast_setup (b, s);
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
	list_free (blast_live, (list_clean_data_fun) _blast_free);
	list_free (blast_trash, (list_clean_data_fun) _blast_free);
}

static void
check_if_blast_out_of_bounds (Blast *b)
{
	if (b->sx > DISPLAY_WIDTH || b->sx < 0)
		b->gone = true;
	if (b->sy > DISPLAY_WIDTH || b->sy < 0)
		b->gone = true;
}

static void
_blast_calculate_position (Blast *b)
{
	movement_calculate_2D_position (&b->sx, &b->sy,
			b->heading, b->speed);
	check_if_blast_out_of_bounds (b);
}

void
blast_calculate_position (void)
{
	List *cur = blast_live;

	while (cur != NULL)
		{
			List *next = list_next (cur);

			Blast *b = list_data (cur);
			_blast_calculate_position (b);

			if (b->gone)
				{
					blast_live = list_remove_link (blast_live, cur);
					blast_trash = list_concat (cur, blast_trash);
				}

			cur = next;
		}
}

static List *
blast_trash_recycle (Spaceship *s)
{
	List *shift = blast_trash;
	blast_trash = list_remove_link (blast_trash, shift);
	blast_setup (list_data (shift), s);
	return shift;
}

void
blast_fire (Spaceship *s)
{
	if (blast_trash == NULL)
		blast_live = list_ins_prev (blast_live, blast_new (s));
	else
		blast_live = list_concat (blast_trash_recycle (s), blast_live);
}

static void
_blast_draw (Blast *b)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_rotate_transform (&transform, b->heading);
	al_translate_transform (&transform, b->sx, b->sy);
	al_use_transform (&transform);
	al_draw_line(0, 0, 0, -3, b->color, 2.0f);
	/*al_draw_circle (0, 0, 2, al_map_rgb (50, 50, 200), 2.0f);*/
}

void
blast_draw (void)
{
	for (List *cur = blast_live; cur != NULL; cur = list_next (cur))
		_blast_draw (list_data (cur));
}
