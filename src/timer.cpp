#include "timer.h"
#include "game.h"
#include "config.h"

Timer::Timer() {
  startTicks = pausedTicks = 0;
  paused = started = false;
}

void Timer::start() {
  started = true;
  paused = false;
  startTicks = SDL_GetTicks();
}

void Timer::pause() {
  if(started && !paused) {
    paused = true;
    pausedTicks = SDL_GetTicks() - startTicks;
  }
}

void Timer::unpause() {
  if(paused) {
    paused = false;
    startTicks = SDL_GetTicks() - pausedTicks;
    pausedTicks = 0;
  }
}

int Timer::getTicks() {
  if(started) {
    if(paused) {
      return pausedTicks;
    } else {
      return SDL_GetTicks() - startTicks;
    }
  }
  return 0;
}

