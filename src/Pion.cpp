/**
* @brief Contient l'implémentation de la classe Pion.
*/
#include "Pion.h"
#include <iostream>

using namespace std;


Pion::Pion(){
    pieu = true;
    image = "data/pion.png";
    id = 0;
    couleur = 0;
}

void Pion::setPion(int identifiant){
    id = identifiant;
    couleur = (id/4) + 1;
}