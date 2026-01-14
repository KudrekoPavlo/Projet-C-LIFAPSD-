#ifndef _SDL_MESSAGE_H
#define _SDL_MESSAGE_H

#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "SDLSprite.h"
#include "../Events.h"

/**
 * @class SDLMessage
 * @brief Classe permettant d'afficher des messages sur l'écran dans un jeu SDL.
 *
 * Cette classe gère l'affichage de messages à l'écran, en utilisant des sprites
 * et du texte pour informer le joueur de divers événements du jeu. Elle prend en charge
 * l'affichage de messages d'erreurs, de validité des cases, et d'autres notifications.
 */
class SDLMessage
{
private:
    int tailleSprite; ///< Taille du sprite pour l'affichage du message.
    int longeur; ///< Longueur de la zone de texte.
    int hauteur; ///< Hauteur de la zone de texte.
    TTF_Font *font; ///< Police de caractères pour afficher les messages.

    SDL_Color text_color; ///< Couleur du texte des messages.

    std::string case_non_valid; ///< Message pour une case non valide.
    std::string err_no_wood; ///< Message d'erreur lié au bois manquant.
    std::string err_no_food; ///< Message d'erreur lié à la nourriture manquante.

    SDLSprite font_case_non_valid; ///< Sprite associé au message "case non valide".
    SDLSprite font_err_no_wood; ///< Sprite associé au message d'erreur "pas de bois".
    SDLSprite font_err_no_food; ///< Sprite associé au message d'erreur "pas de nourriture".

    SDL_Rect positionTitre; ///< Position du titre du message à afficher.

    clock_t timer; ///< Timer pour contrôler la durée d'affichage du message.

public:
    /**
     * @brief Constructeur de la classe SDLMessage.
     * @param renderer Le renderer SDL où afficher les messages.
     * @param f La police de caractères utilisée pour afficher le texte.
     * @param x La position en X de l'affichage des messages.
     * @param y La position en Y de l'affichage des messages.
     * @param ts Taille du sprite pour le message.
     *
     * Initialise les styles de texte, les positions et charge les sprites pour les messages.
     */
    SDLMessage(SDL_Renderer *renderer, TTF_Font *f, unsigned int x, unsigned int y, unsigned int ts);

    /**
     * @brief Destructeur de la classe SDLMessage.
     *
     * Libère les ressources associées aux sprites et autres objets de la classe.
     */
    ~SDLMessage();

    /**
     * @brief Affiche les messages à l'écran en fonction des événements du jeu.
     * @param renderer Le renderer SDL où dessiner les messages.
     * @param e L'objet Event contenant l'état des différents événements du jeu.
     *
     * Affiche des messages à l'écran si les événements correspondants sont activés
     * (par exemple, erreurs, messages d'information, etc.).
     */
    void affMessages(SDL_Renderer *renderer, Event &e);
};

#endif
