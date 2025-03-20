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

    const Carte * carte = joueur.jouerCarte(3);
    assert(carte->getValeur() == 3);
    cout << "setCarte valide !" << endl;

    /*
    int val = carte.getValeur();
    assert(val == 3);
    cout << "getCarte valide !" << endl;

    carte.setJouee(true);
    assert(carte.jouee == true);
    cout << "setJouee valide !" << endl;

    bool val2 = carte.estDansMain();
    assert(val2 == true);
    cout << "estDansMain valide !" << endl;

    cout << "Méthode affichage : " << endl;
    carte.afficher();
    cout << "afficher valide !" << endl;

    carte.~Carte();
    assert(carte.jouee == false && carte.valeur == 0);
    cout << "Destructeur valide !" << endl;*/
}

void Joueur::afficher() const {
    cout << "Pseudo : " << pseudo << " ; Couleur : " << couleur << endl;
}