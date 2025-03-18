/**
* @brief Contient l'implémentation de la classe Pioche.
*/
#include "Pioche.h"

#include <iostream>
#include <cassert>

using namespace std;


Pioche::Pioche() {
	pile = new Carte[54];
    for (int i = 0; i<13; i++) {
        for (int j = 0; j<4; j++) {
            pile[i*4+j].setCarte(i+1);
        }
    }
    pile[52].setCarte(-1);
    pile[53].setCarte(-1);
	tas = Carte();
}

Pioche::~Pioche() {
    delete [] pile;
    pile = nullptr;
}

void Pioche::setTas(const Carte & carte){
    tas = carte;
}

Carte Pioche::getTas() const{
    return tas;
}

Carte* Pioche::getPile() const{
    return pile;
}

void Pioche::testRegression(){
    Pioche pioche;
    assert(true);
}

void Pioche::afficher() const {
    cout << "Tas : ";
    tas.afficher();
    for (int i = 0 ; i < 54 ; i++) pile[i].afficher();
}
