
#include "Carte.h"

using namespace std;


Carte::Carte(){
    valeur = 0;
    image = "data/imagedefaut.png";
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