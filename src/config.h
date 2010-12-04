#ifndef _CONFIG_H_
#define _CONFIG_H_

#define WIDTH 800
#define HEIGHT 600
#define DEPTH 32
#define WINDOW_TITLE "A Game"

#define REST_INDEX 0
#define WALK_INDEX 1
#define JUMP_INDEX 2
#define ATTACK_INDEX 3

#define NUMSTATES 4

#define CHARACTER_WIDTH 96
#define CHARACTER_HEIGHT 96

#define CHARACTER_BACK 0x00, 0x80,0x00

#define CHARACTER_STEP 10

#define FRAME_STEP .3

#define FPS 30

#define GRAVITY 2
#define Y_VELOCITY_STEP -20

#define BULLET_SPEED 15
#define BULLET_DELAY 200

#endif /* _CONFIG_H_ */
