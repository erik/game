#ifndef _GAME_H_
#define _GAME_H_
#include <stdio.h>
#include <stdbool.h>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

typedef enum {
     rest,
     walk,
     jump
} MoveState;

typedef struct {
     int x;
     int y, y_velocity;
     bool jump;
     MoveState state;

     double frame;
     int restframes, walkframes, jumpframes;
     SDL_Rect **clips;

     SDL_Surface *image;

     char *name;
} Character;

typedef struct {
     int startTicks;
     int pausedTicks;
     bool paused;
     bool started;
} Timer;

/* util functions */
SDL_Surface *init_sdl(void);
SDL_Surface *load_image(char *filename);
void apply_surface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect* clip);
void handle_keys(bool[], Character*);

/* character functions */
Character *Character_load(char *name);
void Character_draw(Character*, SDL_Surface*);
int Character_next_frame(Character*);
void Character_jump(Character*);

/* timer fuctions */
Timer *Timer_new();
void Timer_start(Timer *t);
void Timer_pause(Timer *t);
void Timer_unpause(Timer *t);
int Timer_get_ticks(Timer *t);

#endif /* _GAME_H_ */
