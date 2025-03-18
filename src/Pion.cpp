/**
* @brief Contient l'implémentation de la classe Pion.
*/
#include "Pion.h"

#include <iostream>
#include <cassert>

using namespace std;


Pion::Pion(): pieu(true), id(0), couleur(0){}

void Pion::setPion(int identifiant) {
    id = identifiant;
    couleur = (id/4)+1;
}

Pion::~Pion() {
    pieu = true;
    id = 0;
    couleur = 0;
}

int Pion::getId() {
    return id;
}

void Pion::testRegression(){
    
}

void Pion::afficher() const {
    cout << "Id : " << id << " ; Couleur : " << couleur << " ; C'est un " << ((pieu) ? "pieu":"pion") << endl;
}