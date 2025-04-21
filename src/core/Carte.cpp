/**
* @brief Contient l'implémentation de la classe Carte.
*/
#include "Carte.h"

#include <iostream>
#include <cassert>

using namespace std;


Carte::Carte(): valeur(0) {}

Carte::Carte(int val): valeur(val) {
	assert(val == -4 || (-1 <= val && val <= 13 && val != 4));
}

Carte::~Carte() {
	valeur = 0;
}

int Carte::getValeur() const {
	return valeur;
}

void Carte::testRegression(){
	{
		Carte carte;
		assert(carte.valeur == 0);
		cout << "Constructeur par défaut valide !" << endl;

		Carte carte2(3);
		assert(carte2.valeur == 3);
		cout << "Constructeur avec paramètre valide !" << endl;

		int val = carte2.getValeur();
		assert(val == 3);
		cout << "getCarte valide !" << endl;
	}
	cout << "Destructeur valide !" << endl;
}