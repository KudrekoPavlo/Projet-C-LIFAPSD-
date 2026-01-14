#ifndef _SDLMENU_JEU_H
#define _SDLMENU_JEU_H

#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDLSprite.h"

/**
 * @class SDLMenuJeu
 * @brief Classe gérant le menu du jeu avec options de départ et règles.
 *
 * Cette classe est utilisée pour gérer l'affichage du menu principal du jeu,
 * ainsi que le menu des règles, à l'aide de sprites et de texte. Elle permet
 * d'afficher des informations de jeu, des commandes et des règles, et d'interagir
 * avec l'utilisateur via des événements clavier et souris.
 */
class SDLMenuJeu
{
private:
    int tailleSprite; ///< Taille du sprite utilisé pour les images de fond.
    int longeur; ///< Longueur de la zone de texte pour les titres.
    int hauteur; ///< Hauteur de la zone de texte pour les titres.

    TTF_Font *font_name; ///< Police de caractères pour le nom du jeu.
    TTF_Font *font_basique; ///< Police de caractères de base.

    SDLSprite im_background; ///< Sprite représentant l'image de fond du menu.
    SDLSprite im_background2; ///< Sprite représentant une autre image de fond.

    SDL_Color text_color; ///< Couleur du texte des titres et options.
    SDL_Color text_color_regles; ///< Couleur du texte des règles du jeu.

    std::string name_jeu; ///< Nom du jeu.
    std::string regle_de_jeu; ///< Règles du jeu.
    std::string touche_play; ///< Texte indiquant la touche pour jouer.
    std::string touche_regles; ///< Texte indiquant la touche pour afficher les règles.
    std::string touche_sortir; ///< Texte indiquant la touche pour quitter.
    std::string touche_retour; ///< Texte indiquant la touche pour revenir au menu.
    std::string creators; ///< Nom des créateurs du jeu.

    SDLSprite font_name_jeu; ///< Sprite pour afficher le nom du jeu.
    SDLSprite font_regle_de_jeu; ///< Sprite pour afficher les règles du jeu.
    SDLSprite font_touche_play; ///< Sprite pour afficher la touche "Play".
    SDLSprite font_touche_regles; ///< Sprite pour afficher la touche "Regles".
    SDLSprite font_touche_sortir; ///< Sprite pour afficher la touche "Quitter".
    SDLSprite font_touche_retour; ///< Sprite pour afficher la touche "Retour".
    SDLSprite font_creators; ///< Sprite pour afficher les créateurs du jeu.

    SDL_Rect positionTitre_name_jeu; ///< Position du texte pour le nom du jeu.
    SDL_Rect positionTitre_regle_de_jeu; ///< Position du texte pour les règles du jeu.
    SDL_Rect positionTitre_touche_play; ///< Position du texte pour la touche "Play".
    SDL_Rect positionTitre_touche_regles; ///< Position du texte pour la touche "Regles".
    SDL_Rect positionTitre_touche_sortir; ///< Position du texte pour la touche "Quitter".
    SDL_Rect positionTitre_touche_retour; ///< Position du texte pour la touche "Retour".
    SDL_Rect positionTitre_creators; ///< Position du texte pour les créateurs du jeu.

    SDL_Event event; ///< Événements de la SDL pour gérer les interactions utilisateur.

    Mix_Chunk *sound; ///< Son joué lors des interactions avec le menu.

    bool finDeMenu; ///< Indique si le menu est terminé.
    bool menuRegles; ///< Indique si le menu des règles est ouvert.

public:
    /**
     * @brief Constructeur de la classe SDLMenuJeu.
     * @param renderer Le renderer SDL où dessiner les éléments du menu.
     * @param x La position X de l'affichage du menu.
     * @param y La position Y de l'affichage du menu.
     * @param ts La taille du sprite utilisé dans le menu.
     *
     * Charge les images de fond, les styles de texte, et initialise les positions
     * des éléments du menu. Charge également les règles du jeu et les commandes.
     */
    SDLMenuJeu(SDL_Renderer *renderer, unsigned int x, unsigned int y, unsigned int ts);

    /**
     * @brief Destructeur de la classe SDLMenuJeu.
     *
     * Libère les ressources associées aux images, aux sons et aux autres objets.
     */
    ~SDLMenuJeu();

    /**
     * @brief Affiche le menu principal du jeu.
     * @param renderer Le renderer SDL où dessiner le menu.
     *
     * Affiche le menu principal avec les différentes options disponibles (jouer, règles, quitter).
     */
    void affMenuPrencipal(SDL_Renderer *renderer);

    /**
     * @brief Affiche le menu des règles du jeu.
     * @param renderer Le renderer SDL où dessiner le menu des règles.
     *
     * Affiche un écran contenant les règles du jeu.
     */
    void affMenuRegles(SDL_Renderer *renderer);

    /**
     * @brief Gère la boucle principale du menu.
     * @param renderer Le renderer SDL où dessiner les éléments du menu.
     * @param exit Variable indiquant si le jeu doit se fermer.
     *
     * Affiche le menu principal et gère les événements associés (sélection d'options, transitions, etc.).
     */
    void boucleMenuPrencipal(SDL_Renderer *renderer, bool &exit);
};

#endif
