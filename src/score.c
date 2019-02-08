#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "score.h"

#define NUM_SCORES 5
#define NAME_BUFSIZ 80
#define SCORE_BUFSIZ 32

typedef struct {
	char name[NAME_BUFSIZ];
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
	char score_str[SCORE_BUFSIZ];

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

void
score_load (void)
{
	ALLEGRO_PATH *fn = NULL;
	ALLEGRO_CONFIG *cfg = NULL;
	const char *path = NULL;

	fn = al_get_standard_path (ALLEGRO_USER_DATA_PATH);
	al_set_path_filename (fn, "score.ini");

	path = al_path_cstr (fn, ALLEGRO_NATIVE_PATH_SEP);
	cfg = al_load_config_file (path);

	if (cfg)
		{
			ALLEGRO_CONFIG_ENTRY *iterator = NULL;
			const char *name = al_get_first_config_entry (cfg, "scores",
					&iterator);

			for (int i = 0; i < NUM_SCORES; i++)
				{
					if (name == NULL)
						break;
					strncpy (highscores[i].name, name, NAME_BUFSIZ);
					const char *score = al_get_config_value (cfg, "scores", name);
					highscores[i].score = atol (score);
					name = al_get_next_config_entry (&iterator);
				}

			al_destroy_config (cfg);
		}

	al_destroy_path (fn);
}

void
score_print (void)
{
	score_load ();
	for (int i = 0; i < NUM_SCORES; i++)
		printf ("%s = %ld\n", highscores[i].name, highscores[i].score);
}

void
score_insert (const char *name, long score)
{
	int i = 0;

	for (; i < NUM_SCORES; i++)
		{
			if (score > highscores[i].score)
				break;
		}

	if (i == NUM_SCORES)
		return;

	for (int j = NUM_SCORES - 1; j > i; j --)
		{
			strncpy (highscores[j].name, highscores[j - 1].name, NAME_BUFSIZ);
			highscores[j].score = highscores[j - 1].score;
		}

	strncpy (highscores[i].name, name, NAME_BUFSIZ);
	highscores[i].score = score;
}
