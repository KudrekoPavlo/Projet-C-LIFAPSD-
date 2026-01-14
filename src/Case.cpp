#include <iostream>
#include "Case.h"
#include <vector>
#include "Maison.h"

#include <cassert> //for assert
#include <cstdlib> // For rand()
#include <ctime>   // For time()
using namespace std;

Case::Case()
{
    caseType = Ocean;
}

Case::Case(unsigned int x_given, unsigned int y_given, Case::Type_Case caseType_given)
{

    x = x_given;
    y = y_given;
    caseType = caseType_given;
    occupationType = Aucun;
}

Case &Case::getCase()
{
    return *this;
}

const Case *Case::getCaseConst() const
{
    return this;
}

void Case::initializeCase_Terre()
{

    caseType = Terre;
    occupationType = Aucun;
}
void Case::initializeCase_Ocean()
{

    caseType = Ocean;
    occupationType = Aucun;
}
void Case::initializeCase_Foret()
{

    caseType = Foret;
    occupationType = Aucun;
}

void Case::initializeCase_Mais()
{

    caseType = Mais;
    occupationType = Aucun;
}

Case::Type_Case Case::getType() const
{
    return caseType;
}

const bool Case::isOccupied() const
{
    if (occupationType == Aucun)
        return false;
    return true;
}

Case::Type_Occup Case::getOccupationType() const
{
    return occupationType;
}

bool Case::cutForest()
{
    if (caseType == Foret)
    {

        caseType = Terre;
        return true;
    }
    cout << "there is no tree" << endl;
    return false;
}

bool Case::cutMais()
{
    if (caseType == Mais)
    {

        caseType = Terre;
        return true;
    }
    cout << "there is no corn" << endl;
    return false;
}

bool Case::raiseMais()
{
    if (caseType == Terre)
    {

        caseType = Mais;
        return true;
    }
    cout << "there is no  terre" << endl;
    return false;
}

bool Case::buildHouse()
{
    if (caseType == Terre && occupationType == Aucun)
    {

        occupationType = Maison;
        return true;
    }
    cout << "it's not a terre" << endl;
    return false;
}

bool Case::destroyHouse()
{
    if (occupationType == Maison)
    {

        occupationType = Aucun;
        return true;
    }
    cout << "it's not a house" << endl;
    return false;
}

const bool Case::isOcean() const
{
    return (caseType == 1);
}
void Case::occupyPersonnage()
{
    occupationPersonage = true;
}

void Case::clearOccupyByPersonage()
{
    occupationPersonage = false;
}

void Case::clearOccupation()
{
    occupationType = Aucun;
}

bool Case::occupiedByPersonage() const
{
    return occupationPersonage;
}
