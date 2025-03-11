/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cassert>

using namespace std;


Plateau::Plateau(int nbJoueurs){
    assert(nbJoueurs == 4 || nbJoueurs == 6);
    joueurs = new Joueur[nbJoueurs];
    cases = new Pion[16*nbJoueurs];
    image = "data/image.jpg";
    pioche = Pioche();
}


