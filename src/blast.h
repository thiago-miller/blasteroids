#ifndef BLAST_H
#define BLAST_H

#include <allegro5/allegro.h>
#include "spaceship.h"

#define BLAST_COLOR al_map_rgb (255, 0, 0)
#define BLAST_SPEED (SPACESHIP_MAX_SPEED) * 3
#define BLAST_PADDING 11

typedef struct
{
	float         sx;
	float         sy;
	float         heading;
	float         speed;
	int           gone;
	ALLEGRO_COLOR color;
} Blast;

void blast_fire (Spaceship *s);
void blast_free (Blast *b);
void blast_calculate_position (void);
void blast_draw (void);

#endif /* blast.h */
