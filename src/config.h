#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Game config */
#define WIDTH            800
#define HEIGHT           600
#define DEPTH            32
#define WINDOW_TITLE     "A Game"

#define FPS              30
#define GRAVITY          2
#define Y_VELOCITY_STEP  -20

#define FRAME_STEP       0.3

/* Character */
#define CHARACTER_WIDTH  96
#define CHARACTER_HEIGHT 96
#define CHARACTER_BACK   0x00, 0x80,0x00
#define CHARACTER_STEP   10

#define REST_INDEX       0
#define WALK_INDEX       1
#define JUMP_INDEX       2
#define ATTACK_INDEX     3

#define NUMSTATES        4

#define BULLET_SPEED     15
#define BULLET_DELAY     200
#define BULLET_DAMAGE    15

/* Zombie */
#define ZOMBIE_WIDTH     96
#define ZOMBIE_HEIGHT    96
#define ZOMBIE_STEP      2

#define ZREST_INDEX      0
#define ZWALK_INDEX      1
#define ZDEATH_INDEX     2
#define ZATTACK_INDEX    3

#define ZNUMSTATES       4

#define ZOMBIE_DAMAGE    6

#endif /* _CONFIG_H_ */
