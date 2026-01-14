#ifndef _GAME_H
#define _GAME_H

#include "Terrain.h"
#include "Personage.h"
#include "Events.h"
#include "Maison.h"
#include "Tsunami.h"
#include "Chronolog.h"

#include <vector>
#include <time.h>

using namespace std;
typedef pair<int, int> Pair;

/**
 * @class Game
 * @brief Classe principale qui gère la logique du jeu.
 *
 * La classe Game coordonne les personnages, les ennemis, le terrain, les événements
 * comme les tsunamis, ainsi que l'état de la partie.
 */
class Game
{

private:
    vector<Personage> personages; ///< Liste des personnages joueurs
    vector<Personage> enemies; ///< Liste des ennemis
    Terrain terrain; ///< Le terrain du jeu
    Tsunami tsunami; ///< Objet tsunami
    unsigned int tailleSprite; ///< Taille d'un sprite en pixels
    unsigned int tailleX; ///< Largeur du terrain
    unsigned int tailleY; ///< Hauteur du terrain
    clock_t clocks; ///< Horloge interne pour les chronos
    vector<Maison> maisons; ///< Liste des maisons dans le jeu

    // Chronomètres pour différents événements
    Chronolog chronTsunami, chronDureeTsunami, chronAttackEnemies, chronDureeAttack;

    void createEnemies(int numEnemies); ///< Crée un certain nombre d'ennemis

    bool victory = false; ///< Indique si la partie est gagnée
    bool attack = false; ///< Indique si une attaque est en cours

public:
/**
     * @brief Affiche le terrain dans la console.
     */
    void gameAfficherTerrain() const;

    /**
     * @brief Constructeur du jeu.
     * @param terrainWidth Largeur du terrain
     * @param terrainHeight Hauteur du terrain
     * @param tS Taille des sprites
     */
    Game(unsigned int terrainWidth, unsigned int terrainHeight, unsigned int tS);
    // void moveOnePersonage(unsigned int positionPersonnage, int xFin, int yFin);
    // vector<Pair> findWayA(int xStart, int yStart, int xFin, int yFin);
    // void move(unsigned int positionPersonnage, int xFin, int yFin);
    /**
     * @brief Ajoute un personnage joueur au jeu.
     * @param p Le personnage à ajouter
     */
    void addPersonage(const Personage &p);

    /**
     * @brief Récupère un personnage par son index dans la liste.
     * @param posPersonage Index du personnage
     * @return Pointeur vers le personnage
     */
    Personage *getPersonage(unsigned int posPersonage);
    /**
     * @brief Récupère un personnage selon sa position.
     * @param xPos Position X
     * @param yPos Position Y
     * @return Pointeur vers le personnage
     */
    Personage *getPersonage(int xPos, int yPos);

    /**
     * @brief Récupère un ennemi selon sa position.
     * @param xPos Position X
     * @param yPos Position Y
     * @return Pointeur vers l'ennemi
     */
    Personage *getEnemi(int xPos, int yPos);
    /**
     * @brief Accès au terrain du jeu.
     * @return Pointeur vers le terrain
     */
    Terrain *getTerrain();

    /**
     * @brief Accès à l'objet Tsunami.
     * @return Pointeur vers le tsunami
     */
    Tsunami *getTsunami();

    /**
     * @brief Met à jour l'état du jeu en fonction d'un événement.
     * @param e L'événement
     */
    void update(Event &e);
    // void updateTerrain(Event ev, const Personage p);

    /**
     * @brief Récupère la largeur du terrain.
     * @return Largeur
     */
    unsigned int getXTerrain();

    /**
     * @brief Récupère la hauteur du terrain.
     * @return Hauteur
     */
    unsigned int getYTerrain();

    /**
     * @brief Retourne le nombre de personnages.
     * @return Quantité de personnages
     */
    unsigned int quantitePersonages();

    /**
     * @brief Retourne le nombre d'ennemis.
     * @return Quantité d'ennemis
     */
    unsigned int quantiteEnemis();
    /**
     * @brief Récupère un ennemi par son index.
     * @param posEnemies Index de l'ennemi
     * @return Pointeur vers l'ennemi
     */
    Personage *getEnemies(unsigned int posEnemies);

    /**
     * @brief Vérifie si une maison existe à une position.
     * @param x Position X
     * @param y Position Y
     * @return true si une maison est présente, sinon false
     */
    bool retrouverMaison(int x, int y);

    /**
     * @brief Retourne la liste des personnages.
     * @return Pointeur vers la liste
     */
    const vector<Personage> *getPersonages() const
    {
        return &personages;
    }

    /**
     * @brief Ajoute une maison dans le jeu.
     * @param m La maison à ajouter
     */
    void addMaison(Maison m);

    /**
     * @brief Retourne la liste des maisons.
     * @return Pointeur vers le vecteur de maisons
     */
    const vector<Maison> *getMaison() const;

    /**
     * @brief Lance une attaque des ennemis.
     */
    void attackEnemies();

    /**
     * @brief Retourne la liste des ennemis.
     * @return Pointeur vers le vecteur d'ennemis
     */
    vector<Personage> *getEnemies();

    /**
     * @brief Donne le temps écoulé depuis le début du jeu.
     * @return Temps en secondes
     */
    int getTime();

    /**
     * @brief Vérifie si une maison à une position donnée est détruite.
     * @param x Position X
     * @param y Position Y
     * @return true si détruite, sinon false
     */
    bool getMaisonDistructed(unsigned int x , unsigned int y);
    //  void startGame();
};

#endif
