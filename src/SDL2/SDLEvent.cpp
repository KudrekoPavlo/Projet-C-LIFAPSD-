#include <iostream>
#include <assert.h>
#include <SDL2/SDL.h>
#include "SDLEvent.h"

using namespace std;



void SDLEvent::update() 
{
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
            case SDL_QUIT:
                fermer = true;
                break;
            
            case SDL_KEYDOWN:
                derniereTouche = static_cast<char>(event.key.keysym.sym);
                break;

            case SDL_MOUSEBUTTONDOWN:
                sourisClique = true;
                sourisX = event.button.x;
                sourisY = event.button.y;
                break;

            default:
                break;
        }
    }
}

bool SDLEvent::fermeture()
{
    update();
    return fermer;
}

bool SDLEvent::touchClavier() 
{
    update();
    return derniereTouche != 0;
}

char SDLEvent::touchBottom() 
{
    update();
    return derniereTouche;
}

bool SDLEvent::touchSuri() 
{
    update();
    return sourisClique;
}

void SDLEvent::touchSuri(int &x, int &y) 
{
    update();
    x = sourisX;
    y = sourisY;
}
