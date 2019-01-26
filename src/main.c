#include <blasteroids.h>

int
main (int argc, char *argv[])
{
	blasteroids_init ();
	blasteroids_game_loop ();
	blasteroids_shutdown ();
	return 0;
}
