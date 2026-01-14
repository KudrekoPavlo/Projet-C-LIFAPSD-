#include <iostream>
#include "Personage.h"
#include "Maison.h"
#include "Node.h"
#include "Chronolog.h"
#include "Case.h"
#include <unistd.h>
#include <SDL2/SDL.h>
#include "Events.h"
#include "Terrain.h"
#include <map>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;
typedef pair<int, int> Pair;
typedef vector<Case> TabCase;
Personage::Personage()
{
    m_x = m_y = 1; // Default starting position (1, 1)
    cout << "Position personnage " << m_x << " " << m_y << endl;
    chosen = false;
    movePersonnage = false;
    // pathPersonage = {};
}

Personage::Personage(int x, int y)
{
    m_x = x;
    m_y = y;
    // debug cout
    cout << "Personnage positionné " << m_x << "  " << m_y << endl;
    chosen = false;
    movePersonnage = false;
    // pathPersonage = {};
}

bool Personage::getcacheDansMaison() const
{
    return cacheDansMaison;
}
void Personage::setcacheDansMaison(bool val)
{
    cacheDansMaison = val;
}

void Personage::setBusyCutingMais(bool val)
{
    busyCutingMais = val;
}
void Personage::setBusyCutingTree(bool val)
{
    busyCutingTree = val;
}

bool Personage::getBusyCutingTree() { return busyCutingTree; }

bool Personage::getBusyCutingMais() { return busyCutingMais; }

vector<Pair> Personage::findWay(int xFin, int yFin)
{
    vector<Pair> path;

    int currX = m_x, currY = m_y; // Starting position

    // Move horizontally first
    while (currX != xFin)
    {
        currX += (xFin > currX) ? 1 : -1;
        path.push_back(make_pair(currX, currY));
    }

    // Move vertically next
    while (currY != yFin)
    {
        currY += (yFin > currY) ? 1 : -1;
        path.push_back(make_pair(currX, currY));
    }

    // cout pour debugger
    /*cout << "Path: ";
     for (int i = 0; i < path.size(); i++)
     {
         cout << "(" << path[i].first << ", " << path[i].second << ") ";
     }*/

    return path;
}

/*bool Personage::getBusyCuting()
{
    return busyCuting;
}*/

void Personage::moveOneSquare(int posX, int posY)
{

    m_x = posX;
    m_y = posY;
    // cout << "Moved to: (" << m_x << ", " << m_y << ")" << endl;
    //  SDL_Delay(150);
}

void Personage::updatePersonage(Event e, const vector<Maison> *maisons, Terrain *terre)

{

    const vector<TabCase> &grid = terre->getGrid();

    // cout << "updatePersonnage";
    // int indexPath;

    if (busyCutingMais || busyCutingTree)
    {
        if (chronCut.hasElapsed())
        {
            busyCutingMais = false;
            busyCutingTree = false;
            // cout << "Je coupe plus " << busyCuting << endl;
        }
        else
            return;
    }
    if (!(cacheDansMaison))
    {
        for (const Maison maison : *maisons)
        {

            if (maison.isInside(m_x, m_y))
            {
                cacheDansMaison = true;
                cout << "Personage " << m_x << " " << m_y << " caché";
                break;
            }
        }
    }
    if (e.sourisClique)
    {

        if (!enemy)
            chron.defineInterval(50);

        if ((e.sourisX == m_x) && (e.sourisY == m_y))
        {
            chosen = true; // ajouter sleep for
            // cout << "i have chosen a parsonnage" << endl;
        }
        if ((chosen == true) && ((e.sourisX != m_x) || (e.sourisY != m_y)))
        {
            /*for (int i = 0; i < enemies->size(); i++)
            {
                int x = (*enemies)[i].getX();
                int y = (*enemies)[i].getY();
                if (x == e.sourisX && y == e.sourisY)
                {
                    killingEnemy = true;
                    indexEnemyToKill = i;
                    break;
                }
            }*/
            // if (!killingEnemy)
            //{
            moveToX = e.sourisX;
            moveToY = e.sourisY;
            // pathPersonage = findWay(e.sourisX, e.sourisY);
            pathPersonage = findWayA(m_x, m_y, e.sourisX, e.sourisY, terre, false);
            movePersonnage = true;
            // move(e.sourisX, e.sourisY, path, chron);
            // indexPath = 0;
            chosen = false;
        }
    }

    if (movePersonnage)
    {
        if (cacheDansMaison)
        {
            cacheDansMaison = false;
            cout << "I dont hide anymore" << endl;
        }
        // cout << "vasy" << endl;
        if (indexPathPersonage >= pathPersonage.size())

        {
            // cout << indexPathPersonage << " index" << endl;
            if (!enemy)
                movePersonnage = false;
            indexPathPersonage = 0;
            int type = grid[m_x][m_y].getType();

            if ((type == 2) && !(busyCutingTree))
            {
                busyCutingTree = true;
                chronCut.defineInterval(3000);
                // cout << "Je coupe " << busyCuting << endl;
            }

            else if ((type == 3) && !(busyCutingMais))
            {
                busyCutingMais = true;
                chronCut.defineInterval(3000);
                // cout << "Je coupe " << busyCuting << endl;
            }
        }
        if (chron.hasElapsed())
        {
            // cout << indexPathPersonage << " index" << endl;
            if (indexPathPersonage < pathPersonage.size())
            {
                Pair pair = pathPersonage[indexPathPersonage];

                // if (!enemy)
                // terre->clearOccupyByPersonage(m_x, m_y);

                moveOneSquare(pair.first, pair.second);
                if (enemy)
                    cout << pair.first << " " << pair.second << " enemy moved" << endl;
                // if (!enemy)
                // terre->occupyPersonnage(pair.first, pair.second);

                indexPathPersonage++;
            }

            // cout << indexPathPersonage << endl;
            //  chron.defineInterval(5);
        }
    }
}

void Personage::killPersonage(Personage *closestPersonage)
{
    int dx = closestPersonage->getX() - m_x;
    int dy = closestPersonage->getY() - m_y;

    if (abs(dx) < 1 && abs(dy) < 1)
    {
        closestPersonage->enemyAlive = false;
    }
    /*
    else if (abs(dx) > abs(dy))
    {
        int newX;
        if (dx > 0)
        {
            newX = m_x + 1; // Move right
        }
        else
        {
            newX = m_x - 1; // Move left
        }
        if (chron.hasElapsed())
            moveOneSquare(newX, m_y);
    }
    else
    {
        int newY;
        if (dy > 0)
        {
            newY = m_y + 1; // Move right
        }
        else
        {
            newY = m_y - 1; // Move left
        }
        if (chron.hasElapsed())
            moveOneSquare(m_x, newY);
    }*/
}

vector<Pair> Personage::findWayA(int xStart, int yStart, int xFin, int yFin, const Terrain *terrain, bool enemy)
{
    vector<Pair> path;
    int currX = xStart, currY = yStart;
    vector<Pair> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

    // open list nodes a exploresr
    // closed list nodes deja explore
    priority_queue<Node *, vector<Node *>, Node::CompareNodes> noeudsAexplorer; // a explorer
    map<Pair, Node *> allNodes;                                                 // tout les noeuds cree
    set<Pair> noeudsDejaExplores;                                               // noeuds deja explorer

    Node *startNode = new Node(currX, currY, 0, Node::calculerHeuristic(currX, currY, xFin, yFin));
    noeudsAexplorer.push(startNode);
    allNodes[make_pair(xStart, yStart)] = startNode;

    while (!noeudsAexplorer.empty())
    {
        Node *current = noeudsAexplorer.top();
        noeudsAexplorer.pop();

        if (current->x == xFin && current->y == yFin)
        {

            while (current != nullptr)
            {
                path.push_back(make_pair(current->x, current->y)); // on rempli le chemin avec tout les noeuds trouvé
                current = current->parent;
            }

            reverse(path.begin(), path.end()); // inverser ordre de liste
            return path;
        }

        noeudsDejaExplores.insert({current->x, current->y});

        for (auto &dir : directions)
        {
            int newX = current->x + dir.first;
            int newY = current->y + dir.second;

            if (newX < 0 || newY < 0 || newX >= terrain->getDimX() || newY >= terrain->getDimY())
                continue;

            bool isGoal = (newX == xFin && newY == yFin);

            if (!isGoal && terrain->getCase_FromTerrainConst(newX, newY)->isOccupied())
                continue;

            if (isGoal && enemy && terrain->getCase_FromTerrainConst(newX, newY)->isOccupied())
                continue;

            if (terrain->getCase_FromTerrainConst(newX, newY)->occupiedByPersonage())
                continue;

            if (terrain->getCase_FromTerrainConst(newX, newY)->isOcean())
                continue;

            if (!isGoal && !terrain->isTerre(newX, newY))
                continue;

            // vérifier si il est pas déjà exploré
            if (noeudsDejaExplores.find({newX, newY}) != noeudsDejaExplores.end())
                continue;

            // nouvel distanceFromStart est le distanceFromStart de mon noeud actuel
            int newG = current->distanceFromStart;

            if (dir.first == 0 || dir.second == 0)
            {
                newG += 10;
            }

            else
            {
                newG += 14;
            }

            int newH = Node::calculerHeuristic(newX, newY, xFin, yFin);
            // allNodes.count({newX, newY}) - 1 si on a deja cree cette noeud et si la distance de le debut de chemin est plus petit
            if (allNodes.count({newX, newY}) && allNodes[{newX, newY}]->distanceFromStart <= newG)
                continue;
            // voisin est noeud a cote, avec current comme parent
            Node *neighbor = new Node(newX, newY, newG, newH, current);
            noeudsAexplorer.push(neighbor);
            allNodes[{newX, newY}] = neighbor;
        }
    }

    // No path found
    return {};
}