#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "blasteroids.h"
#include "movement.h"
#include "error.h"
#include "blast.h"

static Blast *tmp = NULL;

static Blast *
blast_new (void)
{
	Blast *b = calloc (1, sizeof (Blast));
	if (b == NULL)
		error ("Failed to create blast object");

	b->color = BLAST_COLOR;
	b->speed = BLAST_SPEED;

	return b;
}

static void
blast_setup (Blast *b, Spaceship *s)
{
	b->heading = spaceship_get_heading (s);
	spaceship_get_pos (s, &b->sx, &b->sy);
	movement_calculate_2D_position (&b->sx, &b->sy,
			b->heading, BLAST_PADDING);
}

void
blast_free (Blast *b)
{
	if (b == NULL)
		return;
	free (b);
}

static void
check_if_blast_out_of_bounds (Blast *b)
{
	if (b->sx > DISPLAY_WIDTH || b->sx < 0)
		b->gone = true;
	if (b->sy > DISPLAY_WIDTH || b->sy < 0)
		b->gone = true;
}

void
blast_calculate_position (void)
{
	if (tmp == NULL) return;
	movement_calculate_2D_position (&tmp->sx, &tmp->sy,
			tmp->heading, tmp->speed);
	check_if_blast_out_of_bounds (tmp);
}

void
blast_fire (Spaceship *s)
{
	tmp = blast_new ();
	blast_setup (tmp, s);
}

void
blast_draw (void)
{
	if (tmp == NULL) return;
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_rotate_transform (&transform, tmp->heading);
	al_translate_transform (&transform, tmp->sx, tmp->sy);
	al_use_transform (&transform);

	al_draw_line(0, 0, 0, -3, tmp->color, 2.0f);
}
