#include "zombie.h"

Zombie::Zombie(string n, int x_, int y_) {
  name = n;
  x = x_;
  y = y_;
  
  life = 50;

  state = ZRestState;

  if(!this->load()) {
    FATAL("couldn't create zombie instance!");
  }
}

Zombie::~Zombie() {
}

bool Zombie::load() {
  using std::ifstream;
  string zImage("data/" + this->name + ".png");
  string imageData(zImage + ".info");

  ifstream imageFile(zImage.c_str(), std::ios::binary);
  ifstream infoFile(imageData.c_str());

  if(!imageFile.is_open()) {
    cerr << "can't open image file: " << zImage << endl;
    return false;
  }
  if(!infoFile.is_open()) {
    cerr << "can't open info file: " << imageData << endl;
    return false;
  }

  image = LoadImage(zImage, true);
  
  int r, w, d, a;
  infoFile >> r >> w >> d >> a;
  numframes[ZREST_INDEX] = r;
  numframes[ZWALK_INDEX] = w;
  numframes[ZDEATH_INDEX] = d;
  numframes[ZATTACK_INDEX] = a;

  for(int i = 0; i < ZNUMSTATES; ++i) {
    int ctr = -1;
    switch(i) {
      case ZREST_INDEX: 
	ctr = r;
	break;
      case ZWALK_INDEX:
	ctr = w;
	break;
      case ZDEATH_INDEX:
	ctr = d;
	break;
      case ZATTACK_INDEX:
	ctr = a;
	break;
    }

    SDL_Rect* tmpptr = new SDL_Rect[ctr];
    for(int x = 0; x < ctr; ++x) {
      SDL_Rect tmp;
      tmp.x = x * ZOMBIE_WIDTH;
      tmp.y = i * ZOMBIE_HEIGHT;
      tmp.w = ZOMBIE_WIDTH;
      tmp.h = ZOMBIE_HEIGHT;
      tmpptr[x] = tmp;
    }
    clips[i] = tmpptr;
  }

  return true;  
}


void Zombie::draw(SDL_Surface* screen) {
  SDL_Rect clip;
  int frame = static_cast<int>(this->frame);
  clip = clips[state][frame];
  ApplySurface(x, y, image, screen, &clip);
}

int Zombie::nextFrame() {
  int frames = numframes[state];
  frame = frame + .1;
  if(this->frame >= frames) {
    frame = 0;
    if(this->state == ZAttackState) {
      state = ZRestState;
    }
  }
  return (static_cast<int>(frame)) % frames;
}

void Zombie::reactToPlayer(Character* c) {
  int playerx = c->getX() + CHARACTER_WIDTH;
  // unused
  // int playery = c->getY() + CHARACTER_HEIGHT / 2;
  
  if(state == ZDeathState || life <= 0) {
    state = ZDeathState;
    return;
  }
  

  if(abs(x - playerx) < ZOMBIE_WIDTH / 4) {
    if(state != ZAttackState) frame = 0;
    state = ZAttackState;
    //TODO: Actual collision detection
    c->hit();
  } else {
    state = ZWalkState;
    if(playerx < x) {       
      x -= ZOMBIE_STEP;
    } else {
      x += ZOMBIE_STEP;
    }
  }
}
