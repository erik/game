#include <fstream>

#include "game.h"
#include "character.h"

Character::Character(string n, int x_, int y_) {
  name = n;
  x = x_;
  y = y_;
  velocity_x = velocity_y = 0;
  
  state = rest;
  
  jumping = false;
  image = NULL;

  load();
  
}

Character::~Character() {
  SDL_FreeSurface(image);
}

bool Character::load() {
  using namespace std;
  string charImage("data/" + this->name + ".png");
  string imageData(charImage + ".info");

  ifstream imageFile(charImage.c_str(), ios::binary);
  ifstream infoFile(imageData.c_str());

  if(!imageFile.is_open()) {
    cerr << "can't open image file: " << charImage << endl;
    return false;
  }
  if(!infoFile.is_open()) {
    cerr << "can't open info file: " << imageData << endl;
    return false;
  }

  SDL_Surface *im = LoadImage(charImage);
  if(im == NULL) {
    cerr << "error opening image file" << endl;
    return false;
  }

  /* remove background */
  Uint32 colorkey = SDL_MapRGB(im->format, CHARACTER_BACK);
  SDL_SetColorKey(im, SDL_SRCCOLORKEY, colorkey);
  image = im;

  int r, w, j;  
  infoFile >> r >> w >> j;
  numframes[REST_INDEX] = r;
  numframes[WALK_INDEX] = w;
  numframes[JUMP_INDEX] = j;

  for(int x = 0; x < 3; x++) {
    int ctr = -1;
    switch(x) {
      case REST_INDEX:
	ctr = r;
	break;
      case WALK_INDEX:
	ctr = w;
	break;
      case JUMP_INDEX:
	ctr = j;
	break;
    }
    SDL_Rect* tempptr = new SDL_Rect[ctr];
    for(int i = 0; i < ctr; i++) {
      SDL_Rect tmp;
      tmp.x = i * CHARACTER_WIDTH;
      tmp.y = x * CHARACTER_HEIGHT;
      tmp.w = CHARACTER_WIDTH;
      tmp.h = CHARACTER_HEIGHT;
      tempptr[i] = tmp;
    }
    clips[x] = tempptr;
  }

  return true;
}

void Character::draw(SDL_Surface* screen) {
  SDL_Rect clip;
  int frame = static_cast<int>(this->frame);
  clip = clips[state][frame];
  ApplySurface(x, y, image, screen, &clip);
}

int Character::nextFrame() {
  int frames = numframes[state];
  frame = frame + FRAME_STEP;
  if(this->frame >= frames) {
    frame = 0;
  }
  return (static_cast<int>(frame)) % frames;
}

void Character::handleKeys(const bool keys[]) {
  bool moved = false;
  
  if(keys[SDLK_UP] && !jumping) {
    state = jump;
    frame = 0;
    jumping = true;
    velocity_y = Y_VELOCITY_STEP;
    y += Y_VELOCITY_STEP;
    moved = true;
  }
  if(jumping) {
    moved = true;
    if(y + velocity_y < HEIGHT - CHARACTER_HEIGHT) {
      y = y + velocity_y;
      velocity_y = velocity_y + GRAVITY;
    } else {
      jumping = false;
      moved = false;
      velocity_y = 0;
      y = HEIGHT - CHARACTER_HEIGHT;
    }
  }
  if(keys[SDLK_RIGHT]) {
    x += CHARACTER_STEP;
    moved = true;
  }
  if(keys[SDLK_LEFT]) {
    x -= CHARACTER_STEP;
    moved = true;
  }
  
  if(moved && !jumping) {
    state = walk;
  }
  
  if(!moved) {
    state = rest;
  }
}
