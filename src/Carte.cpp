/**
* @brief Contient l'implémentation de la classe Carte.
*/
#include "Carte.h"

using namespace std;


Carte::Carte(){
    valeur = 0;
    jouee = false;
}

void Carte::setCarte(int val, string chemin){
    valeur = val;
    image = chemin;
}

int Carte::getValeur()const{
    return valeur;
}

string Carte::getImage() const{
    return image;
}

bool Carte::estDansMain() const {
    return jouee;
}

void Carte::setJouee(bool valeur){
    jouee = valeur;
}