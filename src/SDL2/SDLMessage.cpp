#include <iostream>
#include <unistd.h> 
#include <fcntl.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#include "SDLSprite.h"
#include "SDLMessage.h"

using namespace std;


SDLMessage::SDLMessage(SDL_Renderer *renderer, TTF_Font *f, unsigned int x , unsigned int y, unsigned int ts)
{
    //AJOUTER DE LA STYLE DE TEXTE 
    font = f;
    //AJOUTER DE TAILLES DE TERRAIIN
    tailleSprite = ts;
    longeur = x;
    hauteur = y;  

    //AJOUTER DE TEXT D`AFFICHAGE
    case_non_valid = "ce n`est pas la bon place";
    err_no_wood = "il faut 30 bois pour construr la maison";
    err_no_food = "il faut 30 nuri pour cree personage";

    //AJOUTER COULEUR DE TEXTE
    text_color = {240,17,17};

    //CREE LES SURPHASES ET LES TEXTURES DE TEXTE
    font_err_no_food.setSurface(TTF_RenderText_Solid(font, err_no_food.c_str(), text_color));
    font_err_no_food.loadFromCurrentSurface(renderer);

    font_case_non_valid.setSurface(TTF_RenderText_Solid(font, case_non_valid.c_str(), text_color));
    font_case_non_valid.loadFromCurrentSurface(renderer);

    font_err_no_wood.setSurface(TTF_RenderText_Solid(font, err_no_wood.c_str(), text_color));
    font_err_no_wood.loadFromCurrentSurface(renderer);

    //AJOUTER LA POSITION DE TEXTE
    positionTitre = {longeur*tailleSprite/2 - 3* tailleSprite, 0 , 5*tailleSprite, 40};

}

SDLMessage::~SDLMessage()
{
    //LIBERATION DE TEXTE
    font_case_non_valid.free();  
    font_err_no_wood.free();  
    font_err_no_food.free();  
}

void SDLMessage::affMessages(SDL_Renderer *renderer, Event &e)
{
    if(e.caseMaisonNonValid || e.errBois || e.errMais)
    {
        //AJOUTER TIMER
        if(timer == NULL)
        {
            timer = clock();
        }

        //AFFICHER MESSAGE DANS LA FENETRE
        if(e.caseMaisonNonValid)
        {
            e.errMais = false;      
            e.errBois = false;
            SDL_RenderCopy(renderer, font_case_non_valid.getTexture(), nullptr, &positionTitre);
        }
        if(e.errBois)
        {
            e.errMais = false; 
            e.caseMaisonNonValid = false;     
            SDL_RenderCopy(renderer, font_err_no_wood.getTexture(), nullptr, &positionTitre);
        }
        if(e.errMais)
        {
            e.caseMaisonNonValid = false;     
            e.errBois = false;
            SDL_RenderCopy(renderer, font_err_no_food.getTexture(), nullptr, &positionTitre);
        }

        //REPRESENTER LES MESSAGES DANS ECRAN
        SDL_RenderPresent(renderer);

        //ANNOULER TIMER ET LES BOOLLENES DE MESSAGES 
        if((int)(clock() - timer)/1000 == 2)
        {
            timer = NULL;
     
            e.caseMaisonNonValid = false;
            e.errMais = false;      
            e.errBois = false;
        }
    }else
    {
        timer = NULL;
    }
}