#include <iostream>
#include <cmath>

using namespace std;
/**
 * @typedef Pair
 * @brief Définit un couple de coordonnées (x, y).
 */
typedef pair<int, int> Pair;

/**
 * @struct Node
 * @brief Représente un nœud utilisé dans un algorithme de pathfinding (A*, etc.).
 *
 * Contient les coordonnées, les distances, l'heuristique et un pointeur vers le parent.
 */
struct Node
{
    
    int x; ///< Coordonnée X du nœud
    int y; ///< Coordonnée Y du nœud
    int distanceFromStart; ///< Distance depuis le point de départ (g)
    int distanceFromGoal; ///< Distance estimée vers la destination (h)
    int heuristic; ///< Somme g + h (utilisée pour la priorisation)
    Node *parent; ///< Pointeur vers le nœud parent (pour reconstruire le chemin)

    /**
     * @brief Constructeur du nœud.
     * @param x Coordonnée X
     * @param y Coordonnée Y
     * @param g Distance depuis le départ
     * @param h Distance estimée vers l’arrivée
     * @param parent Pointeur vers le parent (optionnel)
     */
    Node(int x, int y, int g, int h, Node *parent = nullptr)
        : x(x), y(y), distanceFromStart(g), distanceFromGoal(h), heuristic(g + h), parent(parent) {}

    /**
     * @struct CompareNodes
     * @brief Compare deux nœuds selon leur heuristique.
     *
     * Utilisé pour organiser une file de priorité (plus petite heuristique = plus haute priorité).
     */
    struct CompareNodes
    {
        /**
         * @brief Compare deux pointeurs de nœuds.
         * @param a Premier nœud
         * @param b Deuxième nœud
         * @return true si `a` a une plus grande heuristique que `b`
         */
        bool operator()(const Node *a, const Node *b)
        {
            return a->heuristic > b->heuristic; // Smallest heuristic has highest priority
        }
    };
    /**
     * @brief Calcule la distance heuristique entre deux points (euclidienne).
     * @param x1 Coordonnée X du point de départ
     * @param y1 Coordonnée Y du point de départ
     * @param x2 Coordonnée X de la destination
     * @param y2 Coordonnée Y de la destination
     * @return La distance heuristique
     */

    static int calculerHeuristic(int x1, int y1, int x2, int y2)
    {
        return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    }
};
