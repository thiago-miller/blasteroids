#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <math.h>
#include "list.h"
#include "spaceship.h"
#include "asteroid.h"
#include "blast.h"
#include "collision.h"

static bool
has_collision (float rad1, float sx1, float sy1,
		float rad2, float sx2, float sy2)
{
	float distance = sqrt (powf (sx1 - sx2, 2) + powf (sy1 - sy2, 2));
	return distance <= (rad1 + rad2);
}

void
collision_detection (Spaceship *s)
{
	for (ListElmt *cur_a = asteroid_get_list_head (); cur_a != NULL; cur_a = list_next (cur_a))
		{
			Asteroid *a = list_data (cur_a);

			if (has_collision (asteroid_get_radius (a), asteroid_get_sx (a),
						asteroid_get_sy (a), spaceship_get_radius (s), spaceship_get_sx (s),
						spaceship_get_sy (s)) && !spaceship_is_invincible (s))
				{
					spaceship_add_points (s, ASTEROID_REWARD_POINTS);
					spaceship_die (s);
					asteroid_die (a);
				}

			for (ListElmt *cur_b = blast_get_list_head (); cur_b != NULL; cur_b = list_next (cur_b))
				{
					Blast *b = list_data (cur_b);
					if (has_collision (asteroid_get_radius (a), asteroid_get_sx (a),
								asteroid_get_sy (a), blast_get_radius (b), blast_get_sx (b), blast_get_sy (b)))
						{
							spaceship_add_points (s, ASTEROID_REWARD_POINTS);
							asteroid_die (a);
							blast_die (b);
							break;
						}
				}
		}
}
