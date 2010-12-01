#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Character {
 private:
  string name;
  int x, y;
  double velocity_x, velocity_y;
  
  double frame;
  int numframes[3]; // rest, walk, jump
  
  MoveState state;
  
  bool jumping;

  SDL_Rect *clips[3]; // rest, walk, jump
  SDL_Surface *image;
 public:
  Character(std::string, int, int);
  Character() { };
  ~Character();
  bool load();
  void draw(SDL_Surface*);
  int nextFrame();
  void handleKeys(const bool[]);
  int getX() { return x; }
  int getY() { return y; }
  void setX(int v) { x = v; }
  void setY(int v) { y = v; }
};

#endif /*_CHARACTER_H_*/
