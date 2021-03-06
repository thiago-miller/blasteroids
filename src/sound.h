#ifndef SOUND_H
#define SOUND_H

#define SOUND_RESERVED_SAMPLES 5

typedef enum {
	SOUND_THRUST = 0,
	SOUND_FIRE,
	SOUND_BANG_LARGE,
	SOUND_BANG_MEDIUM,
	SOUND_BANG_SMALL
} SoundSampleType;

void sound_init        (void);
void sound_free        (void);
void sound_play_sample (SoundSampleType type);
void sound_play_music  (void);
void sound_stop_music  (void);

#endif /* sound.h */
