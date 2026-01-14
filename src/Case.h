#ifndef _CASE_H
#define _CASE_H

#include "Maison.h"

/**
 * @class Case
 * @brief Représente une case individuelle sur le terrain du jeu.
 *
 * Une case peut être de différents types (terre, océan, forêt, maïs) et peut être occupée
 * par une maison, un personnage ou autre entité.
 */
class Case
{

public:

    /**
     * @enum Type_Case
     * @brief Enumération des types de case possibles.
     */
    enum Type_Case
    {
        Terre = 0, ///< Case de type terre
        Ocean = 1, ///< Case de type océan (infranchissable ou spéciale)
        Foret = 2, ///< Case contenant une forêt
        Mais = 3   ///< Case contenant du maïs
    };

    /**
     * @enum Type_Occup
     * @brief Enumération des types d’occupation possibles sur une case.
     */
    enum Type_Occup
    {
        Aucun = 3,      ///< Aucun occupant
        Maison = 4,     ///< Occupée par une maison
        Personnage = 5, ///< Occupée par un personnage
        Autre = 6       ///< Autre occupation
    };

private:
    unsigned int x, y; ///< Coordonnées de la case
    Type_Case caseType; ///< Type de la case
    Type_Occup occupationType; ///< Type d’occupation
    bool occupationPersonage = false; ///< Indique si un personnage occupe la case

public:

    /**
     * @brief Constructeur par défaut.
     */
    Case();

    /**
     * @brief Constructeur avec paramètres.
     * @param x_given Coordonnée X.
     * @param y_given Coordonnée Y.
     * @param caseType_given Type de la case.
     */
    Case(unsigned int x_given, unsigned int y_given, Type_Case caseType_given);

    /**
     * @brief Retourne une référence à l'objet courant.
     */
    Case &getCase();

    /**
     * @brief Retourne un pointeur constant sur l'objet courant.
     */
    const Case *getCaseConst() const;

    /**
     * @brief Initialise la case comme de la terre.
     */
    void initializeCase_Terre();

    /**
     * @brief Initialise la case comme de l’océan.
     */
    void initializeCase_Ocean();

    /**
     * @brief Initialise la case comme une forêt.
     */
    void initializeCase_Foret();

    /**
     * @brief Initialise la case comme contenant du maïs.
     */
    void initializeCase_Mais();

    /**
     * @brief Récupère le type de la case.
     * @return Le type de la case.
     */
    Type_Case getType() const;

    /**
     * @brief Vérifie si la case est occupée.
     * @return `true` si la case est occupée, `false` sinon.
     */
    const bool isOccupied() const;

    /**
     * @brief Vérifie si la case est de type océan.
     * @return `true` si c'est un océan, `false` sinon.
     */
    const bool isOcean() const;

    /**
     * @brief Récupère le type d’occupation de la case.
     * @return Type d’occupation actuel.
     */
    Type_Occup getOccupationType() const;

    /**
     * @brief Occupe la case avec un personnage.
     */
    void occupyPersonnage();

    /**
     * @brief Coupe la forêt présente sur la case (si applicable).
     * @return `true` si l'action a réussi.
     */
    bool cutForest();

    /**
     * @brief Plante du maïs sur la case.
     * @return `true` si l'action a réussi.
     */
    bool raiseMais();

    /**
     * @brief Coupe du maïs sur la case.
     * @return `true` si l'action a réussi.
     */
    bool cutMais();

    /**
     * @brief Construit une maison sur la case.
     * @return `true` si l'action a réussi.
     */
    bool buildHouse();

    /**
     * @brief Détruit la maison présente sur la case.
     * @return `true` si l'action a réussi.
     */
    bool destroyHouse();

    /**
     * @brief Libère l’occupation de la case.
     */
    void clearOccupation();

    /**
     * @brief Libère uniquement l'occupation par un personnage.
     */
    void clearOccupyByPersonage();

    /**
     * @brief Vérifie si la case est occupée par un personnage.
     * @return `true` si un personnage est présent.
     */
    bool occupiedByPersonage() const;
};

#endif
