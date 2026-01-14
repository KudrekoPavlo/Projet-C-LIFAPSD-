#include <iostream>
#include "Terrain.h"
#include "Personage.h"
#include "Case.h"
#include "Maison.h"
#include "Events.h"
#include "Chronolog.h"
#include <vector>
#include <math.h>
// #include "winTxt.h"
// #include "txtJeu.h"

#include <cassert> //for assert
#include <cstdlib> // For rand()
#include <ctime>   // For time()

typedef vector<Case> TabCase;

using namespace std;

Terrain::Terrain(unsigned int width, unsigned int height)
{
    wood = 0;
    mais = 0;
    dx = width;
    dy = height;

    houses.clear();

    grid.resize(width);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            grid[i].push_back(Case(i, j, Case::Ocean));
        }
    }
    srand(static_cast<unsigned int>(std::time(0)));

    int centerX = dx / 2;
    int centerY = dy / 2;

    double radiusX = dx / 1.5;
    double radiusY = dy / 2.0;

    for (int i = 0; i < dx; i++)
    {
        for (int j = 0; j < dy; j++)
        {
            double distX = (i - centerX) / radiusX;
            double distY = (j - centerY) / radiusY;
            double distance = sqrt(distX * distX + distY * distY);

            if (distance < (0.85 + 0.15 * ((rand() % 100) / 100.0)))
            {
                grid[i][j].initializeCase_Terre();
            }
        }
    }

    int totalTerreCells = 0;
    for (int i = 0; i < dx; i++)
    {
        for (int j = 0; j < dy; j++)
        {
            if (grid[i][j].getType() == Case::Terre)
                totalTerreCells++;
        }
    }

    int numForests = totalTerreCells * 0.3;
    int forestCount = 0;

    while (forestCount < numForests)
    {
        int x = rand() % dx;
        int y = rand() % dy;

        if (grid[x][y].getType() == Case::Terre)
        {
            grid[x][y].initializeCase_Foret();
            forestCount++;
        }
    }

    initialNB_Forest = forestCount;

    int numMais = totalTerreCells * 0.1;
    int maisCount = 0;

    while (maisCount < numMais)
    {
        int x = rand() % dx;
        int y = rand() % dy;

        if (grid[x][y].getType() == Case::Terre)
        {
            grid[x][y].initializeCase_Mais();
            maisCount++;
        }
    }

    initialNB_Mais = maisCount;
}

unsigned int Terrain::getDimX() const
{
    return dx;
}

unsigned int Terrain::getDimY() const
{
    return dy;
}

void Terrain::afficherTerrain() const
{

    int countO = 0, countF = 0, countT = 0;
    for (int i = 0; i < dy; ++i)
    {
        for (int j = 0; j < dx; ++j)
        {
            cout << grid[i][j].getType() << " ";
            if (grid[i][j].getType() == Case::Ocean)
                countO++;

            if (grid[i][j].getType() == Case::Foret)
                countF++;

            if (grid[i][j].getType() == Case::Terre)
                countT++;
        }

        cout << endl;
    }

    cout << "ocean " << countO << endl;
    cout << "foret " << countF << endl;
    cout << "terre " << countT << endl;

    cout << "wood " << wood << endl;
}

void Terrain::afficherTerrain_Occup() const
{

    int countO = 0, countF = 0, countT = 0;
    int countM = 0;
    for (int i = 0; i < dy; ++i)
    {
        for (int j = 0; j < dx; ++j)
        {
            cout << grid[i][j].getOccupationType() << " ";
            if (grid[i][j].getType() == Case::Ocean)
                countO++;

            if (grid[i][j].getType() == Case::Foret)
                countF++;

            if (grid[i][j].getType() == Case::Terre)
                countT++;

            if (grid[i][j].getOccupationType() == Case::Maison)
                countM++;
        }

        cout << endl;
    }

    cout << "wood " << wood << endl;

    // int nbHouses=countM/4;
    cout << "house " << getMaisonCount() << endl;
}

size_t Terrain::getMaisonCount() const
{
    return houses.size();
}

const vector<TabCase> &Terrain::getGrid() const
{
    return grid;
}

const vector<Maison> &Terrain::getHouses() const
{
    return houses;
}

const bool Terrain::isTerre(unsigned int x, unsigned int y) const
{

    if (grid[x][y].getType() == Case::Terre)
    {
        return true;
    }

    return false;
}

bool Terrain::isValidCase(unsigned int x, unsigned int y)
{
    return x >= 0 && x < grid.size() && y >= 0 && y < grid[0].size();
}

void Terrain::cutForest_onTerrain_newVersion(Event e)
{
    if (e.sourisClique)
    {
        if (isValidCase(e.sourisX, e.sourisY))
        {
            if (grid[e.sourisX][e.sourisY].cutForest())
            {
                wood += 5;
            }
        }
        cout << "wood after cut " << wood << endl;
    }
}

bool Terrain::radarHouse(Event &e, Personage p)
{
    int pX = p.getX();
    int pY = p.getY();

    if (e.homeInConstruction)
    {
        if (wood >= 15)
        {
            if (isValidCase(pX, pY) && isValidCase(pX + 1, pY) &&
                isValidCase(pX, pY + 1) && isValidCase(pX + 1, pY + 1))
            {
                if (not(grid[pX][pY].isOccupied()) &&
                    not(grid[pX + 1][pY].isOccupied()) &&
                    not(grid[pX][pY + 1].isOccupied()) &&
                    not(grid[pX + 1][pY + 1].isOccupied()))
                {
                    if (grid[pX][pY].getType() == Case::Terre &&
                        grid[pX + 1][pY].getType() == Case::Terre &&
                        grid[pX][pY + 1].getType() == Case::Terre &&
                        grid[pX + 1][pY + 1].getType() == Case::Terre)
                    {
                        return true;
                    }
                }
                else
                {
                    e.caseMaisonNonValid = true;
                }
            }
        }
        else
        {
            e.errBois = true;
        }
    }

    else
        return false;

    cout << "There are not enough wood or case is not valid" << endl;
}

void Terrain::cutForest_onTerrain(unsigned int x, unsigned int y)
{
    if (isValidCase(x, y))
    {
        if (grid[x][y].cutForest())
        {
            wood += 5;
        }
    }
    cout << "wood after cut " << wood << endl;
}

void Terrain::cutMais_onTerrain(unsigned int x, unsigned int y)
{
    if (isValidCase(x, y))
    {
        if (grid[x][y].cutMais())
        {
            mais += 15;
        }
    }
    cout << "mais after cut " << mais << endl;

    /*
    if (!isValidCase(x, y)) return;

    bool cut = false;


    if (isValidCase(x + 1, y) && isValidCase(x, y + 1) && isValidCase(x + 1, y + 1)) {
        if (grid[x][y].cutMais() &&
            grid[x + 1][y].cutMais() &&
            grid[x][y + 1].cutMais() &&
            grid[x + 1][y + 1].cutMais()) {
            cut = true;
        }
    }


    if (x >= 1 && isValidCase(x - 1, y) && isValidCase(x, y + 1) && isValidCase(x - 1, y + 1)) {
        if (grid[x][y].cutMais() &&
            grid[x - 1][y].cutMais() &&
            grid[x][y + 1].cutMais() &&
            grid[x - 1][y + 1].cutMais()) {
            cut = true;
        }
    }

    // Check bottom-left 2x2
    if (y >= 1 && isValidCase(x + 1, y) && isValidCase(x, y - 1) && isValidCase(x + 1, y - 1)) {
        if (grid[x][y].cutMais() &&
            grid[x + 1][y].cutMais() &&
            grid[x][y - 1].cutMais() &&
            grid[x + 1][y - 1].cutMais()) {
            cut = true;
        }
    }

    // Check bottom-right 2x2
    if (x >= 1 && y >= 1 && isValidCase(x - 1, y) && isValidCase(x, y - 1) && isValidCase(x - 1, y - 1)) {
        if (grid[x][y].cutMais() &&
            grid[x - 1][y].cutMais() &&
            grid[x][y - 1].cutMais() &&
            grid[x - 1][y - 1].cutMais()) {
            cut = true;
        }
    }

    if (cut) {
        mais += 15;
    }

    cout << "mais after cut " << mais << endl;*/
}

// ja tut pominiala
void Terrain::buildHouse_onTerrain(unsigned int x, unsigned int y, Event& ev)
{
    if (isValidCase(x, y) && isValidCase(x + 1, y) &&
        isValidCase(x, y + 1) && isValidCase(x + 1, y + 1))
    {
        if (not(grid[x][y].isOccupied()) &&
            not(grid[x + 1][y].isOccupied()) &&
            not(grid[x][y + 1].isOccupied()) &&
            not(grid[x + 1][y + 1].isOccupied()))
        {

            if (grid[x][y].getType() == Case::Terre &&
                grid[x + 1][y].getType() == Case::Terre &&
                grid[x][y + 1].getType() == Case::Terre &&
                grid[x + 1][y + 1].getType() == Case::Terre)
            {
                if(wood >= 15)
                {
                    grid[x][y].buildHouse();
                    grid[x + 1][y].buildHouse();
                    grid[x][y + 1].buildHouse();
                    grid[x + 1][y + 1].buildHouse();

                    wood -= 15;
                    cout << "wood after building " << wood << endl;
                    ev.errBois = false;
                    ev.caseMaisonNonValid = false;
                }else
                {
                    ev.errBois = true;
                }

                ev.caseMaisonNonValid = false;
                // Maison *newMaison = new Maison(x, y);
                // houses.push_back(*newMaison);
                //  return newMaison;
            }
            else
            {
                ev.caseMaisonNonValid = true;
                cout << "it is not a terre" << endl;
                // return nullptr;
            }
        }
        else
        {
            ev.caseMaisonNonValid = true;
            cout << "this case is already occupied" << endl;
            // return nullptr;
        }
    }
    cout << "case is not valid" << endl;
}
/*
void  Terrain::raiseMais_onTerrain(unsigned int x, unsigned int y){
    if (isValidCase(x, y) && isValidCase(x + 1, y) &&
        isValidCase(x, y + 1) && isValidCase(x + 1, y + 1))
    {
        if (not(grid[x][y].isOccupied()) &&
            not(grid[x + 1][y].isOccupied()) &&
            not(grid[x][y + 1].isOccupied()) &&
            not(grid[x + 1][y + 1].isOccupied()))
        {

            if (grid[x][y].getType() == Case::Terre &&
                grid[x + 1][y].getType() == Case::Terre &&
                grid[x][y + 1].getType() == Case::Terre &&
                grid[x + 1][y + 1].getType() == Case::Terre)
            {
                grid[x][y].raiseMais();
                grid[x + 1][y].raiseMais();
                grid[x][y + 1].raiseMais();
                grid[x + 1][y + 1].raiseMais();

            }
            else
            {
                cout << "it is not a terre" << endl;
                // return nullptr;
            }
        }
        else
        {
            cout << "this case is already occupied" << endl;
            // return nullptr;
        }
    }

    cout << "case is not valid" << endl;

}
*/

void Terrain::destroyHouse_onTerrain(const Maison &m)
{
    /* int x = m.getMX();
     int y = m.getMY();

     cout << "Trying to remove house at (" << x << ", " << y << ")" << endl;*/
    /* if (isValidCase(x, y) && isValidCase(x + 1, y) &&
        isValidCase(x, y + 1) && isValidCase(x + 1, y + 1) && m.getScore()==0) */

    /* if (grid[x][y].getOccupationType() == Case::Maison &&
         grid[x + 1][y].getOccupationType() == Case::Maison &&
         grid[x][y + 1].getOccupationType() == Case::Maison &&
         grid[x + 1][y + 1].getOccupationType() == Case::Maison)
     {

         grid[x][y].destroyHouse();
         grid[x + 1][y].destroyHouse();
         grid[x][y + 1].destroyHouse();
         grid[x + 1][y + 1].destroyHouse();

         for (auto check = houses.begin(); check != houses.end();)
         {
             cout << "Checking house at (" << check->getMX() << ", " << check->getMY() << ")" << endl;
             if (check->getMX() == x && check->getMY() == y)
             {

                 check = houses.erase(check); // Update iterator after deletion
                 cout << "Maison at (" << x << ", " << y << ") destroyed and removed from the vector." << endl;
                 return; // Exit the function after removal
             }
             else
             {
                 ++check; // Increment if not removed
             }
         }

         cout << "house is not found in the tableau." << endl;
     }
     else
         cout << "its not a house" << endl;

     cout << "Taille actuelle de houses: " << houses.size() << endl;*/
}

Case &Terrain::getCase_FromTerrain(unsigned int x, unsigned int y)
{
    return (grid[x][y].getCase());
}

const Case *Terrain::getCase_FromTerrainConst(unsigned int x, unsigned int y) const
{
    return (grid[x][y].getCaseConst());
}

unsigned int Terrain::countForet() const
{
    int countF = 0;
    for (int i = 0; i < dy; ++i)
    {
        for (int j = 0; j < dx; ++j)
        {

            if (grid[i][j].getType() == Case::Foret)
                countF++;
        }
    }
    return countF++;
}

unsigned int Terrain::countMais() const
{
    int countM = 0;
    for (int i = 0; i < dy; ++i)
    {
        for (int j = 0; j < dx; ++j)
        {

            if (grid[i][j].getType() == Case::Mais)
                countM++;
        }
    }
    return countM++;
}

void Terrain::updateForest_Mais()
{

    int terreWidth = dx * 0.8;
    int terreHeight = dy * 0.8;

    int startX = (dx - terreWidth) / 2;
    int startY = (dy - terreHeight) / 2;

    unsigned int currentNB_Forest = countForet();
    unsigned int currentNB_Mais = countMais();

    if (currentNB_Forest < (0.5 * initialNB_Forest))
    {

        while (currentNB_Forest < initialNB_Forest)
        {
            int x = startX + (rand() % terreWidth);
            int y = startY + (rand() % terreHeight);

            if (grid[x][y].getType() == Case::Terre && grid[x][y].getOccupationType() == Case::Aucun)
            {
                grid[x][y].initializeCase_Foret();
                currentNB_Forest++;
            }
        }
        cout << "forest was successfuly updated" << endl;
    }

    if (currentNB_Mais < (0.5 * initialNB_Mais))
    {

        while (currentNB_Mais < initialNB_Mais)
        {
            int x = startX + (rand() % terreWidth);
            int y = startY + (rand() % terreHeight);

            if (grid[x][y].getType() == Case::Terre && grid[x][y].getOccupationType() == Case::Aucun)
            {
                grid[x][y].initializeCase_Mais();
                currentNB_Mais++;
            }
        }
        cout << "mais was successfuly updated" << endl;
    }
}

const unsigned int Terrain::getWood()
{
    return wood;
}

const unsigned int Terrain::getMais()
{
    return mais;
}

void Terrain::updateTerrain(Event e, const vector<Personage> *personages)
{

    updateForest_Mais();
    for (unsigned int i = 0; i < (*personages).size(); ++i)
    {

        int posX, posY;
        Chronolog chron;
        posX = (*personages)[i].getX();
        posY = (*personages)[i].getY();
        // cout << "Personnage positionneé " << posX << " " << posY << endl;

        if ((grid[posX][posY].getType() == Case::Foret) && ((*personages)[i].movePersonnage == false))
        {
            // chron.defineInterval(20);
            cout << "I cut the tree" << endl;

            // if (chron.hasElapsed())
            cutForest_onTerrain(posX, posY);
        }

        if ((grid[posX][posY].getType() == Case::Mais) && ((*personages)[i].movePersonnage == false))
        {
            // chron.defineInterval(20);
            cout << "I cut the mais" << endl;
            // if (chron.hasElapsed())
            cutMais_onTerrain(posX, posY);
        }

        /*if ((grid[posX][posY].getOccupationType() == Case::Maison) && ((*personages)[i].movePersonnage == false) && ((*personages)[i].getcacheDansMaison() == false))
        {
            cout << "I hide" << endl;
            //(*personages)[i].setcacheDansMaison(true);
        }*/
    }
}

void Terrain::minusMais()
{

    mais -= 30;
}
/*switch (grid[y][x]) {
    case Ocean:
        // Handle Ocean case (e.g., leave as it is)
        break;
    case Terre:
        // Handle Terre case (e.g., change to Forest or something else)
        break;
    case Forest:
        // Handle Forest case
        break;
    default:
        // Handle any other unknown case
        break;
}
*/
void Terrain::occupyPersonnage(unsigned int x, unsigned int y)
{
    grid[x][y].occupyPersonnage();
}

void Terrain::clearOccupation(int x, int y)
{
    grid[x][y].clearOccupation();
}

void Terrain::clearOccupyByPersonage(int x, int y)
{
    grid[x][y].clearOccupyByPersonage();
}