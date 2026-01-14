#include <iostream>

#include "SDLIncident.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDLSprite.h"

using namespace std;

SDLIncident::SDLIncident()
{

}

SDLIncident::SDLIncident(SDL_Renderer * renderer,TTF_Font *f, unsigned int tS, unsigned int l, unsigned int h)
{   
    //INITIALISATION DES TAILLES
    tailleSprite = tS;
    longeur = l;
    hauteur = h;

    // INREGISTRER LES IMAGES POUR LE MENU
    im_vague.loadFromFile("data/images/vague.png", renderer);
    im_vague1.loadFromFile("data/images/vague_1.png", renderer);
    im_vague2.loadFromFile("data/images/vague_2.png", renderer);

    font = f;

    //INITIALISATION COULEUR DU TEXT
    font_color.r = 228;
    font_color.g = 23;
    font_color.b = 23;
    
    //FAIR LE SURFACE D`UN TEXT
    font_text_incident.setSurface(TTF_RenderText_Solid(font, "TSUNAMI", font_color));

    //AJOUTER DU TEXT
    font_text_incident.loadFromCurrentSurface(renderer);

    //AJOUTER DES COORDONNAIS D`AFFICAGE
    positionTitre.x = longeur * 2 / 5 * tailleSprite;
    positionTitre.y = tailleSprite + 20;
    positionTitre.w = 250;
    positionTitre.h = 50;

}
SDLIncident::~SDLIncident()
{
    im_vague.free();
    im_vague1.free();
    im_vague2.free();
    font_text_incident.free();
}

void SDLIncident::sdlAffTsunami(SDL_Renderer * renderer, int pointAffichageX)
{
    //AFFICHAGE DE TSUNAMI DANS LE FENETRE
    if(pointAffichageX >=-1)
    {
        im_vague.draw(renderer,  pointAffichageX * tailleSprite ,  0 , tailleSprite*2, hauteur*tailleSprite);  
    }
    if(pointAffichageX >=-2)
    {
        im_vague1.draw(renderer,  pointAffichageX * tailleSprite + 2*tailleSprite, tailleSprite*2 , tailleSprite*2, hauteur*tailleSprite - tailleSprite*4);  
    }
    im_vague2.draw(renderer,  pointAffichageX * tailleSprite + 4*tailleSprite ,  4*tailleSprite , tailleSprite*2, hauteur*tailleSprite - 8*tailleSprite);  

    //AFFICER DU TEXT DE MENU DANS LA FENETRE
    SDL_RenderCopy(renderer, font_text_incident.getTexture(), nullptr, &positionTitre);
    SDL_RenderPresent(renderer);
}