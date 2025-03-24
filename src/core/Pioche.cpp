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
            pile[i*4+j].setCarte(i+1);
        }
    }
	for (int j = 12; j<16; j++) {
		pile[j].setCarte(-4);
	}
    pile[52].setCarte(-1);
    pile[53].setCarte(-1);
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
				if (i == 3) assert(pioche.pile[i*4+j].getValeur() == -4 && !pioche.pile[i*4+j].estDansMain());
				else assert(pioche.pile[i*4+j].getValeur() == i+1 && !pioche.pile[i*4+j].estDansMain());
			}
		}
		assert(pioche.pile[52].getValeur() == -1 && !pioche.pile[52].estDansMain());
		assert(pioche.pile[53].getValeur() == -1 && !pioche.pile[53].estDansMain());
		cout << "Constructeur valide !" << endl;

		Carte* carte = new Carte();
		pioche.setTas(carte);
		assert(pioche.tas->getValeur() == 0 && !pioche.tas->estDansMain());
		cout << "setTas valide !" << endl;

		Carte* carte2 = pioche.getTas();
		assert(carte2->getValeur() == 0 && !carte2->estDansMain());
		cout << "getTas valide !" << endl;

		Carte carte3 = pioche.getCarte(52);
		assert(carte3.getValeur() == -1 && !carte3.estDansMain());
		cout << "getCarte valide !" << endl;

		/*cout << "Méthode affichage : " << endl;
		pioche.afficher();
		cout << "afficher valide !" << endl;*/
		delete carte;
	}
    cout << "Destructeur valide !" << endl;
}

void Pioche::afficher() const {
    cout << "Tas : ";
    tas->afficher();
    for (int i = 0 ; i < 54 ; i++) pile[i].afficher();
}
