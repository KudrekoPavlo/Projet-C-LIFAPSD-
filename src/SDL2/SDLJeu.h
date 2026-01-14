#ifndef _SDLJEU_H
#define _SDLJEU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "../Terrain.h"
#include "../Personage.h"
#include "../Game.h"
#include "SDLSprite.h"
#include "SDLMenu.h"
#include "SDLIncident.h"
#include "../Case.h"
#include "SDLAnimation.h"
#include "SDLMenuJeu.h"
#include "SDLMessage.h"

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
 * @class SDLJeu
 * @brief Classe gérant l'affichage et l'interaction avec le jeu via SDL.
 *
 * Cette classe est responsable de la gestion du rendu graphique et de l'interaction avec le jeu,
 * y compris l'affichage du terrain, des personnages, des maisons, des ennemis et des événements.
 * Elle utilise la bibliothèque SDL pour le rendu et la gestion des événements.
 */
class SDLJeu
{
private:
    unsigned int tailleSprite; ///< Taille des sprites utilisés dans le jeu.
    unsigned int longeur; ///< Largeur du terrain de jeu.
    unsigned int hauteur; ///< Hauteur du terrain de jeu.
    bool fin; ///< Indique si le jeu est terminé.
    SDL_Window *window; ///< Fenêtre SDL.
    SDL_Renderer *renderer; ///< Renderer SDL pour dessiner à l'écran.
    SDL_Event event; ///< Événements SDL.
    Event ev; ///< Événements personnalisés pour gérer les interactions du jeu.

    TTF_Font *font; ///< Police de caractères pour le texte.

    SDLSprite font_im; ///< Sprite principal du jeu.
    SDLSprite font_im_menu1; ///< Sprite du premier menu.
    SDLSprite font_im_menu2; ///< Sprite du deuxième menu.
    SDL_Color font_color; ///< Couleur du texte.

    Mix_Chunk *sound; ///< Son principal du jeu.
    Mix_Chunk *sound_perdu; ///< Son joué lors d'une défaite.
    Mix_Chunk *sound_gagne; ///< Son joué lors d'une victoire.
    bool withSound; ///< Indique si le son est activé.

    SDLSprite im_grass; ///< Sprite pour l'herbe du terrain.
    SDLSprite im_ocean; ///< Sprite pour l'océan du terrain.
    SDLSprite im_forret; ///< Sprite pour la forêt du terrain.
    SDLSprite im_personage; ///< Sprite pour les personnages.
    SDLSprite im_personage_caher; ///< Sprite pour les personnages cachés.
    SDLSprite im_maison; ///< Sprite pour les maisons.
    SDLSprite im_ble; ///< Sprite pour le blé.
    SDLSprite im_enemie; ///< Sprite pour les ennemis.
    SDLSprite im_maison_distructed; ///< Sprite pour une maison détruite.
    SDLSprite im_personage_in_distructed_maison; ///< Sprite pour un personnage dans une maison détruite.
    SDLSprite im_victior; ///< Sprite pour l'écran de victoire.
    SDLSprite im_perdre; ///< Sprite pour l'écran de défaite.

    SDLMenu *menu; ///< Menu principal du jeu.
    SDLIncident *incidant; ///< Gestion des incidents dans le jeu.
    SDLAnimation *anim; ///< Gestion des animations dans le jeu.
    SDLMenuJeu *menu_prencipal; ///< Menu de jeu principal.
    SDLMessage *message; ///< Gestion des messages à afficher à l'écran.

public:
    /**
     * @brief Constructeur de la classe SDLJeu.
     * @param x Largeur de la fenêtre du jeu.
     * @param y Hauteur de la fenêtre du jeu.
     * @param tS Taille des sprites utilisés dans le jeu.
     *
     * Ce constructeur initialise la fenêtre, le renderer, les sprites et les sons pour commencer à afficher
     * le jeu avec les éléments graphiques et les ressources nécessaires.
     */
    SDLJeu(unsigned int x, unsigned int y, unsigned int tS);

    /**
     * @brief Destructeur de la classe SDLJeu.
     *
     * Libère les ressources utilisées par la classe SDLJeu, telles que les textures, les sons et les fenêtres.
     */
    ~SDLJeu();

    /**
     * @brief Affiche le terrain de jeu avec les informations du jeu.
     * @param ter Le terrain à afficher.
     * @param game Le jeu contenant les informations à afficher.
     *
     * Cette méthode affiche le terrain avec les éléments associés (personnages, maisons, etc.) en fonction
     * de l'état actuel du jeu.
     */
    void sdlAff(Terrain *ter, Game game);

    /**
     * @brief Récupère le renderer utilisé pour dessiner à l'écran.
     * @return Le renderer SDL utilisé pour le rendu.
     */
    SDL_Renderer *getRenderer() const;

    /**
     * @brief Gère la boucle principale du jeu.
     * @param game L'état actuel du jeu.
     *
     * Cette méthode gère la boucle principale du jeu, y compris les événements, les mises à jour du terrain
     * et l'affichage des éléments à l'écran.
     */
    void boucle(Game game);

    /**
     * @brief Affiche l'animation du tsunami.
     * @param ter Le terrain sur lequel le tsunami doit être affiché.
     * @param game Le jeu contenant les informations du tsunami.
     *
     * Cette méthode affiche l'animation du tsunami sur le terrain.
     */
    void Afftsunami(Terrain *ter, Game game);

    /**
     * @brief Affiche le menu principal du jeu.
     *
     * Cette méthode affiche le menu principal du jeu, avec des options telles que "Jouer", "Quitter", etc.
     */
    void affMenuPrencipal();

    /**
     * @brief Affiche un écran de victoire ou de défaite en fonction du résultat du jeu.
     *
     * Cette méthode affiche un écran de victoire ou de défaite après la fin du jeu, avec un message
     * indiquant si le joueur a gagné ou perdu.
     */
    void affGagnerPerdre();
};

#endif
