#include <iostream>
#include "Personage.h"
#include "Terrain.h"
#include <cmath>
#include "Game.h"
#include <vector>
#include <queue>
#include <map>
#include <set>
#include "Events.h"
#include "Tsunami.h"
#include <time.h>
#include <ctime>

using namespace std;
typedef pair<int, int> Pair;

Game::Game(unsigned int terrainWidth, unsigned int terrainHeight, unsigned int tS)
    : terrain(terrainWidth, terrainHeight), tsunami(terrainWidth - 1, terrainHeight - 1)
{
    cout << "Game initialized with terrain size: " << terrainWidth << "x" << terrainHeight << endl;
    tailleSprite = tS;
    tailleX = terrainWidth;
    tailleY = terrainHeight;
    personages = vector<Personage>();
    Personage p = Personage(10, 13);
    personages.push_back(p);
    clocks = clock();
    chronTsunami.defineInterval(180000);
    chronAttackEnemies.defineInterval(240000);
    chronDureeAttack.defineInterval(260000);
    chronDureeTsunami.defineInterval(187000);
}

void Game::addPersonage(const Personage &p)
{
    personages.push_back(p);
    terrain.minusMais();
}

void Game::addMaison(Maison m)
{
    cout << "maison added" << endl;
    maisons.push_back(m);
    // maisons.push_back(m);
}
const vector<Maison> *Game::getMaison() const
{
    return &maisons;
}
Personage *Game::getPersonage(unsigned int posPersonage)
{
    return &personages.at(posPersonage);
}

Personage *Game::getPersonage(int xPos, int yPos)
{

    Personage p;
    int x, y;
    for (unsigned int i = 0; i < personages.size(); ++i)
    {
        x = personages[i].getX();
        y = personages[i].getY();
        if (x == xPos && y == yPos)
        {
            return &personages.at(i);
        }
    }
}

Personage *Game::getEnemies(unsigned int posEnemies)
{
    return &enemies.at(posEnemies);
}

vector<Personage> *Game::getEnemies()
{
    return &enemies;
}

Personage *Game::getEnemi(int xPos, int yPos)
{
    Personage p;
    int x, y;
    for (unsigned int i = 0; i < enemies.size(); ++i)
    {
        x = enemies[i].getX();
        y = enemies[i].getY();
        if (x == xPos && y == yPos)
        {
            return &enemies.at(i);
        }
    }
}

unsigned int Game::quantiteEnemis()
{
    return enemies.size();
}

Terrain *Game::getTerrain()
{
    return &terrain;
}

Tsunami *Game::getTsunami()
{
    return &tsunami;
}

bool Game::retrouverMaison(int x, int y)
{
    Terrain *t = getTerrain();
    Case definer = t->getCase_FromTerrain(x, y);
    if (definer.getType() == Case::Terre && definer.getOccupationType() == Case::Maison)
    {
        return !getMaisonDistructed(x,y);
    }
    return false;
}

void Game::update(Event &e)
{
    if (personages.size() >= 10)
    {
        victory = true;
        e.victoir = true;
    }

    if (personages.size() == 0)
    {
        e.perdre = true;
    }
    terrain.updateTerrain(e, getPersonages());
    tsunami.update();

    // BOUGER PERSONAGE
    for (unsigned int i = 0; i < personages.size(); ++i)
    {
        int posX, posY;
        posX = personages[i].getX();
        posY = personages[i].getY();
        if (posX == tsunami.getX() && !personages[i].getcacheDansMaison())
            personages.erase(personages.begin() + i);
        personages[i].updatePersonage(e, getMaison(), getTerrain());
    }

    // ACTION DES TOUCHES
    if (e.clavierClique)
    {
        switch (e.derniereTouche)
        {
        case 'm':
            // OPEN MENU
            e.homeInConstruction = false;
            e.menuOpen = !e.menuOpen;
            e.homeInConstruction = false;
            break;
        default:
            break;
        }
    }

    // ACTIONS AVEC CLIQUE SURIS
    if (e.sourisClique)
    {

        // VERIFICATION SI ON CLIQUE SUR LA MAISON
        if (e.homeMenuIsOpen == false)
        {
            e.homeMenuIsOpen = retrouverMaison(e.sourisX, e.sourisY);
        }
    }

    // CREE PERSONAGE
    if (e.personageInCreation)
    {
        cout << "personage is in creation" << endl;
        if (e.sourisClique)
        {

            e.homeMenuIsOpen = false;
            Personage p1(e.sourisX, e.sourisY);

            if (terrain.getMais() >= 30)
            {
                addPersonage(p1);
                terrain.occupyPersonnage(e.sourisX, e.sourisY);
            }
            else
            {
                e.errMais = true;
            }
            // terrain.minusMais();
            e.personageInCreation = false;
            e.sourisClique = false;
            e.sourisX = NULL;
            e.sourisY = NULL;
            cout << "pers cr";
        }
    }

    // CONSTRUIR MAISON
    if (e.homeInConstruction)
    {
        if (e.sourisClique)
        {
            if (e.sourisX != NULL && e.sourisY != NULL)
            {
                // Terrain *t = getTerrain();
                terrain.buildHouse_onTerrain(e.sourisX, e.sourisY, e);
                //  terrain.raiseMais_onTerrain(e.sourisX, e.sourisY); ya vstavila ce tut bo poki nema okremoho menu dlya raiseMais
                if (!e.caseMaisonNonValid && !e.errBois)
                {
                    Maison m(e.sourisX, e.sourisY);
                    addMaison(m);
                }
                e.homeInConstruction = false;
                e.sourisClique = false;
                e.sourisX = NULL;
                e.sourisY = NULL;
                // t = nullptr;
            }
        }
    }

    // ACTION POUR LE MENU
    if (e.menuOpen)
    {
        e.homeMenuIsOpen = false;

        if ((e.propreX >= tailleX * 4 / 5 * tailleSprite && e.propreX <= (tailleX * 4 / 5 * tailleSprite + tailleSprite + 120)) && (e.propreY >= tailleSprite && e.propreY <= tailleSprite * 2))
        {
            e.homeInConstruction = true;
            e.menuOpen = false;
        }
        e.sourisClique = false;
        e.sourisX = NULL;
        e.sourisY = NULL;
    }

    // ACTION POUR LE MENU MAISON
    if (e.homeMenuIsOpen)
    {
        e.menuOpen = false;
        if ((e.propreX >= tailleX * 4 / 5 * tailleSprite && e.propreX <= (tailleX * 4 / 5 * tailleSprite + tailleSprite + 120)) && (e.propreY >= tailleSprite && e.propreY <= tailleSprite * 2))
        {
            e.personageInCreation = true;
            e.homeMenuIsOpen = false;
        }

        e.sourisClique = false;
        e.sourisX = NULL;
        e.sourisY = NULL;
    }

    if (chronTsunami.hasElapsed())
    // if ((int)((clock() - clocks) / 1000) == 10)
    {
        cout << "tsunami!!!!" << endl;
        clocks = clock();
        e.incident = true;
        tsunami.activate();

        for (int i = 0; i < maisons.size(); i++)
        {
            maisons[i].damage(50);
        }

        /*vector<int> died = tsunami.checkCollision(getPersonages());

         for (int i = died.size() - 1; i >= 0; --i)
         {
             cout << "Perso " << died[i] << endl;
             int index = died[i];
             if (index >= 0 && index < personages.size() && !personages[i].getcacheDansMaison())
             {
                 personages.erase(personages.begin() + index); // Safely remove personage at index
             }
         }*/
        // cout << "sfsefseffffffffffffffffffffffffffffffffffffff" << endl;
    }
    // cout << "sfsefseffffffffffffffffffffffffffffffffffffff" << endl;
    //}
    // if (chronDureeTsunami.hasElapsed())
    // cout << "sfsefseffffffffffffffffffffffffffffffffffffff" << endl;

    if (chronDureeTsunami.hasElapsed())
    // if ((int)((clock() - clocks) / 1000) == 30)
    {
        e.incident = false;
        tsunami.disactivate();
    }

    if (chronAttackEnemies.hasElapsed())
    {
        if (enemies.empty())
        {
            createEnemies(10);
            for (auto &enemy : enemies)
            {
                enemy.chron.defineInterval(1000);
            }

            attack = true;
        }
    }
    if (chronDureeAttack.hasElapsed())
    {
        enemies.clear();
        attack = false;
    }
    if (attack)
    {
        attackEnemies();
        for (auto &enemy : enemies)
        {
            // cout << "enemy is updating";
            enemy.updatePersonage(e, getMaison(), getTerrain());
            // cout << enemy.movePersonnage << "he is moving" << endl;
        }
    }
}

// e.incident = false;
// tsunami.disactivate();

unsigned int Game::getXTerrain()
{
    return terrain.getDimX();
}

unsigned int Game::getYTerrain()
{
    return terrain.getDimY();
}

unsigned int Game::quantitePersonages()
{
    return personages.size();
}

int Game::getTime()
{
    return (int)((clock() - clocks) / 1000);
}

void Game::createEnemies(int numEnemies)
{

    set<Pair> uniquePairs;
    srand(time(0));

    while (uniquePairs.size() < numEnemies)
    {
        if (rand() % 2)
        { // Randomly choose between (0, y) or (x, 0)
            uniquePairs.insert({0, 1 + rand() % (tailleY - 1)});
        }
        else
        {
            uniquePairs.insert({1 + rand() % (tailleX - 1), 0});
        }
    }
    for (const auto &p : uniquePairs)
    {
        cout << "enemie cree " << p.first << " " << p.second << endl;
        Personage perso(p.first, p.second);
        perso.enemy = true;
        enemies.push_back(perso);
        terrain.occupyPersonnage(p.first, p.second);
    }
    for (auto &enemy : enemies)
    {
        enemy.chron.defineInterval(1000);
    }
}
// ЗНАЙТИ ТА ПРОВІРИТИ ДЕ ОЧИЩУЮТЬСЯ ДАННІ ПРО КОРДИНАТИ ВІД ЧАС БУДІВЛІ ДОМУ
void Game::attackEnemies()
{
    for (auto &enemy : enemies)
    {
        Personage *closestPersonage = nullptr;
        int minDistance = INT_MAX;

        for (auto &personage : personages)
        {
            if (personage.getcacheDansMaison())
            {
                continue;
            }
            int distance = abs(enemy.getX() - personage.getX()) + abs(enemy.getY() - personage.getY());

            if (distance < minDistance)
            {
                minDistance = distance;
                closestPersonage = &personage;
            }
        }

        if (closestPersonage && minDistance <= 1)
        {
            for (size_t i = 0; i < personages.size();)
            {
                if (personages[i].getX() == closestPersonage->getX() &&
                    personages[i].getY() == closestPersonage->getY() && !(personages[i].getcacheDansMaison()))
                {
                    personages.erase(personages.begin() + i);
                    break;
                }
                else
                {
                    i++;
                }
            }
        }
        else if (closestPersonage)
        {
            // cout << closestPersonage->getX() << " " << closestPersonage->getY() << "est chassé " << endl;
            enemy.pathPersonage = Personage::findWayA(enemy.getX(), enemy.getY(), closestPersonage->getX(), closestPersonage->getY(), getTerrain(), true);
            enemy.movePersonnage = true;

            // enemy.movePersonnage(closestPersonage->getX(), closestPersonage->getY());
            //  enemy.killPersonage(closestPersonage);
        }
    }
}

bool Game::getMaisonDistructed(unsigned int x, unsigned int y)
{
    for (int i = 0; i < maisons.size(); i++)
    {
        if (maisons[i].getMX() == x && maisons[i].getMY() == y)
        {
            return maisons[i].getDistroyed();
        }
        else if (maisons[i].getMX() == x - 1 && maisons[i].getMY() == y)
        {
            return maisons[i].getDistroyed();
        }
        else if (maisons[i].getMX() == x && maisons[i].getMY() == y - 1)
        {
            return maisons[i].getDistroyed();
        }
        else if (maisons[i].getMX() == x - 1 && maisons[i].getMY() == y - 1)
        {
            return maisons[i].getDistroyed();
        }
    }
    return false;
}