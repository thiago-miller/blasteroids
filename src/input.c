#include "blast.h"
#include "input.h"

static struct keys
{
	bool left;
	bool right;
	bool up;
	bool down;
	bool space;
} keys = { false };

void
input_control_spaceship (Spaceship *s)
{
	if (keys.left) spaceship_rotate_left (s);
	if (keys.right) spaceship_rotate_right (s);

	if (keys.up)
		spaceship_accelerate (s);
	else
		spaceship_drift (s);

	if (keys.down) spaceship_decelerate (s);

	if (keys.space)
		blast_fire (s);
}

bool
input_get_user_input (ALLEGRO_EVENT *event)
{
	switch (event->keyboard.keycode)
		{
		case ALLEGRO_KEY_LEFT:
		case ALLEGRO_KEY_A:
			{
				keys.left = (event->type == ALLEGRO_EVENT_KEY_DOWN);
				return false;
			}
		case ALLEGRO_KEY_RIGHT:
		case ALLEGRO_KEY_D:
			{
				keys.right = (event->type == ALLEGRO_EVENT_KEY_DOWN);
				return false;
			}
		case ALLEGRO_KEY_UP:
		case ALLEGRO_KEY_W:
			{
				keys.up = (event->type == ALLEGRO_EVENT_KEY_DOWN);
				return false;
			}
		case ALLEGRO_KEY_DOWN:
		case ALLEGRO_KEY_S:
			{
				keys.down = (event->type == ALLEGRO_EVENT_KEY_DOWN);
				return false;
			}
		case ALLEGRO_KEY_SPACE:
			{
				keys.space = (event->type == ALLEGRO_EVENT_KEY_DOWN);
				return false;
			}
		case ALLEGRO_KEY_ESCAPE:
			{
				return true;
			}
		default:
			{
				return false;
			}
		}
}
