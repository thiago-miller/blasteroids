#ifndef BLASTEROIDS_H
#define BLASTEROIDS_H

#define FPS 60
#define DISPLAY_WIDTH 640
#define DISPLAY_HEIGH 480
#define REST_RESET 4

void blasteroids_init      (void);
void blasteroids_shutdown  (void);
void blasteroids_game_loop (void);

#endif /* blasteroids.h */
