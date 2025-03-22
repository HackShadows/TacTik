/**
* @brief Contient l'implémentation de la classe Pioche.
*/
#include "Pioche.h"

#include <iostream>
#include <cassert>

using namespace std;


Pioche::Pioche() {
    for (int i = 0; i<13; i++) {
        for (int j = 0; j<4; j++) {
            pile[i*4+j].setCarte(i+1);
        }
    }
    pile[52].setCarte(-1);
    pile[53].setCarte(-1);
	tas = Carte();
}

Pioche::~Pioche() {
    tas = Carte();
}

void Pioche::setTas(const Carte & carte){
    tas = carte;
}

Carte Pioche::getTas() const{
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
				assert(pioche.pile[i*4+j].getValeur() == i+1 && !pioche.pile[i*4+j].estDansMain());
			}
		}
		assert(pioche.pile[52].getValeur() == -1 && !pioche.pile[52].estDansMain());
		assert(pioche.pile[53].getValeur() == -1 && !pioche.pile[53].estDansMain());
		cout << "Constructeur valide !" << endl;

		Carte carte;
		pioche.setTas(carte);
		assert(pioche.tas.getValeur() == 0 && !pioche.tas.estDansMain());
		cout << "setTas valide !" << endl;

		Carte carte2 = pioche.getTas();
		assert(carte2.getValeur() == 0 && !carte2.estDansMain());
		cout << "getTas valide !" << endl;

		Carte carte3 = pioche.getCarte(52);
		assert(carte3.getValeur() == -1 && !carte3.estDansMain());
		cout << "getCarte valide !" << endl;

		/*cout << "Méthode affichage : " << endl;
		pioche.afficher();
		cout << "afficher valide !" << endl;*/
	}
    cout << "Destructeur valide !" << endl;
}

void Pioche::afficher() const {
    cout << "Tas : ";
    tas.afficher();
    for (int i = 0 ; i < 54 ; i++) pile[i].afficher();
}
