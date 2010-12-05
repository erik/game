#ifndef _BULLET_H_
#define _BULLET_H_

#include "game.h"

class Bullet {
private:
  int x, y;
  int xmove, ymove;
  SDL_Surface* image;
public:
  const static int MaxDistance = WIDTH;
  int dx, dy;

  Bullet(SDL_Surface *); 
  Bullet(SDL_Surface*, int, int);
  Bullet(SDL_Surface*, int, int, int, int);
  
  void setXMove(int v) { xmove = v; }
  void setYMove(int v) { ymove = v; }

  int getX() { return x; }
  int getY() { return y; }

  void setX(int v) { x = v; }
  void setY(int v) {y = v; }
  void setXY(int a, int b) { x = a; y = b; }

  void move();
  void draw(SDL_Surface*);
};


#endif /* _BULLET_H_ */
