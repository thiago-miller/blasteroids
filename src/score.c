#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro5.h>
#include <stdio.h>
#include "error.h"
#include "score.h"

#define NUM_SCORES 5

typedef struct {
	char name[80];
	long score;
} HighScore;

static HighScore highscores[NUM_SCORES] =
{
	{ "Dagoberto", 1000000 },
	{ "Rogéria",    750000 },
	{ "Gibimba",    500000 },
	{ "Trolha",     300000 },
	{ "N00b",       100000 }
};

void
score_save (void)
{
	ALLEGRO_CONFIG *cfg = NULL;
	ALLEGRO_PATH *fn = NULL;
	const char *path = NULL;
	char score_str[32];

	cfg = al_create_config ();

	for (int i = 0; i < NUM_SCORES; i++)
		{
			snprintf (score_str, sizeof (score_str), "%ld", highscores[i].score);
			al_set_config_value (cfg, "scores", highscores[i].name, score_str);
		}

	fn = al_get_standard_path (ALLEGRO_USER_DATA_PATH);
	path = al_path_cstr (fn, ALLEGRO_NATIVE_PATH_SEP);

	if (!al_make_directory (path))
		error ("Failed to create directory: '%s'", path);

	al_set_path_filename (fn, "score.ini");
	path = al_path_cstr (fn, ALLEGRO_NATIVE_PATH_SEP);

	if (!al_save_config_file (path, cfg))
		error ("Failed to save '%s'", path);

	al_destroy_path (fn);
	al_destroy_config (cfg);
}
