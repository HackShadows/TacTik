/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cassert>

using namespace std;


Plateau::Plateau(){
    nbCases = 16*4;
    cases = new Pion * [nbCases];
    for (int i = 0; i<nbCases; i++) {
        cases[i] = nullptr;
    }
}

Plateau::Plateau(int nbJ){
    nbCases = 16*nbJ;
    cases = new Pion * [nbCases];
    for (int i = 0; i<nbCases; i++) {
        cases[i] = nullptr;
    }
}

Plateau::~Plateau() {
    for (int i = 0; i<nbCases; i++) {
        delete cases[i];
    }
    delete [] cases;
    cases = nullptr;
    nbCases = 0;
}

int Plateau::getNbCase() const {
    return nbCases;
}

Pion* Plateau::getPion(int indice) const {
    assert(0 <= indice && indice < nbCases);
    return cases[indice];
}

void Plateau::setPion(Pion* pion, int indice) {
    cases[indice] = pion;
}

Pion& Plateau::viderCase(int indice) {
	Pion& pion = *cases[indice];
    cases[indice] = nullptr;
	return pion;
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

		Pion* pion = new Pion();
		plateau.setPion(pion, 0);
		assert(plateau.cases[0]->getId() == pion->getId());
		cout << "setPion valide !" << endl;

		Pion pion2 = *plateau.getPion(0);
		assert(pion2.getId() == pion->getId());
		cout << "getPion valide !" << endl;

		Pion pion3 = plateau.viderCase(0);
		assert(plateau.cases[0] == nullptr && pion3.getId() == pion2.getId());
		cout << "viderCase valide !" << endl;

		/*cout << "Méthode affichage : " << endl;
		plateau.afficher();
		cout << "afficher valide !" << endl;*/
		delete pion;
	}
    cout << "Destructeur valide !" << endl;
}

void Plateau::afficher() const {
    cout << "Nombre de cases : " << nbCases << endl;
}