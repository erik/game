#include "game.h"
#include "config.h"

Timer *Timer_new()
{
     Timer *t = malloc(sizeof(Timer));
     t->startTicks = 0;
     t->pausedTicks = 0;
     t->paused = false;
     t->started = false;
     return t;
}

void Timer_start(Timer *t)
{
     t->started = true;
     t->paused = false;
     t->startTicks = SDL_GetTicks();
}

void Timer_pause(Timer *t)
{
     if(t->started && !t->paused) {
          t->paused = true;
          t->pausedTicks = SDL_GetTicks() - t->startTicks;
     }
}

void Timer_unpause(Timer *t)
{
     if(t->paused) {
          t->paused = false;
          t->startTicks = SDL_GetTicks() - t->pausedTicks;
          t->pausedTicks = 0;
     }
}

int Timer_get_ticks(Timer *t)
{
     if(t->started) {
          if(t->paused) {
               return t->pausedTicks;
          }
          return SDL_GetTicks() - t->startTicks;
     }
     return 0;
}
