#ifndef _SDL_EVENT_H
#define _SDL_EVENT_H

#include <SDL2/SDL.h>
#include <iostream>

class SDLEvent
{
private:

    SDL_Event event;

    bool fermer = false;
    bool sourisClique = false;

    char derniereTouche = 0;
    int sourisX = 0, sourisY = 0;


public:

    void update(); 
    
    bool fermeture();

    bool touchClavier();

    char touchBottom();

    bool touchSuri();

    void touchSuri(int &x, int &y);


};


#endif