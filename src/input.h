#ifndef INPUT_H
#define INPUT_H

#include <allegro5/allegro.h>
#include "spaceship.h"

bool input_get_user_input (ALLEGRO_EVENT *event);
void input_control_spaceship (Spaceship *s);

#endif /* input.c */
