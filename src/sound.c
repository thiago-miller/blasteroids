#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "error.h"
#include "sound.h"

static ALLEGRO_AUDIO_STREAM *music;
static ALLEGRO_SAMPLE *samples[SOUND_RESERVED_SAMPLES] = {};

static const char *samples_path[SOUND_RESERVED_SAMPLES] =
{
	"../assets/sound/thrust.wav",
	"../assets/sound/fire.wav",
	"../assets/sound/bangLarge.wav",
	"../assets/sound/bangMedium.wav",
	"../assets/sound/bangSmall.wav"
};

static const char *music_path = "../assets/music/01-speedway.ogg";

void
sound_init (void)
{
	if (!al_install_audio ())
		error ("Failed to install audio");

	if (!al_init_acodec_addon ())
		error ("Failed to initialize audio codecs");

	if (!al_reserve_samples (SOUND_RESERVED_SAMPLES))
		error ("Failed to reserve samples");

	music = al_load_audio_stream (music_path, 4, 1024);
	if (!music)
		error ("Failed to load '%s' music", music_path);

	if (!al_set_audio_stream_playmode (music, ALLEGRO_PLAYMODE_LOOP))
		error ("Failed to set playmode to '%s'", music_path);

	if (!al_attach_audio_stream_to_mixer (music, al_get_default_mixer ()))
		error ("Failed to attach audio stream to mixer");

	for (int i = 0; i < SOUND_RESERVED_SAMPLES; i++)
		{
			ALLEGRO_SAMPLE *sample = al_load_sample (samples_path[i]);
			if (!sample)
				error ("Failed to load '%s' sample", samples_path[i]);
			samples[i] = sample;
		}
}

void
sound_free (void)
{
	if (music)
		al_destroy_audio_stream (music);

	for (int i = 0; i < SOUND_RESERVED_SAMPLES; i++)
		{
			ALLEGRO_SAMPLE *sample = samples[i];
			if (sample)
				al_destroy_sample (sample);
		}
}

void
sound_play_sample (sound_sample_type type)
{
	al_play_sample (samples[type], 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, NULL);
}

void
sound_play_music (void)
{
	al_set_audio_stream_playing (music, true);
}

void
sound_stop_music (void)
{
	al_set_audio_stream_playing (music, false);
}
