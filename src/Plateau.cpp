/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;


Plateau::Plateau(int nbJ){
    assert(nbJ == 4 || nbJ == 6);
    nbJoueurs = nbJ;
    joueurs = new Joueur[nbJoueurs];
    cases = new Pion[16*nbJoueurs];
    image = "data/image.jpg";
    pioche = Pioche();
}

void Plateau::distribuer(){
    int i = 0; 
    while (i<4*nbJoueurs){
        r = rand()%54;
        joueurs[i/4].
    }
}