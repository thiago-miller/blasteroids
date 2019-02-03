#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include "spaceship.h"
#include "blast.h"
#include "asteroid.h"
#include "input.h"
#include "collision.h"
#include "status.h"
#include "error.h"
#include "blasteroids.h"

static bool done;
static ALLEGRO_EVENT_QUEUE *event_queue;
static ALLEGRO_TIMER *timer;
static ALLEGRO_DISPLAY *display;
static ALLEGRO_BITMAP *background;
static Spaceship *s;

void
blasteroids_init (void)
{
	srand (time (NULL));

	if (!al_init ())
		error ("Failed to initialize allegro");

	if (!al_init_primitives_addon ())
		error ("Failed to initialize primitives addon");

	if (!al_init_image_addon ())
		error ("Failed to initialize image addon");

	if (!al_install_keyboard ())
		error ("Failed to install keyboard");

	timer = al_create_timer (1.0 / FPS);
	if (!timer)
		error ("Failed to create timer");

	al_set_new_display_flags (ALLEGRO_WINDOWED);
	display = al_create_display (DISPLAY_WIDTH, DISPLAY_HEIGH);
	if (!display)
		error ("Failed to create display");

	background = al_load_bitmap ("../assets/image/space.png");
	if (!background)
		error	("failed to load background bitmap");

	event_queue = al_create_event_queue ();
	if (!event_queue)
		error ("Failed to create event queue");

	al_register_event_source (event_queue, al_get_keyboard_event_source ());
	al_register_event_source (event_queue, al_get_timer_event_source (timer));
	al_register_event_source (event_queue, al_get_display_event_source (display));

	done = false;

	s = spaceship_new ();
	blast_init ();
	asteroid_init ();
	status_init ();
}

void
blasteroids_shutdown (void)
{
	if (timer)
		al_destroy_timer (timer);

	if (display)
		al_destroy_display (display);

	if (background)
		al_destroy_bitmap (background);

	if (event_queue)
		al_destroy_event_queue (event_queue);

	spaceship_free (s);
	blast_free ();
	asteroid_free ();
	status_free ();
}

static void
blasteroids_draw_background (void)
{
	ALLEGRO_TRANSFORM transform;
	al_identity_transform (&transform);
	al_use_transform (&transform);
	al_draw_bitmap (background, 0, 0, 0);
}

static void
blasteroids_update_graphics (void)
{
	al_clear_to_color (al_map_rgb (0, 0, 0));
	blasteroids_draw_background ();
	spaceship_draw_ship (s);
	blast_draw ();
	asteroid_draw ();
	status_score (spaceship_get_score (s));
	status_lives (spaceship_get_lives (s));

	if (spaceship_get_lives (s) == 0)
		status_gameover_splash ();

	al_flip_display ();
}

static void
blasteroids_update_logic (void)
{
	input_control_spaceship (s);
	spaceship_calculate_position (s);
	spaceship_calculate_invencibility (s);
	blast_calculate_position ();
	asteroid_control ();
	asteroid_calculate_position ();
	collision_detection (s);
}

static void
blasteroids_reset (void)
{
	al_stop_timer (timer);
	spaceship_reset (s);
	blast_reset ();
	asteroid_reset ();
	al_rest (REST_RESET);
	al_start_timer (timer);
}

void
blasteroids_game_loop (void)
{
	bool redraw = true;
	al_start_timer (timer);

	while (!done)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event (event_queue, &event);

			switch (event.type)
				{
					case ALLEGRO_EVENT_KEY_DOWN:
					case ALLEGRO_EVENT_KEY_UP:
						{
							done = input_get_user_input (&event);
							break;
						}
					case ALLEGRO_EVENT_TIMER:
						{
							redraw = true;
							blasteroids_update_logic ();
							break;
						}
					case ALLEGRO_EVENT_DISPLAY_CLOSE:
						{
							done = true;
							break;
						}
				}

			if (redraw && al_is_event_queue_empty (event_queue))
				{
					redraw = false;
					blasteroids_update_graphics ();
				}

			if (spaceship_get_lives (s) == 0)
				blasteroids_reset ();
		}
}
