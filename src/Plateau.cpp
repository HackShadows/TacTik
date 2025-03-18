/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;


Plateau::Plateau(int nbJ){
    cases = new Pion[16*nbJoueurs];
}

Plateau::~Plateau() {
    delete [] cases;
}