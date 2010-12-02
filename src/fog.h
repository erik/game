#ifndef _FOG_H_
#define _FOG_H_

#include "game.h"

class Fog {
  const static int step = 2;
private:
  SDL_Surface* fog;
  int x, y, x_, y_;
  int w, h;
public:
  Fog(SDL_Surface*);

  void setX(int v) { x = x_ = v; }
  void setY(int v) { y = y_ = v; }
  void setXY(int a, int b) { x = x_ = a; y = y_ = b; }

  void scroll();
  void reset();
  void draw(SDL_Surface*);
};

#endif /* _FOG_H_ */
