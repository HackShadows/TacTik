/**
* @brief Contient l'implémentation de la classe Carte.
*/
#include "Carte.h"

#include <iostream>
#include <cassert>

using namespace std;


Carte::Carte(): jouee(false), valeur(0){}

Carte::~Carte() {
    valeur = 0;
    jouee = false;
}

void Carte::setCarte(int val){
    assert(-1 <= val && val <= 13);
    valeur = val;
}

int Carte::getValeur() const {
    return valeur;
}

bool Carte::estDansMain() const {
    return jouee;
}

void Carte::setJouee(bool valeur){
    jouee = valeur;
}

void Carte::testRegression(){
    Carte carte;
    assert(carte.jouee == false && carte.valeur == 0);
    cout << "Constructeur valide !" << endl;

    carte.setCarte(3);
    assert(carte.valeur == 3);
    cout << "setCarte valide !" << endl;

    int val = carte.getValeur();
    assert(val == 3);
    cout << "getCarte valide !" << endl;

    carte.setJouee(true);
    assert(carte.jouee == true);
    cout << "setJouee valide !" << endl;

    bool val2 = carte.estDansMain();
    assert(val2 == true);
    cout << "estDansMain valide !" << endl;

    carte.~Carte();
    assert(carte.jouee == false && carte.valeur == 0);
    cout << "Destructeur valide !" << endl;
}

void Carte::afficher() const {
    cout << "Valeur : " << valeur << " ; Jouee : " << jouee << endl;
}