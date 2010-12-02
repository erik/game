#include "fog.h"

Fog::Fog(SDL_Surface* s) {
  fog = s;
  x = y = x_ = y_ = 0;
  w = s->w;
  h = s->h;
}

void Fog::scroll() {
  x -= Fog::step;
  if(x <= -w) {
    this->reset();
  }
}

void Fog::reset() {
  x = x_;
  y = y_;
}

void Fog::draw(SDL_Surface* screen) {
  ApplySurface(x, y, fog, screen);
  if(x <= -w + WIDTH) {
    ApplySurface(x + w, y, fog, screen);
  }
}
