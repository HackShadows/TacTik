
#include "Carte.h"

using namespace std;


Carte::Carte(int val, string chemin){
    valeur = val;
    image = chemin;
}

int Carte::getValeur()const{
    return valeur;
}

string Carte::getImage() const{
    return image;
}