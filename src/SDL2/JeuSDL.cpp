#include <iostream>
#include "SDLJeu.h"
#include "../Terrain.h"
#include "../Personage.h"
#include "SDLSprite.h"
#include "../Case.h"
#include "../Game.h"

using namespace std;

const unsigned int LONGEUR = 30;
const unsigned int HAUTEUR = 15;
const unsigned int TAILLE_SPRITE = 50;

int main(int argc, char **argv)
{
    
    SDLJeu sj(LONGEUR, HAUTEUR, TAILLE_SPRITE);
    Game game(LONGEUR, HAUTEUR, TAILLE_SPRITE);
    sj.boucle(game);

    /*unsigned int sprite = 45;
   MySDLEvent e(sprite);
   Game game(35, 15);
  Personage per(15, 5);
   game.addPersonage(per);
   Terrain ter = *game.getTerrain();
   SDLJeu sj(ter, sprite);
   SDL_Renderer *renderer = sj.getRenderer();
   while (!e.fermeture())
   {
       sj.sdlAff(ter, per);
       SDL_Delay(16); // ~60 FPS
   }
*/
    return 0;
}