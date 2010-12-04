#include "game.h"
#include "config.h"

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_mixer.h"

#include <string>
#include <iostream>

SDL_Surface *LoadImage(std::string filename, bool transparent) {
  SDL_Surface *image = NULL;
  SDL_Surface *optimized;
  
  image = IMG_Load(filename.c_str());

  IFNULL(image) {
    std::cerr << "Failed to load image: " << filename << std::endl;
    return NULL;
  }

  if(transparent) {
    optimized = SDL_DisplayFormatAlpha(image);
    SDL_SetColorKey(optimized, SDL_SRCCOLORKEY | SDL_RLEACCEL, 
		    SDL_MapRGB(optimized->format, 0, 0, 0));
  } else {
    optimized = SDL_DisplayFormat(image);
  }
  SDL_FreeSurface(image);  
  return optimized;
}

SDL_Surface *RemoveBackground(SDL_Surface *im) {
  Uint32 colorkey = SDL_MapRGB(im->format, CHARACTER_BACK);
  SDL_SetColorKey(im, SDL_SRCCOLORKEY, colorkey);
  return im;
}

SDL_Surface *InitSDL() {
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
    FATAL("SDL init failed");
  }
  SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE);

  IFNULL(screen) {
    FATAL("Couldn't setup SDL screen");
  }

  SDL_WM_SetCaption(WINDOW_TITLE, NULL);

  return screen;
  
}

int CleanUp() {
  SDL_Quit();
  return 0;
}

void ApplySurface(int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect* clip)
{
     SDL_Rect offset;
     offset.x = x;
     offset.y = y;

     SDL_BlitSurface(src, clip, dst, &offset);
}
