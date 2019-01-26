#if HAVE_CONFIG_H
# include <config.h>
#endif

#include <allegro5/allegro5.h>
#include <spaceship.h>
#include <error.h>

#define FPS 60
#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGH 480
#define SPACESHIP_COLOR al_map_rgb (0, 100, 0)
#define MAX_SPEED 5

static bool done;
static ALLEGRO_EVENT_QUEUE* event_queue;
static ALLEGRO_TIMER* timer;
static ALLEGRO_DISPLAY* display;
static Spaceship *s;

void
blasteroids_init (void)
{
	if (!al_init ())
		error ("Failed to initialize allegro");

	if (!al_install_keyboard ())
		error ("Failed to install keyboard");

	timer = al_create_timer (1.0 / FPS);
	if (!timer)
		error ("Failed to create timer");

	al_set_new_display_flags (ALLEGRO_WINDOWED);
	display = al_create_display (DISPLAY_WIDTH, DISPLAY_HEIGH);
	if (!display)
		error ("Failed to create display");

	event_queue = al_create_event_queue ();
	if (!event_queue)
		error ("Failed to create event queue");

	al_register_event_source (event_queue, al_get_keyboard_event_source ());
	al_register_event_source (event_queue, al_get_timer_event_source (timer));
	al_register_event_source (event_queue, al_get_display_event_source (display));

	done = false;

	s = spaceship_new (al_get_display_width (display) / 2,
			al_get_display_height (display) / 2, SPACESHIP_COLOR);
}

void
blasteroids_shutdown (void)
{
	if (timer)
		al_destroy_timer(timer);

	if (display)
		al_destroy_display (display);

	if (event_queue)
		al_destroy_event_queue (event_queue);

	if (s)
		spaceship_free (s);
}

static void
blasteroids_draw (void)
{
	spaceship_draw_ship (s);
}

static void
blasteroids_spaceshift_move (void)
{
	float sx, sy;
	spaceship_move (s);
	spaceship_get_pos (s, &sx, &sy);

	if (sx < 0) sx = 0;
	if (sx > DISPLAY_WIDTH) sx = DISPLAY_WIDTH;
	if (sy < 0) sy = 0;
	if (sy > DISPLAY_HEIGH) sy = DISPLAY_HEIGH;

	spaceship_set_pos (s, sx, sy);
}

static void
blasteroids_update_logic (void)
{
	blasteroids_spaceshift_move ();
}

void
blasteroids_game_loop (void)
{
	bool redraw = true;
	al_start_timer(timer);

	while (!done)
		{
			ALLEGRO_EVENT event;
			al_wait_for_event(event_queue, &event);

			if (event.type == ALLEGRO_EVENT_TIMER)
				{
					redraw = true;
					//update_logic();
					blasteroids_update_logic ();
				}
			else if (event.type == ALLEGRO_EVENT_KEY_CHAR)
				{
					//get_user_input();
					switch (event.keyboard.keycode)
						{
						case ALLEGRO_KEY_ESCAPE:
							{
								done = true;
								break;
							}
						case ALLEGRO_KEY_LEFT:
							{
								spaceship_rotate_left (s, ALLEGRO_PI/30); // 4*
								break;
							}
						case ALLEGRO_KEY_RIGHT:
							{
								spaceship_rotate_right (s, ALLEGRO_PI/30);
								break;
							}
						case ALLEGRO_KEY_UP:
							{
								spaceship_accelerate (s, 0.4);
								if (spaceship_get_speed (s) > MAX_SPEED)
									spaceship_set_speed (s, MAX_SPEED);
								break;
							}
						case ALLEGRO_KEY_DOWN:
							{
								spaceship_decelerate (s, 0.4);
								if (spaceship_get_speed (s) < 0)
									spaceship_set_speed (s, 0);
								break;
							}
						}
				}

			if (redraw && al_is_event_queue_empty(event_queue))
				{
					redraw = false;
					al_clear_to_color(al_map_rgb(0, 0, 0));
					//update_graphics();
					blasteroids_draw ();
					al_flip_display();
				}
		}
}
