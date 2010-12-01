#include "game.h"
#include "character.h"

int main(int argc, char** argv) {
  SDL_Surface *screen = InitSDL();
  SDL_Surface *background = LoadImage("data/back.bmp");
  SDL_Event event;
  bool quit = false;
  Character player("xeon", 0, HEIGHT - CHARACTER_HEIGHT);
  Timer fps;
  bool keys[256];
  for(int i = 0; i < 256; ++i) {
    keys[i] = false;
  }

  ApplySurface(0, 0, background, screen);
  player.draw(screen);

  SDL_Flip(screen);

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
    
    player.nextFrame();
    
    ApplySurface(0, 0, background, screen);
    player.draw(screen);

    SDL_Flip(screen);
    
    if(fps.getTicks() < 1000 / FPS) {
      SDL_Delay((1000 / FPS) - fps.getTicks());
    }
  }

  return CleanUp();
}
