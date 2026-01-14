
#ifndef _TSUNAMI_H
#define  _TSUNAMI_H

#include <iostream>
#include <vector>
      
#include "Personage.h"    
using namespace std;


/**
 * @class Tsunami
 * @brief Classe représentant un tsunami se déplaçant verticalement dans un champ de jeu.
 */

class Tsunami {
private:
    int x; // горизонтальна позиція (залишається незмінною)
    int y; // поточна вертикальна позиція
   // int height; // висота поля
    bool active;

public:
/**
     * @brief Constructeur par défaut du tsunami.
     */
    Tsunami();

    /**
     * @brief Constructeur avec position initiale.
     * @param startX Position horizontale initiale.
     * @param startY Position verticale initiale.
     */
    Tsunami(unsigned int startX, unsigned int startY);

/**
     * @brief Récupère la position horizontale du tsunami.
     * @return La position x.
     */

    int getX() const;

    /**
     * @brief Récupère la position verticale du tsunami.
     * @return La position y.
     */

    int getY() const;
/**
 * @brief Met à jour la position du tsunami.
 * Fait reculer le tsunami horizontalement s’il est actif. 
 * Le désactive lorsqu’il dépasse la limite de l’écran.
 */
    void update();
    /**
 * @brief Vérifie si le tsunami est actif.
 * @return true si actif, false sinon.
 */

    bool isActive() const;
/**
 * @brief Active le tsunami.
 */
    void activate();
/**
 * @brief Désactive le tsunami.
 */
    void disactivate();
/**
 * @brief Vérifie les collisions entre le tsunami et les personnages.
 * @param personages Pointeur vers un vecteur de personnages.
 * @return Un vecteur contenant les indices des personnages touchés par le tsunami.
 */
 vector<int> checkCollision(const vector<Personage>* personages);
};

#endif