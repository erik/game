#include "game.h"
#include "config.h"
#include <assert.h>

SDL_Surface *init_sdl(void)
{
     SDL_Surface* screen = NULL;

     if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
          fprintf(stderr, "SDL_Init failed! Exiting.\n");
          exit(EXIT_FAILURE);
     }

     screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE);

     if(screen == NULL) {
          fprintf(stderr, "Couldn't initialize screen! Exiting\n");
          exit(EXIT_FAILURE);
     }

     SDL_WM_SetCaption(WINDOW_TITLE, NULL);

     return screen;

}

SDL_Surface *load_image(char *filename)
{
     SDL_Surface* image = NULL;
     SDL_Surface* optimized = NULL;

     image = IMG_Load(filename);

     //TODO: handle this
     assert(image && "Failed to load image");
     optimized = SDL_DisplayFormat(image);
     SDL_FreeSurface(image);

     return optimized;
}

void apply_surface(int x, int y, SDL_Surface* src, SDL_Surface* dst, SDL_Rect* clip)
{
     SDL_Rect offset;
     offset.x = x;
     offset.y = y;

     SDL_BlitSurface(src, clip, dst, &offset);
}

void handle_keys(bool keys[], Character *c)
{
     bool moved = false;

     if(keys[SDLK_UP] && !c->jump) {
          c->state = jump;
          c->frame = 0;
          c->jump = true;
          c->y_velocity = Y_VELOCITY_STEP;
          c->y += Y_VELOCITY_STEP;
          moved = true;
     }
     if(c->jump) {
          moved = true;
          if(c->y + c->y_velocity < HEIGHT - CHARACTER_HEIGHT) {
               c->y = c->y + c->y_velocity;
               c->y_velocity = c->y_velocity + GRAVITY;
          } else {
               c->jump = false;
               moved = false;
               c->y_velocity = 0;
               c->y = HEIGHT - CHARACTER_HEIGHT;
          }
     }
     if(keys[SDLK_RIGHT]) {
          c->x += CHARACTER_STEP;
          moved = true;
     }
     if(keys[SDLK_LEFT]) {
          c->x -= CHARACTER_STEP;
          moved = true;
     }

     if(moved && !c->jump) {
          c->state = walk;
     }

     if(keys[SDLK_UP]) {
          c->state = jump;
          c->frame = 0;
          moved = true;
     }

     if(!moved) {
          c->state = rest;
     }

}
