#include "game.h"
#include "config.h"

#include <stdio.h>
#include <assert.h>

Character *Character_load(char *name)
{
     Character *c = malloc(sizeof(Character));
     c->name = name;
     c->x = 0;
     c->y = 0;
     c->state = rest;
     c->frame = 0;
     c->jump = false;
     char *filename = malloc(strlen(name) + 20);
     sprintf(filename, "data/%s.png", name);
     SDL_Surface *image = load_image(filename);
     Uint32 colorkey = SDL_MapRGB(image->format, CHARACTER_BACK);
     SDL_SetColorKey(image, SDL_SRCCOLORKEY, colorkey);
     c->image = image;

     FILE* info = fopen(strcat(filename, ".info"), "r");
     free(filename);

     int rf;
     int wf;
     int jf;
     fscanf(info, "%d %d %d", &rf, &wf, &jf);
     free(info);

     c->restframes = rf;
     c->walkframes = wf;
     c->jumpframes = jf;

     SDL_Rect** clips = malloc(sizeof(SDL_Rect*) * 3);

     int i;
     SDL_Rect* tmpclip = NULL;

     tmpclip = malloc(sizeof(SDL_Rect) * rf);
     for(i = 0; i < rf; i++) {
          SDL_Rect tmp;
          tmp.x = i * CHARACTER_WIDTH;
          tmp.y = 0 * CHARACTER_HEIGHT;
          tmp.w = CHARACTER_WIDTH;
          tmp.h = CHARACTER_HEIGHT;
          tmpclip[i] = tmp;
     }
     clips[0] = tmpclip;

     tmpclip = malloc(sizeof(SDL_Rect) * wf);
     for(i = 0; i < wf; i++) {
          SDL_Rect tmp;
          tmp.x = i * CHARACTER_WIDTH;
          tmp.y = 1 * CHARACTER_HEIGHT;
          tmp.w = CHARACTER_WIDTH;
          tmp.h = CHARACTER_HEIGHT;
          tmpclip[i] = tmp;
     }
     clips[1] = tmpclip;

     tmpclip = malloc(sizeof(SDL_Rect) * jf);
     for(i = 0; i < jf; i++) {
          SDL_Rect tmp;
          tmp.x = i * CHARACTER_WIDTH;
          tmp.y = 2 * CHARACTER_HEIGHT;
          tmp.w = CHARACTER_WIDTH;
          tmp.h = CHARACTER_HEIGHT;
          tmpclip[i] = tmp;
     }
     clips[2] = tmpclip;

     c->clips = clips;
     return c;
}

void Character_draw(Character *c, SDL_Surface* screen)
{
     SDL_Rect clip;
     int frame = (int)c->frame;
     switch(c->state) {
     case rest:
          clip = c->clips[0][frame];
          break;
     case walk:
          clip = c->clips[1][frame];
          break;
     case jump:
          clip = c->clips[2][frame];
          break;
     }

     apply_surface(c->x, c->y, c->image, screen, &clip);
}

int Character_next_frame(Character *c)
{
     int numframes = -1;
     if(c->state == rest)
          numframes = c->restframes;
     else if(c->state == walk)
          numframes = c->walkframes;
     else if(c->state == jump)
          numframes = c->jumpframes;

     c->frame = c->frame + FRAME_STEP;
     if(c->frame >= numframes)
          c->frame = 0;
     return ((int)c->frame) % numframes;

}

