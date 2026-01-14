#ifndef _SDLMENU_H
#define _SDLMENU_H

#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDLSprite.h"

/**
 * @class SDLMenu
 * @brief Classe gérant l'affichage du menu du jeu.
 *
 * Cette classe est utilisée pour gérer l'affichage du menu du jeu, notamment le menu principal,
 * le menu des maisons et l'affichage des scores. Elle utilise des sprites pour dessiner les
 * éléments graphiques et du texte pour afficher les informations importantes (score, ressources, etc.).
 */
class SDLMenu
{
private:
    unsigned int tailleSprite; ///< Taille du sprite utilisé pour les éléments graphiques.
    unsigned int longeur; ///< Largeur de la zone d'affichage du terrain.
    unsigned int hauteur; ///< Hauteur de la zone d'affichage du terrain.

    TTF_Font *font; ///< Police de caractères utilisée pour afficher le texte.

    SDLSprite font_im_score_bois; ///< Sprite pour afficher le score du bois.
    SDLSprite font_im_score_ble; ///< Sprite pour afficher le score du blé.
    SDLSprite font_im_menu1; ///< Sprite pour afficher le premier menu.
    SDLSprite font_im_menu2; ///< Sprite pour afficher le deuxième menu.
    SDLSprite font_im_menu3; ///< Sprite pour afficher le troisième menu.
    SDLSprite font_im_menu4; ///< Sprite pour afficher le quatrième menu.
    SDLSprite font_im_temp; ///< Sprite pour afficher un élément temporel (par exemple, un compte à rebours).
    // SDLSprite font_im_temp_ataque; ///< Sprite pour afficher un élément spécifique lié aux attaques.

    SDL_Color font_color; ///< Couleur du texte principal.
    SDL_Color font_color_bois; ///< Couleur du texte pour le score du bois.
    SDL_Color font_color_ble; ///< Couleur du texte pour le score du blé.
    SDL_Color font_color_remp_critique; ///< Couleur du texte en cas de situation critique.

    SDLSprite im_menu; ///< Sprite pour afficher l'image de fond du menu.
    SDLSprite im_home_bottom; ///< Sprite pour afficher l'image du bas du menu d'accueil.
    SDLSprite im_home_bottom1; ///< Sprite pour afficher une autre variante de l'image du bas du menu d'accueil.
    SDLSprite im_score_bois; ///< Sprite pour afficher l'image du score du bois.
    SDLSprite im_score_ble; ///< Sprite pour afficher l'image du score du blé.

    SDL_Rect positionTitre_menu; ///< Position du titre du menu.
    SDL_Rect positionTitre_touch; ///< Position des touches dans le menu.
    SDL_Rect positionTitre_menu_maison; ///< Position du titre du menu des maisons.
    SDL_Rect positionTitre_bois; ///< Position du score du bois dans l'affichage.
    SDL_Rect positionTitre_ble; ///< Position du score du blé dans l'affichage.
    SDL_Rect positionTitre_temp; ///< Position du score temporel ou du compte à rebours.
    // SDL_Rect positionTitre_temp_eneemies; ///< Position du score des ennemis (si applicable).

public:
    /**
     * @brief Constructeur par défaut de la classe SDLMenu.
     *
     * Ce constructeur crée une instance de SDLMenu avec des valeurs par défaut.
     */
    SDLMenu();

    /**
     * @brief Constructeur de la classe SDLMenu.
     * @param renderer Le renderer SDL utilisé pour dessiner les éléments à l'écran.
     * @param f La police de caractères utilisée pour afficher le texte.
     * @param tS La taille des cases du terrain.
     * @param l La longueur du terrain.
     * @param h La hauteur du terrain.
     *
     * Ce constructeur initialise les sprites et charge les images pour le menu à partir de fichiers.
     * Il configure également la police et les couleurs des textes.
     */
    SDLMenu(SDL_Renderer *renderer, TTF_Font *f, unsigned int tS, unsigned int l, unsigned int h);

    /**
     * @brief Destructeur de la classe SDLMenu.
     *
     * Le destructeur libère les ressources associées aux textures et aux surfaces utilisées dans le menu.
     */
    ~SDLMenu();

    /**
     * @brief Affiche le menu principal du jeu.
     * @param renderer Le renderer SDL utilisé pour dessiner les éléments à l'écran.
     *
     * Affiche le menu principal du jeu avec les différentes options.
     */
    void sdlAffMenu(SDL_Renderer* renderer);

    /**
     * @brief Affiche le menu des maisons dans le jeu.
     * @param renderer Le renderer SDL utilisé pour dessiner les éléments à l'écran.
     *
     * Affiche un menu spécifique pour les maisons dans le jeu.
     */
    void sdlAffMenuMaison(SDL_Renderer* renderer);

    /**
     * @brief Affiche le score du joueur (bois et blé).
     * @param renderer Le renderer SDL utilisé pour dessiner les éléments à l'écran.
     * @param score Le score du bois à afficher.
     * @param score2 Le score du blé à afficher.
     * @param t Un paramètre supplémentaire utilisé pour afficher un élément temporel.
     *
     * Affiche les scores de ressources comme le bois et le blé à l'écran.
     */
    void sdlAffScore(SDL_Renderer* renderer, unsigned int score, unsigned int score2, int t);
};

#endif
