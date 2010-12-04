#include "bullet.h"

Bullet::Bullet(SDL_Surface* i) {
  image = i;
  x = y= xmove = ymove = 0;
}

Bullet::Bullet(SDL_Surface* i, int x_, int y_) {
  image = i;
  x = x_;
  y = y_;
  xmove = ymove = 0;
}

Bullet::Bullet(SDL_Surface* i, int x_, int y_, int dx, int dy) {
  image = i;
  x = x_;
  y = y_;
  xmove = dx;
  ymove = dy;
}

void Bullet::move() {
  x += xmove;
  y += ymove;
}

void Bullet::draw(SDL_Surface* s) {
  ApplySurface(x, y, image, s);
}
