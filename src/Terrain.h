#ifndef _Terrain_H
#define _Terrain_H

#include "Case.h"
#include "Maison.h"
#include "Events.h"
#include "Personage.h"
#include "Chronolog.h"
#include <vector>

using namespace std;

/// Alias pour une ligne de cases (TabCase)
typedef vector<Case> TabCase;

/**
 * @class Terrain
 * @brief Représente la grille du terrain dans le jeu, gérant les forêts, les maïs, les maisons et les événements.
 */
class Terrain
{
private:
    unsigned int wood;         ///< Quantité de bois disponible
    unsigned int mais;         ///< Quantité de maïs disponible
    unsigned int dx, dy;       ///< Dimensions du terrain

    unsigned int initialNB_Forest; ///< Nombre initial de cases forêt
    unsigned int initialNB_Mais;   ///< Nombre initial de cases maïs

    vector<TabCase> grid;      ///< Grille 2D représentant le terrain
    vector<Maison> houses;     ///< Liste des maisons sur le terrain

    Chronolog chronCut;        ///< Chronologie des événements de coupe de forêt

public:
/**
     * @brief Constructeur d'un terrain avec les dimensions données.
     * @param width Largeur du terrain.
     * @param height Hauteur du terrain.
     */
    Terrain(unsigned int width, unsigned int height);

    /// @return La largeur du terrain.
    unsigned int getDimX() const;

    /// @return La hauteur du terrain.
    unsigned int getDimY() const;
    /**
     * @brief Accède à une case modifiable du terrain.
     * @param x Coordonnée X
     * @param y Coordonnée Y
     * @return Référence à la case
     */
    Case &getCase_FromTerrain(unsigned int x, unsigned int y);
    /**
     * @brief Accède à une case constante du terrain.
     * @param x Coordonnée X
     * @param y Coordonnée Y
     * @return Pointeur vers la case constante
     */
    const Case *getCase_FromTerrainConst(unsigned int x, unsigned int y) const;

    /// @return La grille du terrain (en lecture seule).
    const vector<TabCase> &getGrid() const;

    // @return La liste des maisons présentes sur le terrain.
    const vector<Maison> &getHouses() const;

    /// @brief Affiche la carte du terrain avec les types de cases. (pour debugger)
    void afficherTerrain() const;

    // @brief Affiche la carte du terrain avec l'occupation des cases. (pour debugger)
    void afficherTerrain_Occup() const;

    /// @return Le nombre de maisons sur le terrain.
    size_t getMaisonCount() const;

    /**
     * @brief Vérifie si la case est de type Terre.
     * @param x Coordonnée X
     * @param y Coordonnée Y
     * @return Vrai si la case est de type Terre
     */
    const bool isTerre(unsigned int x, unsigned int y) const;

    /**
 * @brief Vérifie si la case aux coordonnées données est valide.
 * @param x Coordonnée X de la case.
 * @param y Coordonnée Y de la case.
 * @return Vrai si la case est valide, sinon faux.
 */
    bool isValidCase(unsigned int x, unsigned int y);

    /**
 * @brief Coupe la forêt sur le terrain en fonction de l'événement.
 * @param e L'événement qui contient les informations de la souris.
 */
    
    void cutForest_onTerrain_newVersion(Event e);
    /**
 * @brief Couper un arbre dans la case du terrain spécifiée par (x, y).
 * 
 * Cette méthode coupe un arbre sur la case spécifiée et ajoute du bois au stock.
 * 
 * @param x Position X de la case sur le terrain.
 * @param y Position Y de la case sur le terrain.
 */
    void cutForest_onTerrain(unsigned int x, unsigned int y);
    /**
 * @brief Construire une maison sur la case spécifiée par (x, y).
 * 
 * Cette méthode permet de construire une maison si les conditions sont remplies :
 * - Le terrain doit être libre.
 * - Le stock de bois doit être suffisant (15 unités de bois nécessaires).
 * 
 * @param x Position X de la case sur le terrain.
 * @param y Position Y de la case sur le terrain.
 * @param ev Événement contenant les informations de l'état de la construction.
 */
    void buildHouse_onTerrain(unsigned int x, unsigned int y, Event & ev);

    // void raiseMais_onTerrain(unsigned int x, unsigned int y);

/**
 * @brief Couper du maïs sur la case spécifiée par (x, y).
 * 
 * Cette méthode coupe du maïs sur la case spécifiée et ajoute des unités de maïs au stock.
 * 
 * @param x Position X de la case sur le terrain.
 * @param y Position Y de la case sur le terrain.
 */
    void cutMais_onTerrain(unsigned int x, unsigned int y);

/**
 * @brief Vérifie si les conditions pour construire une maison sont remplies à la position du personnage.
 * 
 * Cette méthode vérifie si le stock de bois est suffisant et si les cases autour du personnage sont valides 
 * pour construire une maison.
 * 
 * @param e Événement qui contient des informations sur les erreurs potentielles.
 * @param p Personnage qui tente de construire la maison.
 * @return true Si la construction est possible.
 * @return false Si les conditions ne sont pas remplies.
 */
    bool radarHouse(Event &e, Personage p);

/**
 * @brief Détruire une maison à la position spécifiée par un objet Maison.
 * 
 * Cette méthode détruit une maison située aux coordonnées (x, y) de la maison spécifiée.
 * Les cases sont libérées et la maison est supprimée de la liste.
 * 
 * @param m Maison à détruire.
 */
    void destroyHouse_onTerrain(const Maison &m); // dorobiti

/**
 * @brief Compter le nombre d'arbres présents sur le terrain.
 * 
 * Cette méthode parcourt toutes les cases du terrain et compte celles qui contiennent des arbres.
 * 
 * @return Nombre d'arbres sur le terrain.
 */
    unsigned int countForet() const;
    /**
 * @brief Compter le nombre de maïs présents sur le terrain.
 * 
 * Cette méthode parcourt toutes les cases du terrain et compte celles qui contiennent du maïs.
 * 
 * @return Nombre de maïs sur le terrain.
 */
    unsigned int countMais() const;

/**
 * @brief Met à jour les forêts et le maïs sur le terrain en fonction de l'état actuel.
 * 
 * Cette méthode génère de nouvelles forêts et du maïs si leur nombre actuel est inférieur à 50% de leur valeur initiale.
 */
    void updateForest_Mais();

/**
 * @brief Met à jour le terrain, en tenant compte des actions des personnages.
 * 
 * Cette méthode met à jour le terrain en fonction des événements et des actions des personnages,
 * par exemple couper des arbres ou récolter du maïs.
 * 
 * @param e Événement contenant des informations sur les actions du personnage.
 * @param personages Liste des personnages sur le terrain.
 */
    void updateTerrain(Event e, const vector<Personage> *personages);

/**
 * @brief Récupérer le nombre de bois disponible.
 * 
 * Cette méthode retourne la quantité de bois actuellement disponible.
 * 
 * @return Quantité de bois.
 */
    const unsigned int getWood();
    /**
 * @brief Récupérer le nombre de maïs disponible.
 * 
 * Cette méthode retourne la quantité de maïs actuellement disponible.
 * 
 * @return Quantité de maïs.
 */
    const unsigned int getMais();

/**
 * @brief Diminuer le nombre de maïs disponible.
 * 
 * Cette méthode réduit la quantité de maïs de 30 unités.
 */
    void minusMais();

/**
 * @brief Occuper une case sur le terrain avec un personnage.
 * 
 * Cette méthode marque une case comme occupée par un personnage à la position (x, y).
 * 
 * @param x Position X de la case sur le terrain.
 * @param y Position Y de la case sur le terrain.
 */
    void occupyPersonnage(unsigned int x, unsigned int y);
    /**
 * @brief Libérer l'occupation d'une case sur le terrain.
 * 
 * Cette méthode libère une case précédemment occupée par un personnage à la position (x, y).
 * 
 * @param x Position X de la case sur le terrain.
 * @param y Position Y de la case sur le terrain.
 */
    void clearOccupation(int x, int y);

/**
 * @brief Libérer l'occupation d'une case spécifique occupée par un personnage.
 * 
 * Cette méthode libère l'occupation spécifique d'un personnage à la position (x, y).
 * 
 * @param x Position X de la case sur le terrain.
 * @param y Position Y de la case sur le terrain.
 */
    void clearOccupyByPersonage(int x, int y);

    // void forestUpdate();
};

#endif