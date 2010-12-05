#include "game.h"
#include "character.h"
#include "music.h"
#include "fog.h"
#include "background.h"
#include "zombie.h"

#include <vector>

int main(int argc, char** argv) {
  SDL_Surface *screen = InitSDL();
  Background background(LoadImage("data/back.png", true));
  Fog fog(LoadImage("data/fog.png", true));
  fog.setXY(0, 300);

  Music::init();
  Music music("data/music.ogg");
  music.loop();

  SDL_Event event;
  bool quit = false;
  Character player("xeon", 0, HEIGHT - CHARACTER_HEIGHT);
  Timer fps;

  bool keys[256];
  for(int i = 0; i < 256; ++i) {
    keys[i] = false;
  }

  Zombie zom("zombie", WIDTH - ZOMBIE_WIDTH / 2, HEIGHT - CHARACTER_HEIGHT);

  background.draw(screen);
  player.draw(screen);
  fog.draw(screen);
  zom.draw(screen);

  SDL_Flip(screen);

  while(!quit) {
    fps.start();

    while(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_QUIT:
	  quit = true;
	  break;
        case SDL_KEYDOWN:
	  keys[event.key.keysym.sym] = true;
	  break;
        case SDL_KEYUP:
	  keys[event.key.keysym.sym] = false;
	  break;
      }
    }
    player.handleKeys(keys);

    if(player.getX() < 0) {
      player.setX(0);
    } else if(player.getX() > WIDTH - CHARACTER_WIDTH) {
      player.setX(WIDTH - CHARACTER_WIDTH);
    }

    /*if(keys[SDLK_LEFT]) {
      background.unscroll();
    }
    if(keys[SDLK_RIGHT]) {
      background.scroll();
    }*/
    
    player.nextFrame();
    zom.reactToPlayer(&player);
    zom.nextFrame();
    fog.scroll();

    background.draw(screen);
    player.draw(screen);
    zom.draw(screen);
    fog.draw(screen);

    SDL_Flip(screen);
    
    if(fps.getTicks() < 1000 / FPS) {
      SDL_Delay((1000 / FPS) - fps.getTicks());
    }
  }

  return CleanUp();
}
