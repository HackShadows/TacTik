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

void Joueur::setJoueur(string nom, int id_couleur){
    pseudo = nom;
    couleur = id_couleur;
}


const Carte& Joueur::jouerCarte(int valeur) {
    for (int i = 0; i<4; i++){
        if (main[i].estDansMain() && valeur == main[i].getValeur()){
            main[i].setJouee(false);
            return main[i];
        }
    }
    return {};
}

bool Joueur::maisonRemplie() const{
    for (int i = 0; i<4; i++){
        if (!maison[i]){
            return false;
        }
    }
    return true;
}


void Joueur::piocherCarte(const Carte & carte){

}