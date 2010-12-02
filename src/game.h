#ifndef _GAME_H_
#define _GAME_H_
#include <string>
#include <iostream>

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "config.h"
#include "timer.h"

using std::string;
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

// to save some precious keystrokes
#define IFNULL(x) if(x == NULL)
#define FATAL(msg) std::cerr << "FATAL: " << msg << std::endl; exit(EXIT_FAILURE)
//

typedef enum {
     rest,
     walk,
     jump
} MoveState;

/* util functions */
SDL_Surface *InitSDL(void);
SDL_Surface *LoadImage(std::string, bool transparent = false);
int CleanUp();
void ApplySurface(int, int, SDL_Surface*, SDL_Surface*, SDL_Rect* clip=NULL); 
#endif /* _GAME_H_ */
