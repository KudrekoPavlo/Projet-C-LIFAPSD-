#ifndef _Maison_H
#define _Maison_H

#include "Case.h"
#include "Personage.h"
#include <vector>
using namespace std;

/**
 * @class Maison
 * @brief Représente une maison dans le jeu.
 *
 * La maison peut accueillir un nombre limité de personnages, accumule un score,
 * peut être endommagée, et suivre si elle est détruite ou non.
 */
class Maison
{

private:
    unsigned int mx; ///< Coordonnée X de la maison
    unsigned int my; ///< Coordonnée Y de la maison
    unsigned int score; ///< Score associé à la maison
    unsigned int max_people; ///< Nombre maximal de personnes pouvant entrer
    unsigned int current_people; ///< Nombre actuel de personnes à l'intérieur
    vector<unsigned int> Person; ///< Liste des identifiants des personnages dans la maison
   bool destroyed; ///< Indique si la maison est détruite
public:
/**
     * @brief Constructeur de la maison.
     * @param x Coordonnée X
     * @param y Coordonnée Y
     */
    Maison(int x, int y);

    /**
     * @brief Récupère la position X de la maison.
     * @return La coordonnée X
     */
    int getMX() const;
     /**
     * @brief Récupère la position Y de la maison.
     * @return La coordonnée Y
     */
    int getMY() const;
    /**
     * @brief Récupère le score de la maison.
     * @return Le score
     */
    unsigned int getScore() const;

    /**
     * @brief Récupère une référence vers cette maison.
     * @return Référence vers l'objet Maison
     */
    Maison &getMaison();
    /**
     * @brief Fait entrer un certain nombre de personnages dans la maison.
     * @param people Le nombre de personnes à faire entrer
     */
    void personageEnter(unsigned int people);

    /**
     * @brief Fait sortir un certain nombre de personnages de la maison.
     * @param people Le nombre de personnes à faire sortir
     */
    void personageExit(unsigned int people);
    /**
     * @brief Vérifie si un personnage est à l'intérieur de la maison selon ses coordonnées.
     * @param posX_personage Position X du personnage
     * @param posY_personage Position Y du personnage
     * @return true si le personnage est à l'intérieur, false sinon
     */
    
    bool isInside(int posX_personage, int posY_personage) const;

    /**
     * @brief Inflige des dégâts à la maison.
     * @param damage Le montant des dégâts
     * @return Le score mis à jour
     */
    unsigned int damage(unsigned int damage);

    /**
     * @brief Ajoute un personnage à la liste interne.
     * @param i Identifiant du personnage
     */
    void addPersonage(unsigned int i);

    /**
     * @brief Vérifie si la maison est détruite.
     * @return true si détruite, false sinon
     */
    bool getDistroyed();
    // void destroy();
};

#endif
