/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cstdlib>
#include <cassert>

using namespace std;


Plateau::Plateau(){
    nbCases = 16*4;
    cases = new Pion[nbCases];
}

Plateau::Plateau(int nbJ){
    nbCases = 16*nbJ;
    cases = new Pion[nbCases];
}

Plateau::~Plateau() {
    delete [] cases;
}

int Plateau::getNbCase() {
    return nbCases;
}

Pion& Plateau::getPion(int indice) {
    return cases[indice];
}

void Plateau::testRegression(){
    
}

void Plateau::afficher() const {
    cout << "Nombre de cases : " << nbCases << endl;
}