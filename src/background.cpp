#include "background.h"

Background::Background(SDL_Surface* s) {
  image = s;
  x = y= x_ = y_ = 0;
  w = s->w;
  h = s->h;
}

void Background::scroll() {
  x -= Background::step;
  if(x <= -w) {
    this->reset();
  }
}

void Background::unscroll() {
  x += Background::step;
  if(x <= -w) {
    this->reset();
  }
}

void Background::reset() {
  x = x_;
  y = y_;
}

void Background::draw(SDL_Surface* screen) {
  ApplySurface(x, y, image, screen);
  if(x <= -w + WIDTH) {
    ApplySurface(x + w, y, image, screen);
  }
}
