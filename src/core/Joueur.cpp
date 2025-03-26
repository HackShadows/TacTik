/**
* @brief Contient l'implémentation de la classe Joueur.
*/
#include "Joueur.h"

#include <iostream>
#include <cassert>

using namespace std;


Joueur::Joueur(): couleur(0), reserve(4) {
    for (int i = 0; i<4; i++){
        main[i] = nullptr;
    }
}

Joueur::Joueur(int id_couleur): couleur(id_couleur), reserve(4) {
    assert(1 <= id_couleur && id_couleur <= 6);
    for (int i = 0; i<4; i++){
        main[i] = nullptr;
    }
}

Joueur::~Joueur() {
    for (int i = 0; i<4; i++){
        main[i] = nullptr;
    }
}

void Joueur::setMaison(int indice, int id_pion) {
    assert(0 <= indice && indice < 4);
	assert(0 <= id_pion && id_pion <=24);
    maison[indice] = id_pion;
}

void Joueur::setReserve(int quantite) {
	assert(quantite == 1 || quantite == -1);
	reserve += quantite;
}

Carte* Joueur::getCarte(int indice) const {
	assert(0 <= indice && indice < 4);
	return main[indice];
}

int Joueur::getReserve() const {
	return reserve;
}

int Joueur::getCouleur() const {
	return couleur;
}

const int* Joueur::getMaison() const {
	return maison;
}

bool Joueur::estDansMain(int val_carte) const {
	if (val_carte == 4 || val_carte == 0 ||(val_carte < -1 && val_carte != -4)  || val_carte > 13) return false;
	for (int i = 0; i<4; i++){
        Carte* carte = main[i];
        if (carte != nullptr && val_carte == carte->getValeur()) {
            return true;
        }
    }
	return false;
}

bool Joueur::piocherCarte(Carte * carte) {
	assert(carte->getValeur() != 0);
    for (int i = 0 ; i < 4 ; i++) {
		if (main[i] == nullptr) {
			main[i] = carte;
			return true;
		}
	}
	return false;
}

Carte* Joueur::retirerCarte(int valeur, int indice) {
	if (indice != -1) {
		assert(0 <= indice && indice < 4);
		Carte* carte = main[indice];
		main[indice] = nullptr;
		return carte;
	}
	assert(valeur == -4 || (-1 <= valeur && valeur <= 13 && valeur != 0 && valeur != 4));
    for (int i = 0; i<4; i++){
        Carte* carte = main[i];
        if (carte != nullptr && valeur == carte->getValeur()) {
            main[i] = nullptr;
            return carte;
        }
    }
    return nullptr;
}

bool Joueur::maisonRemplie() const {
    for (int i = 0; i<4; i++){
        if (maison[i] == 0){
            return false;
        }
    }
    return true;
}

void Joueur::testRegression(){
	{
		Joueur joueur;
		assert(joueur.couleur == 0);
		for (int i = 0 ; i < 4 ; i++) {
			assert(joueur.maison[i] == 0);
			assert(joueur.main[i] == nullptr);
		}
		cout << "Constructeur par défaut valide !" << endl;

		Joueur joueur2(3);
		assert(joueur2.couleur == 3);
		for (int i = 0 ; i < 4 ; i++) {
			assert(joueur2.maison[i] == 0);
			assert(joueur2.main[i] == nullptr);
		}
		cout << "Constructeur avec paramètres valide !" << endl;

		joueur.setMaison(2, 5);
		assert(joueur.maison[2] == 5);
		cout << "setMaison valide !" << endl;

		joueur.setReserve(-1);
		assert(joueur.reserve == 3);
		cout << "setReserve valide !" << endl;

		Carte * cartes = new Carte[4];
		for (int i = 0 ; i < 4 ; i++) {
			cartes[i] = Carte(9+i);
			assert(joueur.piocherCarte(&cartes[i]));
			assert(joueur.main[i]->getValeur() == 9+i);
		}
		Carte carte_tmp = Carte(8);
		assert(!joueur.piocherCarte(&carte_tmp));
		cout << "piocherCarte valide !" << endl;

		Carte * carte = joueur.getCarte(3);
		assert(carte->getValeur() == 12);
		cout << "getCarte valide !" << endl;

		assert(joueur.getReserve() == 3);
		cout << "getReserve valide !" << endl;

		assert(joueur.getCouleur() == 0);
		assert(joueur2.getCouleur() == 3);
		cout << "getCouleur valide !" << endl;

		const int* mais = joueur.getMaison();
		const int* mais2 = joueur2.getMaison();
		for (int i = 0 ; i < 4 ; i++) assert(mais2[i] == 0);
		assert(mais[2] == 5);
		cout << "getMaison valide !" << endl;

		for (int i = 9 ; i < 13 ; i++) assert(joueur.estDansMain(i));
		cout << "estDansMain valide !" << endl;

		Carte * carte2 = joueur.retirerCarte(12);
		assert(carte2->getValeur() == 12 && joueur.main[3] == nullptr);
		cout << "retirerCarte valide !" << endl;

		bool remplie = joueur.maisonRemplie();
		assert(!remplie);
		for (int i = 0 ; i < 4 ; i++) joueur.setMaison(i, 2);
		remplie = joueur.maisonRemplie();
		assert(remplie);
		cout << "maisonRemplie valide !" << endl;

		delete [] cartes;
	}
	cout << "Destructeur valide !" << endl;
}