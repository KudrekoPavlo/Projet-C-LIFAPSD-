#include <iostream>
#include "Maison.h"
#include "Personage.h"

using namespace std;

Maison::Maison(int x, int y)
{
    mx = x;
    my = y;
    cout << "Position " << x << " " << y;
    score = 100;
    max_people = 1;
    current_people = 0;
    destroyed = false;
}

Maison &Maison::getMaison()
{
    return *this;
}

int Maison::getMX() const
{

    return this->mx;
}
int Maison::getMY() const
{

    return this->my;
}

void Maison::personageEnter(unsigned int people)
{

    while (current_people < max_people && people > 0)
    {
        current_people++;
        people--;
    }
    cout << "there are " << current_people << " at home" << endl;
    if (people > 0)
    {
        cout << "There ere no more space " << people << " people must stay outside." << endl;
    }
}

void Maison::personageExit(unsigned int people)
{

    if (people >= current_people)
    {
        current_people = 0;
    }
    else
    {
        current_people -= people;
    }
    cout << "there are " << current_people << " people in the house" << endl;
}
bool Maison::isInside(int posX_personage, int posY_personage) const
{
    if ((mx == posX_personage && my == posY_personage) ||
        (mx + 1 == posX_personage && my == posY_personage) ||
        (mx == posX_personage && my + 1 == posY_personage) ||
        (mx + 1 == posX_personage && my + 1 == posY_personage))
    {
        cout << "Personage at (" << posX_personage << "," << posY_personage
             << ") is inside house at (" << mx << "," << my << ")" << endl;
        return true;
    }
    return false;
}

unsigned int Maison::damage(unsigned int damage)
{
    if (damage > score)
        score = 0;
    else
        score -= damage;

    cout << "score of the house " << score << endl;
    if(score<=0)
    {
        destroyed = true;
    }
    return score;
}

unsigned int Maison::getScore() const
{
    return this->score;
}

void Maison::addPersonage(unsigned int i)
{
    Person.push_back(i);
}

bool Maison::getDistroyed()
{
    return destroyed;
}