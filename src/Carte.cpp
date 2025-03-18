/**
* @brief Contient l'implémentation de la classe Carte.
*/
#include "Carte.h"

using namespace std;


Carte::Carte(){
    valeur = 0;
    jouee = false;
}

void Carte::setCarte(int val){
    valeur = val;
}

int Carte::getValeur()const{
    return valeur;
}

bool Carte::estDansMain() const {
    return jouee;
}

void Carte::setJouee(bool valeur){
    jouee = valeur;
}