#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDLSprite.h"
#include "SDLAnimation.h"
#include "time.h"


using namespace std;


SDLAnimation::SDLAnimation(SDL_Renderer *renderer, unsigned int ts)
{
    tailleSprite = ts;
    //INITIALISATION DES IMAGES D`ANIMATION
    im_animcouper1.loadFromFile("data/animation/arbre_anim1.png",renderer);
    im_animcouper2.loadFromFile("data/animation/arbre_anim2.png",renderer);
    im_animcouper3.loadFromFile("data/animation/arbre_anim3.png",renderer);

    im_animble1.loadFromFile("data/animation/Ble_anim1.png",renderer);
    im_animble2.loadFromFile("data/animation/Ble_anim2.png",renderer);
    im_animble3.loadFromFile("data/animation/Ble_anim3.png",renderer);
    im_animble4.loadFromFile("data/animation/Ble_anim4.png",renderer);
}

void SDLAnimation::affAnimationCouper(SDL_Renderer *renderer, unsigned int x, unsigned int y)
{
    if(t == NULL)
    {
        t = clock();
    }
    if((int)((clock()-t)/100) <= 2)
    {
        im_animcouper1.draw(renderer,x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite); 
    }

    if((int)((clock()-t)/100) <= 4 && (int)((clock()-t)/100) > 2)
    {
        im_animcouper2.draw(renderer, x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite); 
    }

    if((int)((clock()-t)/100) <= 6 && (int)((clock()-t)/100) > 4)
    {
        im_animcouper3.draw(renderer, x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite);  
    }

    if((int)((clock()-t)/100) <= 8 && (int)((clock()-t)/100) > 6)
    {
        im_animcouper2.draw(renderer, x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite); 
    }

    if((int)((clock()-t)/100) > 8)
    {
        im_animcouper1.draw(renderer, x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite); 
        t = clock();
    }
    
}

void SDLAnimation::affAnimationBle(SDL_Renderer *renderer, unsigned int x, unsigned int y)
{
    if(t == NULL)
    {
        t = clock();
    }

    if((int)((clock()-t)/100) <= 2)
    {
        im_animble1.draw(renderer,x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite); 
    }

    if((int)((clock()-t)/100) <= 4 && (int)((clock()-t)/100) > 2)
    {
        im_animble2.draw(renderer, x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite); 
    }

    if((int)((clock()-t)/100) <= 6 && (int)((clock()-t)/100) > 4)
    {
        im_animble3.draw(renderer, x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite);  
    }

    if((int)((clock()-t)/100) <= 8 && (int)((clock()-t)/100) > 6)
    {
        im_animble4.draw(renderer, x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite); 
    }

    if( (int)((clock()-t)/100) > 8)
    {
       im_animble1.draw(renderer, x*tailleSprite,y*tailleSprite,tailleSprite,tailleSprite); 
        t = clock();
    } 
}
