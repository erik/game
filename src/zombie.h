#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include <iostream>
#include <fstream>

#include "game.h"
#include "character.h"

// TODO: inherit from Character? //
class Zombie {
private:
  string name;
  int x, y;  

  int life;
  
  double frame;
  int numframes[ZNUMSTATES]; /* rest, walk, death, attack */
  
  ZombieState state;

  SDL_Rect *clips[ZNUMSTATES];
  SDL_Surface *image;

public:
  Zombie(std::string, int, int); 
  Zombie() {};
  ~Zombie();
  
  bool load();
  void draw(SDL_Surface*);
  int nextFrame();
  void reactToPlayer(Character*);
  void attack() { state = ZAttackState; }

  int getX() { return x; }
  int getY() { return y; }
  void setX(int v) { x = v; }
  void setY(int v) { y = v; }
  void setXY(int a, int b) { x = a; y = b; }

  void hit(int damage=BULLET_DAMAGE) { life -= damage; }
  
  bool alive() { return life > 0; }
  int health() { return life; }

};

#endif /* _ZOMBIE_H_ */
