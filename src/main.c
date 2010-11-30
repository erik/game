#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "config.h"

int main(int argc, char** argv)
{
     bool keys[256];
     /* not sure why this is needed :/ */
     keys[SDLK_UP] = false;
     keys[SDLK_RIGHT] = false;
     keys[SDLK_LEFT] = false;

     SDL_Surface *screen = NULL;
     SDL_Surface *background = NULL;
     bool quit = false;
     SDL_Event event;
     Timer *fps = Timer_new();

     int i;
     for(i = 0; i < 256; i++) {
          keys[i] = false;
     }

     screen = init_sdl();

     Character* xeon = Character_load("xeon");
     xeon->x = 0 + CHARACTER_WIDTH;
     xeon->y = HEIGHT - CHARACTER_HEIGHT;

     background = load_image("data/back.bmp");
     apply_surface(0, 0, background, screen, NULL);
     Character_draw(xeon, screen);

     if(SDL_Flip(screen) == -1) {
          return 1;
     }

     while(quit == false) {
          Timer_start(fps);

          handle_keys(keys, xeon);
          Character_next_frame(xeon);

          if(xeon-> x < 0) {
               xeon->x = 0;
          }
          if(xeon->x > WIDTH - CHARACTER_WIDTH) {
               xeon->x = WIDTH - CHARACTER_WIDTH;
          }

          apply_surface(0, 0, background, screen, NULL);
          Character_draw(xeon, screen);
          SDL_Flip(screen);

          if(Timer_get_ticks(fps) < 1000 / FPS) {
               SDL_Delay((1000 / FPS) - Timer_get_ticks(fps));
          }

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
     }

     SDL_FreeSurface(background);
     SDL_FreeSurface(xeon->image);
     SDL_Quit();

     return 0;
}

