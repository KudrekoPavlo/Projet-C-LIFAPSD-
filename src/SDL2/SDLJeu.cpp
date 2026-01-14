#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>

#include "SDLJeu.h"
#include "../Terrain.h"
#include "../Personage.h"
#include "../Case.h"
#include "../Events.h"
#include "../Game.h"
#include "SDLMenu.h"
#include "SDLAnimation.h"
#include "SDLMessage.h"

using namespace std;

float temps()
{
    return float(SDL_GetTicks()) / CLOCKS_PER_SEC; // conversion des ms en secondes en divisant par 1000
}
// ============= CLASS SDLJEU =============== //

SDL_Renderer *SDLJeu::getRenderer() const
{
    return renderer;
}

SDLJeu::SDLJeu(unsigned int x, unsigned int y, unsigned int tS = 50)
{
    tailleSprite = tS;
    longeur = x;
    hauteur = y;

    // INITIALISATION DE LA SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // INITIALISATION SDL AUDIO
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        cout << "SDL_mixer could not initialize! Error: " << Mix_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }
    else
    {
        withSound = true;
    }
    // INITIALISATION DE TAILLE DE LA FENETRE
    withSound = true;
    int dimx, dimy;
    dimx = longeur * tailleSprite;
    dimy = hauteur * tailleSprite;

    // CREATION DE LA FENETRE
    window = SDL_CreateWindow("Terra", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, dimx, dimy, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // CREATION DE LA RENDERER
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        cout << "Erreur lors de la creation de la renderer : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // INITIALISATION DES IMAGES POUR LE TERRAIN
    im_personage.loadFromFile("data/images/Personage.png", renderer);
    im_ocean.loadFromFile("data/images/ocean.png", renderer);
    im_forret.loadFromFile("data/images/arbre.png", renderer);
    im_grass.loadFromFile("data/images/grass.png", renderer);
    im_maison.loadFromFile("data/images/maison.png", renderer);
    im_ble.loadFromFile("data/images/Ble.png", renderer);
    im_personage_caher.loadFromFile("data/images/Personage_proteger.png", renderer);
    im_enemie.loadFromFile("data/images/enemi.png", renderer);
    im_maison_distructed.loadFromFile("data/images/maison_detruit.png",renderer);
    im_personage_in_distructed_maison.loadFromFile("data/images/Personnage_in_det_maison.png",renderer);
    im_victior.loadFromFile("data/images/victoir.png",renderer);
    im_perdre.loadFromFile("data/images/perdre.png",renderer);
    // INITIALISATION DES FONTS
    font = TTF_OpenFont("data/text_styles/Text_font.ttf", 50);
    if (font == nullptr)
        font = TTF_OpenFont("../data/Text_font.ttf", 50);
    if (font == nullptr)
    {
        cout << "Failed to load Text_font.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    // INITIALISATION MENU
    menu = new SDLMenu(renderer, font, tailleSprite, longeur, hauteur);

    // INITIALISATION ANIMATION
    anim = new SDLAnimation(renderer, tailleSprite);

    // INITIALISATION DES INCIDENTES
    incidant = new SDLIncident(renderer, font, tailleSprite, longeur, hauteur);

    message = new SDLMessage(renderer,font, longeur, hauteur, tailleSprite);

    // INITIALISATION DE MENU PRENCIPAL
    menu_prencipal = new SDLMenuJeu(renderer, longeur, hauteur, tailleSprite);
    affMenuPrencipal();
    // INITIALISATION DES SONS
    if (withSound)
    {
        sound = Mix_LoadWAV("data/songs/game_main_song.wav");
        if (sound == nullptr)
            sound = Mix_LoadWAV("../data/songs/game_main_song.wav");
        if (sound == nullptr)
        {
            cout << "Failed to load son.mp3! SDL_mixer Error: " << Mix_GetError() << endl;
            SDL_Quit();
            exit(1);
        }
        
        Mix_VolumeChunk(sound, 5);
        Mix_PlayChannel(-1, sound, 0);
    }
}

SDLJeu::~SDLJeu()
{
    // DESTRUCTION DES IMAGES
    im_grass.free();
    im_ocean.free();
    im_forret.free();
    im_personage.free();
    im_personage_caher.free();
    im_maison.free();
    im_ble.free();
    im_enemie.free();
    im_maison_distructed.free();
    im_personage_in_distructed_maison.free();
    im_victior.free();
    im_perdre.free();

    font_im.free();
    font_im_menu1.free();
    font_im_menu2.free();

    // VIDE DE LA MEMOIRE
    delete menu;
    menu = nullptr;
    delete anim;
    anim = nullptr;
    delete incidant;
    incidant = nullptr;
    delete message;
    message = nullptr;
    // FERMETURE SDL
    if (withSound)
    {
        Mix_FreeChunk(sound);
        Mix_FreeChunk(sound_perdu);
        Mix_FreeChunk(sound_gagne);
        Mix_CloseAudio();
        Mix_Quit();
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLJeu::sdlAff(Terrain *ter, Game game)
{
    // METR ECTAN EN BLANC
    SDL_SetRenderDrawColor(renderer, 15, 170, 255, 255);
    SDL_RenderClear(renderer);
    unsigned int x, y;

    // Afficher les sprites des murs et des pastilles
    for (x = 0; x < longeur; ++x)
    {
        for (y = 0; y < hauteur; ++y)
        {
            // definer - copy  de case de terrain sur les coordonnais x y
            Case definer = ter->getCase_FromTerrain(x, y);

            // ajouter les texturess sur renderer
            switch (definer.getType())
            {
            // case s'il y a grasse
            case Case::Terre:
                switch (definer.getOccupationType())
                {
                // si terrain n'est pas occuper
                case Case::Aucun:
                    im_grass.draw(renderer, x * tailleSprite, y * tailleSprite, tailleSprite, tailleSprite);
                    break;
                // si terrain est occuper par une maison
                case Case::Maison:
                    if(game.getMaisonDistructed(x,y))
                    {
                        im_maison_distructed.draw(renderer, x * tailleSprite, y * tailleSprite, tailleSprite, tailleSprite);
                    }else
                    {
                        im_maison.draw(renderer, x * tailleSprite, y * tailleSprite, tailleSprite, tailleSprite);
                    }
                    break;
                    // si terrain est occuper par un personnage
                }
                break;

            // case s'il y a forret
            case Case::Foret:
                im_forret.draw(renderer, x * tailleSprite, y * tailleSprite, tailleSprite, tailleSprite);
                break;
            // case s'il y a Ocean
            case Case::Ocean:
                im_ocean.draw(renderer, x * tailleSprite, y * tailleSprite, tailleSprite, tailleSprite);
                break;
            // case s'il y a Ble
            case Case::Mais:
                im_ble.draw(renderer, x * tailleSprite, y * tailleSprite, tailleSprite, tailleSprite);
                break;
            // case de cas extrait
            default:
                std::cerr << "Case inconue : " << definer.getType() << std::endl;
                break;
            }
        }
    }
    // AFFICHAGE PERSONAGE
    for (unsigned int i = 0; i < game.quantitePersonages(); i++)
    {
        Personage *p = game.getPersonage(i);
        Case definer2 = ter->getCase_FromTerrain(p->getX(), p->getY());
        // cout << "sdasdasdasd" <<p->getX()<<endl<< p->getX()<<endl;
        //S`IL COUP LE BOIS
        if (p->getBusyCutingTree())
        {
            anim->affAnimationCouper(renderer, p->getX(), p->getY());
        }
        else
        {
            //S`IL COUP LE MAIS
            if (p->getBusyCutingMais())
            {
                anim->affAnimationBle(renderer, p->getX(), p->getY());
            }
            else
            {
                if (definer2.getType() == Case::Terre && definer2.getOccupationType() == Case::Maison)
                {
                    if(game.getMaisonDistructed(p->getX(),p->getY()))
                    {
                        //S`IL DANS MAISON DETRUIT
                        im_personage_in_distructed_maison.draw(renderer, p->getX() * tailleSprite, p->getY() * tailleSprite, tailleSprite, tailleSprite);
                    }else
                    {
                        //S`IL DANS LA MAISON
                        im_personage_caher.draw(renderer, p->getX() * tailleSprite, p->getY() * tailleSprite, tailleSprite, tailleSprite);
                    }
                }
                else
                {
                    //S`IL SUR LE TERRE
                    im_personage.draw(renderer, p->getX() * tailleSprite, p->getY() * tailleSprite, tailleSprite, tailleSprite);
                }
            }
        }
        p = nullptr;
    }

    // AFFICHAGE DES ENEMIES
    for (unsigned int i = 0; i < game.quantiteEnemis(); i++)
    {
        Personage *p1 = game.getEnemies(i);
        Case definer2 = ter->getCase_FromTerrain(p1->getX(), p1->getY());
        im_enemie.draw(renderer, p1->getX() * tailleSprite, p1->getY() * tailleSprite, tailleSprite, tailleSprite);
        p1 = nullptr;
    }

    // AFFICHER LE SCORE
    menu->sdlAffScore(renderer, ter->getWood(), ter->getMais(), game.getTime());

    // MENU AFFICHAGE
    if (ev.menuOpen)
    {
        menu->sdlAffMenu(renderer);
    }

    // MAISON MENU AFFICHAGE
    if (ev.homeMenuIsOpen)
    {
        menu->sdlAffMenuMaison(renderer);
    }

    // AFFICHAGE DE RENDERER DANS LA FENETRE
    SDL_RenderPresent(renderer);
}

void SDLJeu::Afftsunami(Terrain *ter, Game game)
{
    for (int x = longeur - 1; x >= 0; x--)
    {
        sdlAff(ter, game);
        incidant->sdlAffTsunami(renderer, x);
        SDL_Delay(100);
        ev.incident = false;
    }
}

void SDLJeu::affMenuPrencipal()
{
    menu_prencipal->boucleMenuPrencipal(renderer, ev.fermer);
    delete menu_prencipal;
    menu_prencipal = nullptr;
}

void SDLJeu::affGagnerPerdre()
{
    if(ev.victoir)
    {
        im_victior.draw(renderer, 0, 0, longeur*tailleSprite, hauteur*tailleSprite);  
        if(!fin)
        {
            sound_gagne = Mix_LoadWAV("data/songs/gagne.wav");
            Mix_VolumeChunk(sound, 0);
            Mix_VolumeChunk(sound_gagne, 15);
            Mix_PlayChannel(-1, sound_gagne, 0);
            fin = true;
        }
    }
    
    if(ev.perdre)
    {
        im_perdre.draw(renderer, 0, 0, longeur*tailleSprite, hauteur*tailleSprite);
        if(!fin)
        {
            sound_perdu = Mix_LoadWAV("data/songs/perdu.wav");
            Mix_VolumeChunk(sound, 0);
            Mix_VolumeChunk(sound_perdu, 15);
            Mix_PlayChannel(-1, sound_perdu, 0);
            fin = true;
        }
    }

    SDL_RenderPresent(renderer);
}

void SDLJeu::boucle(Game game)
{
    while (!ev.fermer)
    {
        // DECLARATUON DES EVENTS
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                ev.fermer = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    ev.renouveller();
                }
                else
                {
                    ev.sourisClique = false;
                    ev.clavierClique = true;
                    ev.derniereTouche = static_cast<char>(event.key.keysym.sym);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                ev.clavierClique = false;
                ev.sourisClique = true;
                ev.propreX = event.button.x;
                ev.propreY = event.button.y;
                ev.sourisX = ((int)ev.propreX + 1) / tailleSprite;
                ev.sourisY = ((int)ev.propreY + 1) / tailleSprite;
                break;
            default:
                break;
            }
        }

        if(!ev.victoir && !ev.perdre)
        {
            // UPDADE DE JEU
            game.update(ev);
            
            if (ev.incident == true)
            {
                Afftsunami(game.getTerrain(), game);
            }
            // AFFICAHGE DE JEU
            sdlAff(game.getTerrain(), game);

            //AFFICHER DES MESSAGES
            message->affMessages(renderer, ev);
        }else
        {
            affGagnerPerdre();
        }
        // DESTRUCTION CERTAIN EVENEMENTS
        ev.destructionEventPourBoucle();
        SDL_Delay(16);
    }
}