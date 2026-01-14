#ifndef _SDLINCIDENT_H
#define _SDLINCIDENT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDLSprite.h"

/**
 * @def HOUTEUR_TERRAIN
 * @brief Hauteur du terrain de jeu.
 */
#define HOUTEUR_TERRAIN 20

/**
 * @def LONGEUR_TERRAIN
 * @brief Longueur du terrain de jeu.
 */
#define LONGEUR_TERRAIN 40

/**
 * @class SDLIncident
 * @brief Classe gérant les incidents dans le jeu, comme le tsunami.
 *
 * Cette classe est responsable de l'affichage des incidents dans le jeu, comme le tsunami. 
 * Elle utilise la bibliothèque SDL pour le rendu graphique et pour afficher les incidents à l'écran.
 */
class SDLIncident
{
private:
    unsigned int tailleSprite; ///< Taille des sprites utilisés pour les incidents.
    unsigned int longeur; ///< Largeur du terrain de jeu.
    unsigned int hauteur; ///< Hauteur du terrain de jeu.
    SDLSprite im_vague; ///< Sprite pour l'image de la vague.
    SDLSprite im_vague1; ///< Sprite pour l'image de la vague 1.
    SDLSprite im_vague2; ///< Sprite pour l'image de la vague 2.
    SDLSprite font_text_incident; ///< Sprite pour le texte des incidents.

    TTF_Font *font; ///< Police de caractères utilisée pour afficher le texte.

    SDL_Color font_color; ///< Couleur du texte des incidents.

    SDL_Rect positionTitre; ///< Position du texte à afficher sur la fenêtre.

public:
    /**
     * @brief Constructeur par défaut de la classe SDLIncident.
     *
     * Ce constructeur initialise les variables membres de la classe, mais ne charge pas encore les ressources graphiques.
     */
    SDLIncident();

    /**
     * @brief Constructeur de la classe SDLIncident avec des paramètres spécifiques.
     * @param renderer Le renderer utilisé pour dessiner les éléments sur la fenêtre.
     * @param f La police de caractères utilisée pour afficher le texte.
     * @param tS La taille des sprites.
     * @param l La largeur du terrain.
     * @param h La hauteur du terrain.
     *
     * Ce constructeur initialise les variables membres et charge les ressources graphiques nécessaires pour l'affichage des incidents.
     */
    SDLIncident(SDL_Renderer *renderer, TTF_Font *f, unsigned int tS, unsigned int l, unsigned int h);

    /**
     * @brief Destructeur de la classe SDLIncident.
     *
     * Libère les ressources allouées, comme les textures et les surfaces.
     */
    ~SDLIncident();

    /**
     * @brief Affiche l'animation du tsunami à l'écran.
     * @param renderer Le renderer utilisé pour dessiner sur la fenêtre.
     * @param pointAffichageX La position horizontale où l'animation du tsunami doit commencer.
     *
     * Cette méthode affiche l'animation du tsunami à la position spécifiée.
     */
    void sdlAffTsunami(SDL_Renderer *renderer, int pointAffichageX);
};

#endif
