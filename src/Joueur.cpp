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
    assert(1 <= id_couleur && id_couleur <=6);
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
    Joueur joueur;
    assert(joueur.main == nullptr);
    for (int i = 0 ; i < 4 ; i++) assert(joueur.maison[i] == false);
    cout << "Constructeur valide !" << endl;

    joueur.setJoueur("Toto", 3);
    assert(joueur.pseudo == "Toto" && joueur.couleur == 3);
    cout << "setJoueur valide !" << endl;
}

void Joueur::afficher() const {
    cout << "Pseudo : " << pseudo << " ; Couleur : " << couleur << endl;
}