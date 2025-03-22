/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cassert>

using namespace std;


Plateau::Plateau(){
    nbCases = 16*4;
    cases = new int [nbCases];
    for (int i = 0; i<nbCases; i++) {
        cases[i] = 0;
    }
}

Plateau::Plateau(int nbJ){
    nbCases = 16*nbJ;
    cases = new int [nbCases];
    for (int i = 0; i<nbCases; i++) {
        cases[i] = 0;
    }
}

Plateau::~Plateau() {
    delete [] cases;
    cases = nullptr;
    nbCases = 0;
}

int Plateau::getNbCase() const {
    return nbCases;
}

int Plateau::getIdPion(int indice) const {
    assert(0 <= indice && indice < nbCases);
    return cases[indice];
}

void Plateau::setPion(int id_pion, int indice) {
    cases[indice] = id_pion;
}

int Plateau::viderCase(int indice) {
	int id_pion = cases[indice];
    cases[indice] = 0;
	return id_pion;
}


void Plateau::testRegression(){
	{
		Plateau plateau;
		assert(plateau.nbCases == 64);
		cout << "Constructeur par défaut valide !" << endl;

		Plateau plateau6(6);
		assert(plateau6.nbCases == 96);
		cout << "Constructeur avec paramètre valide !" << endl;

		assert(plateau.getNbCase() == 64);
		assert(plateau6.getNbCase() == 96);
		cout << "getNbCase valide !" << endl;

		plateau.setPion(2, 4);
		assert(plateau.cases[4] == 2);
		cout << "setPion valide !" << endl;

		int id_pion = plateau.getIdPion(4);
		assert(id_pion == 2);
		cout << "getIdPion valide !" << endl;

		int id_pion2 = plateau.viderCase(4);
		assert(plateau.cases[4] == 0 && id_pion2 == 2);
		cout << "viderCase valide !" << endl;

		/*cout << "Méthode affichage : " << endl;
		plateau.afficher();
		cout << "afficher valide !" << endl;*/
	}
    cout << "Destructeur valide !" << endl;
}

void Plateau::afficher() const {
    cout << "Nombre de cases : " << nbCases << endl;
}