/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cassert>

using namespace std;


Plateau::Plateau(){
    nbCases = 16*4;
    cases = new Pion*[nbCases];
}

Plateau::Plateau(int nbJ){
    nbCases = 16*nbJ;
    cases = new Pion*[nbCases];
}

Plateau::~Plateau() {
    for (int i = 0; i<nbCases; i++) {
        delete cases[i];
    }
}

int Plateau::getNbCase() {
    return nbCases;
}

Pion& Plateau::getPion(int indice) {
    return *cases[indice];
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

    Pion pion;
    pion = plateau.getPion(0);
    assert(pion.getId() == plateau.cases[0]->getId());
    cout << "getPion valide !" << endl;

    /*cout << "Méthode affichage : " << endl;
    plateau.afficher();
    cout << "afficher valide !" << endl;

    plateau.~Plateau();
    plateau6.~Plateau();
    cout << "Destructeur valide !" << endl;*/


}

void Plateau::afficher() const {
    cout << "Nombre de cases : " << nbCases << endl;
}