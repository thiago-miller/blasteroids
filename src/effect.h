#ifndef EFFECT_H
#define EFFECT_H

typedef struct
{
	float         sx;
	float         sy;
	float         heading;
	float         speed;
	int           frames;
	bool          gone;
	ALLEGRO_COLOR color;
} Effect;

#define EFFECT_BANG_NUM 3
#define EFFECT_COLOR al_map_rgb (255, 255, 255);

typedef enum
{
	EFFECT_BANG_LARGE = 0,
	EFFECT_BANG_MEDIUM,
	EFFECT_BANG_SMALL
} EffectBangType;

void effect_reset   (void);
void effect_free    (void);
void effect_control (void);
void effect_draw    (void);
void effect_init    (void);
void effect_bang    (float sx, float sy, EffectBangType type);

#endif /* effect.h */
