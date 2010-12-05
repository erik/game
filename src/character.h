#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "bullet.h"

#include <vector>
#include <fstream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Character {
private:
  string name;
  int x, y;
  double velocity_x, velocity_y;

  int life;
  
  double frame;
  int numframes[NUMSTATES]; // rest, walk, jump, attack
  
  MoveState state;
  
  bool jumping;

  SDL_Rect *clips[NUMSTATES]; // rest, walk, jump, attack
  SDL_Surface *image;

  SDL_Surface *bulletImage;
  std::vector<Bullet> bullets;
  Uint32 lastShot;

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
  void fire();

  void hit(int damage=ZOMBIE_DAMAGE) {life -= damage; }
  bool alive() { return life > 0; }
  int health() { return life; }

};

#endif /*_CHARACTER_H_*/
