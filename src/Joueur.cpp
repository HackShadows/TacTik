
#include "Joueur.h"
#include "Carte.h"

using namespace std;

Joueur::Joueur(string nom, int coul){
    pseudo = nom;
    couleur = coul;
    for (int i = 0; i<4; i++){
        maison[i] = false;
    }
}

const Carte* Joueur::jouerCarte(int valeur) {
    for (int i = 0; i<4; i++){
        if (valeur == main[i]->getValeur()){
            const Carte* temp = main[i];
            main[i] = nullptr;
            return temp;
        }
    }
}

bool Joueur::maisonRemplie() const{
    for (int i = 0; i<4; i++){
        if (!maison[i]){
            return false;
        }
    }
    return true;
}