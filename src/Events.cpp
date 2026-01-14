#include <iostream>
#include "Events.h"

using namespace std;

Event::Event()
{
    fermer = false;
    sourisClique = false;
    clavierClique = false;
    menuOpen = false;
    homeInConstruction = false;
    homeMenuIsOpen = false;
    personageInCreation = false;
    incident = false;
    victoir = false;
    perdre = false;
    caseMaisonNonValid = false;
    errBois = false;
    errMais = false;

    derniereTouche = 0;
    sourisX = 0;
    sourisY = 0;
    propreX = 0;
    propreY = 0;
}

void Event::renouveller()
{
    fermer = false;
    sourisClique = false;
    clavierClique = false;
    menuOpen = false;
    homeInConstruction = false;
    homeMenuIsOpen = false;
    personageInCreation = false;
    caseMaisonNonValid = false;
    errBois = false;
    errMais = false;
    derniereTouche = 0;
    sourisX = 0;
    sourisY = 0;
    propreX = 0;
    propreY = 0;  

}

void Event::destructionEventPourBoucle()
{
    derniereTouche = NULL;
    clavierClique = false;
    sourisClique = false;
    incident = false;
    sourisY = NULL;
    sourisY = NULL;

}

