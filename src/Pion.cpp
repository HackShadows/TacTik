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
    Pion pion;
    assert(pion.pieu);
    assert(pion.id == 0);
    assert(pion.couleur == 0);
    pion.setPion(4);
    assert(pion.id == 4);
    assert(pion.getId()==4);
    pion.afficher();
}

void Pion::afficher() const {
    cout << "Id : " << id << " ; Couleur : " << couleur << " ; C'est un " << ((pieu) ? "pieu":"pion") << endl;
}