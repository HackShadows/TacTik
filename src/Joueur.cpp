/**
* @brief Contient l'implémentation de la classe Joueur.
*/
#include "Joueur.h"

#include <iostream>
#include <cassert>

using namespace std;


Joueur::Joueur(): pseudo("Jean"), couleur(0){
    for (int i = 0; i<4; i++){
        main[i] = nullptr;
        maison[i] = false;
    }
}

Joueur::Joueur(int id_couleur): pseudo("Jean"), couleur(id_couleur){
    for (int i = 0; i<4; i++){
        main[i] = nullptr;
        maison[i] = false;
    }
}

Joueur::~Joueur() {
    for (int i = 0; i<4; i++){
        main[i] = nullptr;
    }
}

void Joueur::setPseudo(string nom){
    pseudo = nom;
}

void Joueur::setMaison(int indice, bool etat) {
    assert(0 <= indice && indice < 4);
    maison[indice] = etat;
}

void Joueur::piocherCarte(int indice, Carte * carte){
    assert(main[indice] == nullptr);
    main[indice] = carte;
}

Carte* Joueur::jouerCarte(int valeur) {
    assert(-1 <= valeur && valeur <= 13);
    for (int i = 0; i<4; i++){
        Carte* carte = main[i];
        if (carte != nullptr && valeur == carte->getValeur()) {
            main[i] = nullptr;
            return carte;
        }
    }
    return nullptr;
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
    for (int i = 0 ; i < 4 ; i++) {
        assert(joueur.maison[i] == false);
        assert(joueur.main[i] == nullptr);
    }
    cout << "Constructeur valide !" << endl;

    joueur.setPseudo("Toto");
    assert(joueur.pseudo == "Toto");
    cout << "setPseudo valide !" << endl;

    Carte carte_tmp;
    carte_tmp.setCarte(12);
    joueur.piocherCarte(3, &carte_tmp);
    assert(joueur.main[3]->getValeur() == 12);
    cout << "piocherCarte valide !" << endl;

    Carte * carte = joueur.jouerCarte(12);
    assert(carte->getValeur() == 12 && joueur.main[3] == nullptr);
    cout << "jouerCarte valide !" << endl;

    bool remplie = joueur.maisonRemplie();
    assert(carte->getValeur() == 12 && joueur.main[3] == nullptr);
    cout << "jouerCarte valide !" << endl;
}

void Joueur::afficher() const {
    cout << "Pseudo : " << pseudo << " ; Couleur : " << couleur << endl;
}