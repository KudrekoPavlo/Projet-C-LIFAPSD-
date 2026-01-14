#ifndef _SDL_ANIMATION_H
#define _SDL_ANIMATION_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDLSprite.h"
#include "time.h"

class SDLAnimation
{
private:
    unsigned int tailleSprite; 
    SDLSprite im_animcouper1;
    SDLSprite im_animcouper2;
    SDLSprite im_animcouper3;


    SDLSprite im_animble1;
    SDLSprite im_animble2;
    SDLSprite im_animble3;
    SDLSprite im_animble4;

    
    clock_t t;

public:
    SDLAnimation(SDL_Renderer * renderer, unsigned int ts);
    void affAnimationCouper(SDL_Renderer *renderer, unsigned int x, unsigned int y);
    void affAnimationBle(SDL_Renderer *renderer, unsigned int x, unsigned int y);

};


#endif