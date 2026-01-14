#ifndef _SDL_SPRITE_H
#define _SDL_SPRITE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/**
 * @class SDLSprite
 * @brief Classe représentant un sprite chargé en mémoire dans SDL.
 *
 * Cette classe permet de gérer des images (sprites) dans une application SDL,
 * avec des fonctionnalités pour charger des images, les dessiner à l'écran,
 * et gérer la mémoire associée aux textures SDL.
 */
class SDLSprite
{

private: 
    SDL_Surface *m_surface; ///< Surface SDL associée à l'image
    SDL_Texture *m_texture; ///< Texture SDL associée à l'image
    bool m_hasChanged; ///< Indique si l'image a été modifiée depuis son dernier chargement

public:

    /**
     * @brief Constructeur par défaut de la classe SDLSprite.
     *
     * Initialise les membres internes et prépare l'objet pour charger une image.
     */
    SDLSprite();

    /**
     * @brief Destructeur de la classe SDLSprite.
     *
     * Libère la mémoire associée à la surface et à la texture.
     */
    ~SDLSprite();

    /**
     * @brief Constructeur de recopie.
     * @param im Instance à copier.
     *
     * Crée une nouvelle instance de `SDLSprite` en copiant les données d'une autre instance.
     */
    SDLSprite(const SDLSprite &im);

    /**
     * @brief Opérateur d'assignation.
     * @param im Instance à copier.
     * @return Référence à l'objet courant.
     *
     * Permet de copier le contenu d'une instance de `SDLSprite` dans une autre.
     */
    SDLSprite &operator=(const SDLSprite &im);

    /**
     * @brief Charge une image depuis un fichier.
     * @param filename Nom du fichier image.
     * @param renderer Le renderer SDL dans lequel la texture sera chargée.
     *
     * Charge l'image depuis le fichier spécifié et la convertit en texture SDL.
     */
    void loadFromFile(const char *filename, SDL_Renderer *renderer);

    /**
     * @brief Charge une image depuis une surface existante.
     * @param renderer Le renderer SDL dans lequel la texture sera chargée.
     *
     * Convertit la surface actuelle en texture SDL.
     */
    void loadFromCurrentSurface(SDL_Renderer *renderer);

    /**
     * @brief Dessine le sprite à l'écran.
     * @param renderer Le renderer SDL dans lequel le sprite sera dessiné.
     * @param x Position en X où dessiner l'image.
     * @param y Position en Y où dessiner l'image.
     * @param w Largeur du sprite. Utilise la largeur de l'image si égal à -1.
     * @param h Hauteur du sprite. Utilise la hauteur de l'image si égal à -1.
     *
     * Dessine le sprite à la position donnée, avec une taille spécifiée.
     */
    void draw(SDL_Renderer *renderer, int x, int y, int w = -1, int h = -1);

    /**
     * @brief Modifie la surface associée au sprite.
     * @param s Nouvelle surface SDL à associer au sprite.
     *
     * Change la surface actuelle utilisée pour la texture.
     */
    void setSurface(SDL_Surface *s);

    /**
     * @brief Récupère la texture associée au sprite.
     * @return La texture SDL associée à l'image.
     */
    SDL_Texture* getTexture() const;

    /**
     * @brief Libère la mémoire associée à la surface et à la texture.
     *
     * Libère la mémoire utilisée par la surface et la texture afin d'éviter les fuites de mémoire.
     */
    void free();
};

#endif
