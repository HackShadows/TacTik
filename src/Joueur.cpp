/**
* @brief Contient l'implémentation de la classe Joueur.
*/
#include "Joueur.h"

#include <iostream>
#include <cassert>

using namespace std;


Joueur::Joueur(): pseudo("jean"), couleur(0){
    main = nullptr;
    for (int i = 0; i<4; i++){
        maison[i] = false;
    }

}

Joueur::~Joueur() {
    if (main!=nullptr) {
        delete [] main;
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
    __builtin_unreachable();
}

void Joueur::piocherCarte(const Carte & carte){

}

bool Joueur::maisonRemplie() const{
    for (int i = 0; i<4; i++){
        if (!maison[i]){
            return false;
        }
    }
    return true;
}

void Joueur::testRegression(){
    
}

void Joueur::afficher() const {
    cout << "Pseudo : " << pseudo << " ; Couleur : " << couleur << endl;
}