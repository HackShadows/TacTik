/**
* @brief Contient l'implémentation de la classe Joueur.
*/
#include "Joueur.h"

#include <iostream>
#include <cassert>

using namespace std;


Joueur::Joueur(): pseudo("jean"), couleur(0){
    for (int i = 0; i<4; i++){
        main[i] = nullptr;
        maison[i] = false;
    }

}

Joueur::~Joueur() {
    for (int i = 0; i<4; i++){
        main[i] = nullptr;
    }
    delete [] main;
}

void Joueur::setJoueur(string nom, int id_couleur){
    assert(1 <= id_couleur && id_couleur <=6);
    pseudo = nom;
    couleur = id_couleur;
}

void Joueur::piocherCarte(int indice, Carte * carte){
    assert(main[indice] == nullptr);
    main[indice] = carte;
}

Carte* Joueur::jouerCarte(int valeur) {
    for (int i = 0; i<4; i++){
        Carte* carte = main[i];
        if (carte != nullptr && valeur == carte->getValeur()) {
            main[i] = nullptr;
            return carte;
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

void Joueur::testRegression(){
    Joueur joueur;
    assert(joueur.main == nullptr);
    for (int i = 0 ; i < 4 ; i++) assert(joueur.maison[i] == false);
    cout << "Constructeur valide !" << endl;

    joueur.setJoueur("Toto", 3);
    assert(joueur.pseudo == "Toto" && joueur.couleur == 3);
    cout << "setJoueur valide !" << endl;

    Carte carte_tmp;
    carte_tmp.setCarte(12);
    joueur.piocherCarte(3, &carte_tmp);
    assert(joueur.main[3]->getValeur() == 12);
    cout << "piocherCarte valide !" << endl;

    Carte * carte = joueur.jouerCarte(3);
    assert(carte->getValeur() == 12 && joueur.main[3] == nullptr);
    cout << "jouerCarte valide !" << endl;
}

void Joueur::afficher() const {
    cout << "Pseudo : " << pseudo << " ; Couleur : " << couleur << endl;
}