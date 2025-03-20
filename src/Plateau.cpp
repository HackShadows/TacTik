/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cassert>

using namespace std;


Plateau::Plateau(){
    nbCases = 16*4;
    for (int i = 0; i<16*4; i++) {
        cases[i] = nullptr;
    }
}

Plateau::Plateau(int nbJ){
    nbCases = 16*nbJ;
    cases = new Pion*[nbCases];
}

Plateau::~Plateau() {
    for (int i = 0; i<nbCases; i++) {
        delete cases[i];
    }
    delete [] cases;
    cases = nullptr;
    nbCases = 0;
}

int Plateau::getNbCase() {
    return nbCases;
}

Pion& Plateau::getPion(int indice) {
    assert(cases[indice] != nullptr);
    return *cases[indice];
}

void Plateau::setPion(Pion* pion, int indice) {
    cases[indice] = pion;
}

void Plateau::viderCase(int indice) {
    cases[indice] = nullptr;
}


void Plateau::testRegression(){
    Plateau plateau;
    assert(plateau.nbCases == 64);
    cout << "Constructeur par défaut valide !" << endl;

    Plateau plateau6(6);
    assert(plateau6.nbCases == 96);
    cout << "Constructeur avec paramètre valide !" << endl;

    assert(plateau.getNbCase() == 64);
    assert(plateau6.getNbCase() == 96);
    cout << "getNbCase valide !" << endl;

    Pion* pion = new Pion();
    plateau.setPion(pion, 0);
    assert(plateau.cases[0]->getId() == pion->getId());
    cout << "setPion valide !" << endl;

    plateau.viderCase(0);
    assert(plateau.cases[0] == nullptr);
    cout << "viderCase valide !" << endl;

    *pion = plateau.getPion(0);
    assert(pion->getId() == plateau.cases[0]->getId());
    cout << "getPion valide !" << endl;

    /*cout << "Méthode affichage : " << endl;
    plateau.afficher();
    cout << "afficher valide !" << endl;*/

    plateau.~Plateau();
    plateau6.~Plateau();
    assert(plateau.cases == nullptr && plateau.getNbCase() == 0);
    assert(plateau6.cases == nullptr && plateau6.getNbCase() == 0);
    cout << "Destructeur valide !" << endl;


}

void Plateau::afficher() const {
    cout << "Nombre de cases : " << nbCases << endl;
}