#ifndef BLAST_H
#define BLAST_H

#include <allegro5/allegro.h>
#include "recycle.h"
#include "spaceship.h"

typedef struct
{
	float         sx;
	float         sy;
	float         radius;
	float         heading;
	float         speed;
	int           gone;
	ALLEGRO_COLOR color;
} Blast;

#define BLAST_COLOR al_map_rgb (255, 69, 0)
#define BLAST_RADIUS 2
#define BLAST_SPEED (SPACESHIP_MAX_SPEED) * 3
#define BLAST_PADDING 11
#define BLAST_INTERVAL 4

ListElmt * blast_get_list_head      (void);
void       blast_reset              (void);
void       blast_die                (Blast *b);
void       blast_fire               (Spaceship *s);
void       blast_free               (void);
void       blast_calculate_position (void);
void       blast_draw               (void);
void       blast_init               (void);

#define blast_get_sx(b)      (b->sx)
#define blast_get_sy(b)      (b->sy)
#define blast_get_radius(b)  (b->radius)
#define blast_get_heading(b) (b->heading)
#define blast_get_speed(b)   (b->speed)

#endif /* blast.h */
