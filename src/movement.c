#include <math.h>
#include "blasteroids.h"
#include "movement.h"

void
movement_calculate_2D_position (float *sx, float *sy, float heading, float speed)
{
	*sy -= speed * cos (heading);
	*sx += speed * sin (heading);
}

void
movement_teleport (float *sx, float *sy)
{
	if (*sx < 0)
		*sx = DISPLAY_WIDTH;
	else if (*sx > DISPLAY_WIDTH)
		*sx = 0;
	if (*sy < 0)
		*sy = DISPLAY_HEIGH;
	else if (*sy > DISPLAY_HEIGH)
		*sy = 0;
}
