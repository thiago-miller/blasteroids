#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include "recycle.h"
#include "movement.h"
#include "error.h"
#include "effect.h"

static struct bang_attr
{
	int quant;
	int size;
	int frames;
	float speed;
} bang_attr[EFFECT_BANG_NUM] = {
	{100, 70, 200, 0.5},
	{50, 40, 180, 0.3},
	{25, 20, 150, 0.15}
};

static Recycle *recycle = NULL;

void
effect_reset (void)
{
	ListElmt *cur = recycle_list_head (recycle);

	while (cur != NULL)
		{
			ListElmt *next = list_next (cur);
			recycle_remove_list_element (recycle, cur);
			cur = next;
		}
}

static Effect *
effect_new (void)
{
	Effect *e = calloc (1, sizeof (Effect));
	if (e == NULL)
		error ("Failed to create effect object");
	return e;
}

static void
_effect_free (Effect *e)
{
	if (e == NULL)
		return;
	free (e);
}

void
effect_free (void)
{
	recycle_free (recycle);
}

static void
effect_raffle_position (Effect *e, float sx, float sy, int size)
{
	e->sx = rand () % size;
	e->sx = rand () % 2 ? sx + e->sx : sx - e->sx;
	e->sy = rand () % size;
	e->sy = rand () % 2 ? sy + e->sy : sy - e->sy;
}


static void
effect_setup (Effect *e, EffectBangType type)
{
	e->gone = false;
	e->heading = rand () % 360 * ALLEGRO_PI / 180;
	e->frames = bang_attr[type].frames;
	e->speed = bang_attr[type].speed;
	e->color = EFFECT_COLOR;
}

void
effect_bang (float sx, float sy, EffectBangType type)
{
	for (int i = 0; i < bang_attr[type].quant; i++)
		{
			Effect *e = list_data (recycle_get_list_element (recycle));
			effect_setup (e, type);
			effect_raffle_position (e, sx, sy, bang_attr[type].size);
		}
}

void
effect_control (void)
{
	ListElmt *cur = recycle_list_head (recycle);

	while (cur != NULL)
		{
			ListElmt *next = list_next (cur);
			Effect *e = list_data (cur);

			movement_calculate_2D_position (&e->sx, &e->sy,
					e->heading, e->speed);

			if (movement_is_out_of_bounds (e->sx, e->sy))
				e->gone = true;

			if (e->gone)
				recycle_remove_list_element (recycle, cur);

			if (--e->frames == 0)
				e->gone = true;

			cur = next;
		}
}

static void
_effect_draw (Effect *e)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_rotate_transform (&transform, e->heading);
	al_translate_transform (&transform, e->sx, e->sy);
	al_use_transform (&transform);
	al_draw_triangle (-1, 0, 0, 2, 1, 0, e->color, 0.5);
}

void
effect_draw (void)
{
	for (ListElmt *cur = recycle_list_head (recycle); cur != NULL; cur = list_next (cur))
		_effect_draw (list_data (cur));
}

void
effect_init (void)
{
	recycle = recycle_new ((RecycleCreate)effect_new,
			(RecycleDestroy)_effect_free);
}
