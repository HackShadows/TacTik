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
    cout<<"Constructeur par défaut validé"<<endl;

    pion.setPion(4);
    assert(pion.id == 4);
    cout<<"SetPion validé"<<endl;

    assert(pion.getId()==4);
    cout<<"getPion validé"<<endl;

    pion.afficher();
    cout<<"afficher validé "<<endl;

    pion.~Pion();
    assert(pion.pieu);
    assert(pion.id == 0);
    assert(pion.couleur == 0);
    cout<<"Destructeur validé"<<endl;
}

void Pion::afficher() const {
    cout << "Id : " << id << " ; Couleur : " << couleur << " ; C'est un " << ((pieu) ? "pieu":"pion") << endl;
}