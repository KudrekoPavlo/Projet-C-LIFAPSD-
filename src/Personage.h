#ifndef _PERSONAGE_H
#define _PERSONAGE_H

#include <vector>
#include "Events.h"
#include <SDL2/SDL.h>
#include "Chronolog.h"

class Maison;
class Terrain;
using namespace std;
typedef pair<int, int> Pair;
/**
 * @class Personage
 * @brief Représente un personnage dans le jeu.
 *
 * Cette classe gère les actions, déplacements, états, et interactions
 * d'un personnage avec les éléments du terrain (arbres, maisons, ennemis, etc.).
 */
class Personage
{
private:
    int m_x, m_y; ///< Position X et Y du personnage
    int moveToX = 0; ///< Destination X pour le déplacement
    int moveToY = 0; ///< Destination Y pour le déplacement
    int indexEnemyToKill; ///< Index de l'ennemi à éliminer
    bool cacheDansMaison; ///< Indique si le personnage est caché dans une maison
    bool busyCutingTree = false; ///< Indique si le personnage coupe un arbre
    bool busyCutingMais = false; ///< Indique si le personnage coupe du maïs
    bool killingEnemy = false; ///< Indique si le personnage est en train d'attaquer un ennemi
    Chronolog chronCut; ///< Chronologie pour la coupe d’arbre ou de maïs

    /**
     * @brief Trouve un chemin vers la position cible.
     * @param xFin Coordonnée X de la destination
     * @param yFin Coordonnée Y de la destination
     * @return Un vecteur de positions représentant le chemin
     */
    vector<Pair> findWay(int xFin, int yFin);

public:
    bool enemyAlive; ///< Indique si un ennemi ciblé est encore vivant
    Chronolog chron; ///< Chronologie générale du personnage
    bool chosen; ///< Indique si le personnage est sélectionné
    bool movePersonnage; ///< Indique si le personnage est en mouvement
    vector<Pair> pathPersonage; ///< Chemin à suivre pour le personnage
    bool enemy = false; ///< Indique si le personnage est un ennemi
    int indexPathPersonage = 0; ///< Index actuel dans le chemin

    /**
     * @brief Constructeur par défaut.
     */
    Personage();

    /**
     * @brief Constructeur avec position initiale.
     * @param x Position X initiale
     * @param y Position Y initiale
     */
    Personage(int x, int y);

    /**
     * @brief Récupère la position X du personnage.
     * @return Position X
     */
    int getX() const;

    /**
     * @brief Récupère la position Y du personnage.
     * @return Position Y
     */
    int getY() const;

    // void move(int posX, int posY, vector<Pair> path, Chronolog chron); // Method to move the personage
    
    /**
     * @brief Déplace le personnage d'une case vers une position donnée.
     * @param posX Destination X
     * @param posY Destination Y
     */
    void moveOneSquare(int posX, int posY);
    /**
     * @brief Met à jour l'état du personnage selon l'événement.
     * @param e L'événement déclencheur
     * @param maisons Liste de maisons
     * @param terre Pointeur vers le terrain
     */
    void updatePersonage(Event e, const vector<Maison> *maisons, Terrain *terre);

    /**
     * @brief Positionne le personnage à une nouvelle position.
     * @param x Nouvelle position X
     * @param y Nouvelle position Y
     */
    void getPersonage(int x, int y);

    /**
     * @brief Vérifie si le personnage est caché dans une maison.
     * @return true si caché, false sinon
     */
    bool getcacheDansMaison() const;
/**
     * @brief Définit l’état caché dans une maison.
     * @param val true ou false
     */
    void setcacheDansMaison(bool val);
    /**
     * @brief Définit si le personnage est en train de couper du maïs.
     * @param val true ou false
     */
    void setBusyCutingMais(bool val);
    /**
     * @brief Définit si le personnage est en train de couper un arbre.
     * @param val true ou false
     */
    void setBusyCutingTree(bool val);
    /**
     * @brief Vérifie si le personnage coupe du maïs.
     * @return true si occupé, false sinon
     */
    bool getBusyCutingMais();
/**
     * @brief Vérifie si le personnage coupe un arbre.
     * @return true si occupé, false sinon
     */
    bool getBusyCutingTree();

    /**
     * @brief Trouve un chemin entre deux points sur le terrain.
     * @param xStart Position de départ X
     * @param yStart Position de départ Y
     * @param xFin Destination X
     * @param yFin Destination Y
     * @param t Pointeur vers le terrain
     * @param enemy true si c’est un ennemi, sinon false
     * @return Vecteur représentant le chemin
     */
    static vector<Pair> findWayA(int xStart, int yStart, int xFin, int yFin, const Terrain *t, bool enemy);
/**
     * @brief Tue un personnage ennemi proche.
     * @param closestPersonage Pointeur vers le personnage à tuer
     */
    void killPersonage(Personage *closestPersonage);
};

    // bool getBusyCuting();
    //  void moveNew(const Game *t);
/**
 * @brief Récupère la position X du personnage.
 * @return Position X
 */
inline int Personage::getX() const { return m_x; }

/**
 * @brief Récupère la position Y du personnage.
 * @return Position Y
 */
inline int Personage::getY() const { return m_y; }

#endif
