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
    for (int i = 0; i<nbJoueurs; i++){
        for (int j = 0; j<4; j++){
            int r = rand()%54;
            joueurs[i/4].piocherCarte(pioche.getPile()[r])
        }
    }
}