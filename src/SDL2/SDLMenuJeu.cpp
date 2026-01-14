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
#include "SDLMenuJeu.h"

using namespace std;

SDLMenuJeu::SDLMenuJeu(SDL_Renderer *renderer, unsigned int x , unsigned int y ,unsigned int ts)
{
    //INITIALISATION DES TAILLES
    tailleSprite = ts;
    longeur = x;
    hauteur = y;

    //INITIALISATION L`IMAGE DE FOND
    im_background.loadFromFile("data/images/menu_background.png",renderer);
    im_background2.loadFromFile("data/images/menu_background2.png", renderer);
    //INITIALISATION DES STYLE DE TEXT
    font_name = TTF_OpenFont("data/text_styles/Menu_font1.ttf", 50);
    font_basique = TTF_OpenFont("data/text_styles/Menu_font2.ttf", 50);
    
    //AJOUTER LE LISTE DES REGLES DANS STRING D'UN FICHIER
    int t = open("data/text/regle.txt",O_RDONLY,NULL);
    if(t == -1)
    {
        cerr<<"ERROR : "<<strerror(errno)<<endl;
    }
    else
    {
        char buf[42];
        int nb_rd = 0;
        do
        {
            
            nb_rd = read(t,buf,42);
            if(nb_rd == -1)
            {
                cerr<<"ERROR : "<<strerror(errno)<<endl;
                break;
                

            }else
            {
                regle_de_jeu.append(buf, nb_rd);
            }
            
        }while(nb_rd>0);
        
    }
    close(t);
    //INITIALISATION DE TEXTE DE MENU
    name_jeu = "CIVILISATION";
    touche_play = "Jouer";
    touche_regles = "Regles";
    touche_sortir = "Sortir";
    touche_retour = "Retour";
    creators = "Created by : UA Tech Creations";

    //INITIALISATION DE POSITIONS DES TOUCHES
    positionTitre_name_jeu = {tailleSprite*longeur/2 -4*tailleSprite,10,tailleSprite*8,tailleSprite*3};
    positionTitre_regle_de_jeu = {tailleSprite*4, tailleSprite, longeur*tailleSprite-9*tailleSprite, hauteur*tailleSprite - tailleSprite};
    positionTitre_touche_play = {tailleSprite, tailleSprite*hauteur-8*tailleSprite, tailleSprite*4, tailleSprite*2};
    positionTitre_touche_regles = {tailleSprite, tailleSprite*hauteur-6*tailleSprite, tailleSprite*4, tailleSprite*2};
    positionTitre_touche_sortir = {tailleSprite, tailleSprite*hauteur - 2*tailleSprite, tailleSprite*4, tailleSprite*2};
    positionTitre_touche_retour = {5,0,tailleSprite*2,tailleSprite};
    positionTitre_creators = {longeur*tailleSprite - 4*tailleSprite, 0, tailleSprite*3, 20};
    
    //INITIALISATION DE LA COULEUR DE LA TEXTE
    text_color = {0,0,0};
    text_color_regles={255,255,255};
    //INITIALISATION DE BOOLEEN QUI INDIQUE LE SORTIE DE BOUCLE
    finDeMenu = false;
    menuRegles = false;
    //AJOUTER LA MUSIQUE
    sound = Mix_LoadWAV("data/songs/menu_main_song.wav");
    if (sound == nullptr)
    {
        cout << "Failed to load son.mp3! SDL_mixer Error: " << Mix_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    Mix_VolumeChunk(sound, 10);
    Mix_PlayChannel(-1, sound, 0);

    //TRANSFORMATION DE TEXT DANS SURFACE
    font_name_jeu.setSurface(TTF_RenderText_Solid(font_name, name_jeu.c_str(), text_color));
    //POUR LES TOUCHES
    font_touche_play.setSurface(TTF_RenderText_Solid(font_basique, touche_play.c_str(), text_color));
    font_touche_regles.setSurface(TTF_RenderText_Solid(font_basique, touche_regles.c_str(), text_color));
    font_touche_sortir.setSurface(TTF_RenderText_Solid(font_basique, touche_sortir.c_str(), text_color));
    font_creators.setSurface(TTF_RenderText_Solid(font_basique,creators.c_str(),text_color));
    //POUR LE MENU DES REGLES
    font_regle_de_jeu.setSurface(TTF_RenderText_Blended_Wrapped(font_basique, regle_de_jeu.c_str(), text_color_regles, positionTitre_regle_de_jeu.w));
    font_touche_retour.setSurface(TTF_RenderText_Solid(font_basique, touche_retour.c_str(), text_color_regles));
    font_creators.setSurface(TTF_RenderText_Solid(font_basique,creators.c_str(),text_color_regles));
    //TRANSFORMATION DES SURFACES DANS TEXTURES
    font_name_jeu.loadFromCurrentSurface(renderer);
    font_touche_play.loadFromCurrentSurface(renderer);
    font_touche_regles.loadFromCurrentSurface(renderer);
    font_touche_sortir.loadFromCurrentSurface(renderer);
    font_creators.loadFromCurrentSurface(renderer);
    //TRANSFORMATION DES SURFACES DANS TEXTURES POUR LE MENU DES REGLES
    font_regle_de_jeu.loadFromCurrentSurface(renderer);
    font_touche_retour.loadFromCurrentSurface(renderer);
    font_creators.loadFromCurrentSurface(renderer);

}

SDLMenuJeu::~SDLMenuJeu()
{
    Mix_FreeChunk(sound);
}

void SDLMenuJeu::affMenuPrencipal(SDL_Renderer *renderer)
{
    //EFACER LA CONTENU DE FENETRE
    SDL_SetRenderDrawColor(renderer, 15, 170, 255, 255);
    SDL_RenderClear(renderer);

    //AJOUT DE BACKGROUND SUR LA FENETRE
    im_background.draw(renderer, 0, 0, tailleSprite*longeur, tailleSprite*hauteur);

    //AJOUTER LES TEXTURES DANS RENDERER
    SDL_RenderCopy(renderer, font_name_jeu.getTexture(), nullptr , &positionTitre_name_jeu );
    SDL_RenderCopy(renderer, font_touche_play.getTexture(), nullptr , &positionTitre_touche_play );
    SDL_RenderCopy(renderer, font_touche_regles.getTexture(), nullptr , &positionTitre_touche_regles);
    SDL_RenderCopy(renderer, font_touche_sortir.getTexture(), nullptr , &positionTitre_touche_sortir);
    SDL_RenderCopy(renderer, font_creators.getTexture(), nullptr , &positionTitre_creators);

}

void SDLMenuJeu::affMenuRegles(SDL_Renderer *renderer)
{
    //EFACER LA CONTENU DE FENETRE
    SDL_SetRenderDrawColor(renderer, 15, 170, 255, 255);
    SDL_RenderClear(renderer);

    //AJOUT DE BACKGROUND SUR LA FENETRE
    im_background2.draw(renderer, 0, 0, tailleSprite*longeur, tailleSprite*hauteur);

    //AJOUTER LES TEXTURES DANS RENDERER
    SDL_RenderCopy(renderer, font_regle_de_jeu.getTexture(), nullptr, &positionTitre_regle_de_jeu);
    SDL_RenderCopy(renderer, font_touche_retour.getTexture(), nullptr, &positionTitre_touche_retour);
    SDL_RenderCopy(renderer, font_creators.getTexture(), nullptr , &positionTitre_creators);

}

void SDLMenuJeu::boucleMenuPrencipal(SDL_Renderer *renderer, bool &exit)
{
    //INSCTIPTION DES EVENT
    unsigned int x,y; 
    while(!finDeMenu)
    {
        
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                x = event.button.x;
                y = event.button.y;
            } 
            if(event.type == SDL_QUIT)
            {
                finDeMenu = true;
                exit = true;
            }
        }

        if(menuRegles)
        {
            //SI LE MENU DES REGLES EST OUVERT
            //AFICHER LE MENU DE REGLES
            affMenuRegles(renderer);

            //ACTION QUI DEPEND DES EVENTS 
            if((x >= 0 &&  x <= (tailleSprite*2)) && ( y >= 0 && y <= (tailleSprite)))
            {
                menuRegles = false;
            }
        }else
        {
            //SI LE MENU DES REGLES EST FERMEE
            affMenuPrencipal(renderer);
            //ACTION QUI DEPEND DES EVENTS
            if((x >= tailleSprite &&  x <= (tailleSprite*4 + tailleSprite)) && ( y >= tailleSprite*hauteur-8*tailleSprite && y <= (tailleSprite*2 + tailleSprite*hauteur-8*tailleSprite)))
            {
                finDeMenu = true;
            }

            if((x >= tailleSprite &&  x <= (tailleSprite*4 + tailleSprite)) && ( y >= tailleSprite*hauteur-6*tailleSprite && y <= (tailleSprite*2 + tailleSprite*hauteur-6*tailleSprite)))
            {
                menuRegles = true;
            }

            if((x >= tailleSprite &&  x <= (tailleSprite*4 + tailleSprite)) && ( y >= tailleSprite*hauteur-2*tailleSprite && y <= (tailleSprite*2 + tailleSprite*hauteur-2*tailleSprite)))
            {
                finDeMenu = true;
                exit = true;
                break;
            }
        }  
        //DESTRUCTIO DES ACTION
        x = 9999;
        y = 9999;

        //AFFICHAGE DE MENU DANS LA FENETRE
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }
}
