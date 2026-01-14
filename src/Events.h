#ifndef EVENT_H
#define EVENT_H

#include <iostream>

/**
 * @class Event
 * @brief Classe représentant les événements dans le jeu.
 *
 * Cette classe regroupe tous les états déclenchés par l'utilisateur ou par le système
 * pendant une boucle de jeu : clics souris, appuis clavier, menus, erreurs, victoires, etc.
 */
class Event
{
public:
    bool fermer;                  ///< Indique si la fenêtre doit être fermée
    bool sourisClique;            ///< Indique si un clic souris a eu lieu
    bool clavierClique;           ///< Indique si une touche a été pressée
    bool menuOpen;                ///< Indique si le menu est ouvert
    bool homeInConstruction;      ///< Indique si une maison est en construction
    bool homeMenuIsOpen;          ///< Indique si le menu de la maison est ouvert
    bool personageInCreation;     ///< Indique si un personnage est en cours de création
    bool incident;                ///< Indique si un incident est survenu
    bool victoir;                 ///< Indique si la victoire a été atteinte
    bool perdre;                  ///< Indique si le joueur a perdu
    bool errMais;                 ///< Erreur liée à la construction de maison
    bool errBois;                 ///< Erreur liée au bois (ressources)
    bool caseMaisonNonValid;     ///< Indique si la case maison est invalide

    char derniereTouche;          ///< Dernière touche appuyée au clavier
    int sourisX, sourisY;         ///< Position de la souris
    int propreX, propreY;         ///< Position transformée ou relative (à préciser selon usage)

    /**
     * @brief Constructeur par défaut.
     *
     * Initialise tous les booléens à `false` et les coordonnées à zéro.
     */
    Event();

    /**
     * @brief Réinitialise tous les événements.
     *
     * Met tous les booléens à `false` et les coordonnées à zéro.
     */
    void renouveller();

    /**
     * @brief Réinitialise les événements liés à une boucle.
     *
     * Met certains booléens à `false` (ex : clics, touches...) sans toucher aux événements plus durables.
     */
    void destructionEventPourBoucle();
};

#endif
