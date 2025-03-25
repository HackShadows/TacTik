/**
* @brief Contient l'implémentation de la classe Pioche.
*/
#include "Pioche.h"

#include <iostream>
#include <cassert>

using namespace std;


Pioche::Pioche() {
    for (int i = 0; i<13; i++) {
		if (i == 3) continue;
        for (int j = 0; j<4; j++) {
            pile[i*4+j] = Carte(i+1);
        }
    }
	for (int j = 12; j<16; j++) {
		pile[j] = Carte(-4);
	}
    pile[52] = Carte(-1);
    pile[53] = Carte(-1);
	tas = nullptr;
}

Pioche::~Pioche() {
    tas = nullptr;
}

void Pioche::setTas(Carte * carte){
    tas = carte;
}

Carte* Pioche::getTas() const{
    return tas;
}

Carte& Pioche::getCarte(int indice) {
    assert(0 <= indice && indice < 54);
    return pile[indice];
}

void Pioche::testRegression(){
	{
		Pioche pioche;
		for (int i = 0; i<13; i++) {
			for (int j = 0; j<4; j++) {
				if (i == 3) assert(pioche.pile[i*4+j].getValeur() == -4);
				else assert(pioche.pile[i*4+j].getValeur() == i+1);
			}
		}
		assert(pioche.pile[52].getValeur() == -1);
		assert(pioche.pile[53].getValeur() == -1);
		cout << "Constructeur valide !" << endl;

		Carte* carte = new Carte();
		pioche.setTas(carte);
		assert(pioche.tas->getValeur() == 0);
		cout << "setTas valide !" << endl;

		Carte* carte2 = pioche.getTas();
		assert(carte2->getValeur() == 0);
		cout << "getTas valide !" << endl;

		Carte carte3 = pioche.getCarte(52);
		assert(carte3.getValeur() == -1);
		cout << "getCarte valide !" << endl;

		delete carte;
	}
    cout << "Destructeur valide !" << endl;
}