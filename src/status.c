#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include "blasteroids.h"
#include "error.h"
#include "status.h"

static ALLEGRO_FONT *font = NULL;

void
status_init (void)
{
	al_init_font_addon ();
	font = al_create_builtin_font ();
	if (!font)
		error ("Failed to install builtin font");
}

void
status_free (void)
{
	if (font)
		al_destroy_font (font);
}

void
status_score (long score)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_translate_transform (&transform, 5, 10);
	al_scale_transform (&transform, 2.0f, 2.0f);
	al_use_transform (&transform);
	al_draw_textf (font, STATUS_FONT_COLOR, 0, 0, ALLEGRO_ALIGN_LEFT, "%d", score);
}

void
status_lives (int lives)
{
	for (int i = 0; i < lives; i++)
		{
			ALLEGRO_TRANSFORM transform;
			al_identity_transform (&transform);
			al_translate_transform (&transform, 17 + 25 * i, 55);
			al_use_transform (&transform);
			al_draw_line (-8, 9, 0, -11, al_map_rgb (0, 255, 0), 3.0f);
			al_draw_line (0, -11, 8, 9, al_map_rgb (0, 255, 0), 3.0f);
			al_draw_line (-6, 4, -1, 4, al_map_rgb (0, 255, 0), 3.0f);
			al_draw_line (6, 4, 1, 4, al_map_rgb (0, 255, 0), 3.0f);
		}
}

void
status_gameover_splash (void)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_scale_transform (&transform, 3.0f, 3.0f);
	al_translate_transform (&transform, DISPLAY_WIDTH / 2, DISPLAY_HEIGH / 2);
	al_use_transform (&transform);
	al_draw_text (font, STATUS_GAMEOVER_COLOR, 0, 0, ALLEGRO_ALIGN_CENTER, "Game Over");
}
