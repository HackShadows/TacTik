/**
* @brief Contient l'implémentation de la classe Joueur.
*/
#include "Joueur.h"

using namespace std;

Joueur::Joueur(){
    pseudo = "Jean";
    couleur = 0;
    main = nullptr;
    for (int i = 0; i<4; i++){
        maison[i] = false;
    }

}

void Joueur::setJoueur(string nom, int coul){
    pseudo = nom;
    couleur = coul;
}


const Carte& Joueur::jouerCarte(int valeur) {
    for (int i = 0; i<4; i++){
        if (main[i].estJouable() && valeur == main[i].getValeur()){
            main[i].setJouable(false);
            return main[i];
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