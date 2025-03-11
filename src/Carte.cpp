/**
* @brief Contient l'implémentation de la classe Carte.
*/
#include "Carte.h"

using namespace std;


Carte::Carte(){
    valeur = 0;
    image = "data/imagedefaut.png";
    jouable = true;
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

bool Carte::estJouable() const {
    return jouable;
}

void Carte::setJouable(bool valeur){
    jouable = valeur;
}