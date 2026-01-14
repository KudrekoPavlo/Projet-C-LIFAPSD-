#include<iostream>
#include <string>
#include <time.h>

#include "SDLMenu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDLSprite.h"

using namespace std;

SDLMenu::SDLMenu()
{
    //AJOUT LA COULEUR DE LA TEXT DANS LE MENU
    font_color = {0, 0, 0};

    //AJOUT LA COULEUR DE BOIS SCORE
    font_color_bois = {183, 126, 23};

    //AJOUT LA COULEUR DE BLE SCORE
    font_color_ble = {237, 191, 90};

    //AJOUT LA COULEUR DE TIMER
    font_color_remp_critique = {248, 11, 11};

    //INITIALISATION DE LA POSITION DE MENU 
    positionTitre_menu.x = longeur * 4 / 5 * tailleSprite + 2 * tailleSprite + 20;
    positionTitre_menu.y = 0;
    positionTitre_menu.w = 70;
    positionTitre_menu.h = 30;

    //INITIALISATION DE LA POSITION DE MENU MAISON
    positionTitre_menu_maison.x = longeur * 4 / 5 * tailleSprite + 2 * tailleSprite;
    positionTitre_menu_maison.y = 0;
    positionTitre_menu_maison.w = 110;
    positionTitre_menu_maison.h = 40;

    //INITIALISATION DE LA POSITION DES TOUCHES DANS LE MENU 
    positionTitre_touch.x = longeur * 4 / 5 * tailleSprite + tailleSprite;
    positionTitre_touch.y = tailleSprite + 20;
    positionTitre_touch.w = 120;
    positionTitre_touch.h = 30;

    //INITIALISATION DE LA POSITION DE LA SCORE DE BOIS
    positionTitre_bois.x = (longeur - 7) * tailleSprite;
    positionTitre_bois.y = 0;
    positionTitre_bois.w = 120;
    positionTitre_bois.h = 30;

    //INITIALISATION DE LA POSITION DE LA SCORE DE BLE
    positionTitre_ble.x = positionTitre_bois.x + positionTitre_bois.w + 25;
    positionTitre_ble.y = 0;
    positionTitre_ble.w = 120;
    positionTitre_ble.h = 30;

}

SDLMenu::SDLMenu(SDL_Renderer* renderer, TTF_Font *f, unsigned int tS, unsigned int l, unsigned int h)
{
    //INITIALISATION DES TAILLES
    tailleSprite = tS;
    longeur = l;
    hauteur = h;

    //AJOUT LA COULEUR DE LA TEXT DANS LE MENU
    font_color = {0, 0, 0};

    //AJOUT LA COULEUR DE BOIS SCORE
    font_color_bois = {183, 126, 23};

    //AJOUT LA COULEUR DE BLE SCORE
    font_color_ble = {237, 191, 90};

    //AJOUT LA COULEUR DE TIMER
    font_color_remp_critique = {248, 11, 11};
    
    //INITIALISATION DE LA POSITION DE MENU 
    positionTitre_menu.x = longeur * 4 / 5 * tailleSprite + 2 * tailleSprite + 20;
    positionTitre_menu.y = 0;
    positionTitre_menu.w = 70;
    positionTitre_menu.h = 30;

    //INITIALISATION DE LA POSITION DE MENU MAISON
    positionTitre_menu_maison.x = longeur * 4 / 5 * tailleSprite + 2 * tailleSprite;
    positionTitre_menu_maison.y = 0;
    positionTitre_menu_maison.w = 110;
    positionTitre_menu_maison.h = 40;

    //INITIALISATION DE LA POSITION DES TOUCHES DANS LE MENU 
    positionTitre_touch.x = longeur * 4 / 5 * tailleSprite + tailleSprite;
    positionTitre_touch.y = tailleSprite + 20;
    positionTitre_touch.w = 120;
    positionTitre_touch.h = 30;

    //INITIALISATION DE LA POSITION DE LA SCORE DE BOIS
    positionTitre_bois.x = (longeur - 7) * tailleSprite;
    positionTitre_bois.y = 0;
    positionTitre_bois.w = 120;
    positionTitre_bois.h = 20;

    //INITIALISATION DE LA POSITION DE LA SCORE DE BLE
    positionTitre_ble.x = positionTitre_bois.x + positionTitre_bois.w + 35;
    positionTitre_ble.y = 0;
    positionTitre_ble.w = 120;
    positionTitre_ble.h = 20;

    //INITIALISATION DE LA POSITION DE TAIMER
    positionTitre_temp.x = 0;
    positionTitre_temp.y =0;
    positionTitre_temp.w =300;
    positionTitre_temp.h = 20;

    /*//INITIALISATION DE LA POSITION DE TAIMER DES ATAQUES
    positionTitre_temp.x = positionTitre_temp.x + positionTitre_temp.w + 5;
    positionTitre_temp.y =0;
    positionTitre_temp.w =300;
    positionTitre_temp.h = 20;*/

    // INREGISTRER LES IMAGES POUR LE MENU
    im_menu.loadFromFile("data/images/menu.png", renderer);
    im_home_bottom.loadFromFile("data/images/home_touche.png", renderer);
    im_home_bottom1.loadFromFile("data/images/pers_touche.png",renderer);
    im_score_bois.loadFromFile("data/images/bois_score.png",renderer);
    im_score_ble.loadFromFile("data/images/nuri_score.png",renderer);

    //INITIALISATION DE LA STYLE DE TEXT 
    font = f;

    //AJOUTER DU TEXT
    font_im_menu2.setSurface(TTF_RenderText_Solid(font, "Cree personage", font_color));
    font_im_menu2.loadFromCurrentSurface(renderer);
    font_im_menu1.setSurface(TTF_RenderText_Solid(font, "Menu maison", font_color));
    font_im_menu1.loadFromCurrentSurface(renderer);
    font_im_menu3.setSurface(TTF_RenderText_Solid(font, "Menu", font_color));
    font_im_menu3.loadFromCurrentSurface(renderer);
    font_im_menu4.setSurface(TTF_RenderText_Solid(font, "Construir maison", font_color));
    font_im_menu4.loadFromCurrentSurface(renderer);
}

SDLMenu::~SDLMenu()
{
    //LEBERATION DE LA MEMOIR
    im_menu.free();
    im_home_bottom.free();
    im_home_bottom1.free();
    im_score_bois.free();
    im_score_ble.free();
    font_im_menu2.free();
    font_im_menu1.free();
    font_im_menu3.free();
    font_im_menu4.free();
}


void SDLMenu::sdlAffMenu(SDL_Renderer* renderer)
{
    //INITIALISATION DES IMAGES DE TOUCHES
    im_menu.draw(renderer, longeur * 4 / 5 * tailleSprite, 0, longeur / 5 * tailleSprite, hauteur * tailleSprite);
    im_home_bottom.draw(renderer, longeur * 4 / 5 * tailleSprite, tailleSprite, tailleSprite, tailleSprite);

    //AFFICER LES IMAGES DU MENU SUR LA FENETRE
    SDL_RenderCopy(renderer, font_im_menu3.getTexture(), nullptr, &positionTitre_menu);

    //AFFICER DU TEXT DE MENU DANS LA FENETRE
    SDL_RenderCopy(renderer, font_im_menu4.getTexture(), nullptr, &positionTitre_touch);
    

}

void SDLMenu::sdlAffMenuMaison(SDL_Renderer* renderer)
{
    //INITIALISATION DES IMAGES DE TOUCHES
    im_menu.draw(renderer, longeur * 4 / 5 * tailleSprite, 0, longeur / 5 * tailleSprite, hauteur * tailleSprite);
    im_home_bottom1.draw(renderer, longeur * 4 / 5 * tailleSprite, tailleSprite, tailleSprite, tailleSprite);

    //AFFICER LES IMAGES DU MENU DANS LA FENETRE
    SDL_RenderCopy(renderer, font_im_menu1.getTexture(), nullptr, &positionTitre_menu_maison);

    //AFFICER DU TEXT DE MENU DANS LA FENETRE
    SDL_RenderCopy(renderer, font_im_menu2.getTexture(), nullptr, &positionTitre_touch);
    
}

void SDLMenu::sdlAffScore(SDL_Renderer* renderer, unsigned int score1, unsigned int score2, int t)
{

    //AJOUT LE TEXT DU SCORE DE BOIS DANS RENDERER
    string bois_score = "Tree score: " + to_string(score1);
    font_im_score_bois.setSurface(TTF_RenderText_Solid(font, bois_score.c_str(), font_color_bois));
    font_im_score_bois.loadFromCurrentSurface(renderer);
    
    //AJOUT LE TEXT DU SCORE DE BLE DANS RENDERER
    string ble_score = "Nutri score: " + to_string(score2);
    font_im_score_ble.setSurface(TTF_RenderText_Solid(font, ble_score.c_str(), font_color_ble));
    font_im_score_ble.loadFromCurrentSurface(renderer);

    int min = (int)(t/60);
    int sec = t - min*60;
    string temp = "Tsunami timer: " + to_string(min) + ":" + (sec < 10 ? "0" : "") + to_string(sec) + "/3:00";
    /*
    int min_ataque = (int)(t/60000);
    int sec_ataque = (int)(t/1000-min*60);
    string temp_ataque = "Tsunami taimer: " + to_string(min) + ":" + to_string(sec) + "/5:00";
    */
    if(min >=2)
    {
        font_im_temp.setSurface(TTF_RenderText_Solid(font, temp.c_str(), font_color_remp_critique));
    }
    else
    {
        font_im_temp.setSurface(TTF_RenderText_Solid(font, temp.c_str(), font_color));
    }

    /*if(min_ataque >=3)
    {
        font_im_temp_ataque.setSurface(TTF_RenderText_Solid(font, temp_ataque.c_str(), font_color_remp_critique));
    }else
    {
        font_im_temp_ataque.setSurface(TTF_RenderText_Solid(font, temp_ataque.c_str(), font_color));
    }*/
    font_im_temp.loadFromCurrentSurface(renderer);

    //AFFICER LA SCORE DANS LA FENETRE
    SDL_RenderCopy(renderer, font_im_score_bois.getTexture(), nullptr, &positionTitre_bois);
    SDL_RenderCopy(renderer, font_im_score_ble.getTexture(), nullptr, &positionTitre_ble);
    SDL_RenderCopy(renderer, font_im_temp.getTexture(), nullptr, &positionTitre_temp);

    //AJOUTER LES OMAGES DE SCORE
    im_score_bois.draw(renderer,positionTitre_bois.x + positionTitre_bois.w +5, positionTitre_bois.y , positionTitre_bois.h , positionTitre_bois.h );
    im_score_ble.draw(renderer, positionTitre_ble.x + positionTitre_ble.w +5, positionTitre_ble.y , positionTitre_ble.h , positionTitre_ble.h);
    
    font_im_temp.free();
    font_im_score_ble.free();
    font_im_score_bois.free();
}
