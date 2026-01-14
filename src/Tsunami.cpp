#include <iostream>
#include "Terrain.h"
#include "Personage.h"
#include "Case.h"
#include "Maison.h"
#include "Tsunami.h"
#include "Events.h"
#include <vector>
#include <math.h>
// #include "winTxt.h"
// #include "txtJeu.h"


using namespace std;

    Tsunami::Tsunami(){
    x = 0;
    y = 0;
   // height = 10;
    active = false;

    }


Tsunami::Tsunami(unsigned int startX, unsigned int startY) {
    x = startX;
    y = startY;
   // height = givedHeight;
    active = false;
}

int Tsunami::getX() const {
    return x;
}

int Tsunami::getY() const {
    return y;
}

void Tsunami::update() {
    if (active) {
        x--;
        cout<<"Tsunami "<<x<<endl;  // Move left
        if (x < -6) { // assuming the tsunami image spans up to 6 sprite widths
            active = false; // it's off screen now
        }
    }
}


bool Tsunami::isActive() const {
        return active;
    }

    void Tsunami:: activate()
    {

        this->active = true;


    }

    void Tsunami:: disactivate()
    {


        this->active = false;

    }

vector<int> Tsunami::checkCollision(const vector<Personage>* personages) {
    vector<int> died;
    int tsunamiX = this->x; 

    for (int i = 0; i < personages->size(); i++) {
        int px = personages->at(i).getX();
        
        if (px == tsunamiX) {
            died.push_back(i);
        }
    }

    return died;
}
