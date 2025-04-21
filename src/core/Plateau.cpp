/**
* @brief Contient l'implémentation de la classe Plateau.
*/
#include "Plateau.h"

#include <iostream>
#include <cassert>

using namespace std;


Plateau::Plateau(): nbCases(16*4) {
	cases = new int [nbCases];
	casesDepart = new int [4]{0, 16, 32, 48};
	for (int i = 0; i<nbCases; i++) {
		cases[i] = 0;
	}
}

Plateau::Plateau(int nbJ): nbCases(16*nbJ) {
	cases = new int [nbCases];
	casesDepart = (nbJ == 4) ? new int [4]{0, 16, 32, 48}:new int [6]{0, 16, 48, 64, 32, 80};
	for (int i = 0; i<nbCases; i++) {
		cases[i] = 0;
	}
}

Plateau::~Plateau() {
	delete [] cases;
	delete [] casesDepart;
	cases = nullptr;
	casesDepart = nullptr;
	nbCases = 0;
}

void Plateau::setPion(int idPion, int indice) {
	assert(0 <= indice && indice < nbCases);
	assert(0 < idPion && idPion <= nbCases/4);
	assert(cases[indice] == 0);
	cases[indice] = idPion;
}

int Plateau::getNbCase() const {
	return nbCases;
}

int Plateau::getIdPion(int indice) const {
	assert(0 <= indice && indice < nbCases);
	return cases[indice];
}

int Plateau::getCasesDepart(int couleur) const {
	assert(1 <= couleur && couleur <= nbCases/16);
	return casesDepart[couleur-1];
}

int Plateau::viderCase(int indice) {
	assert(0 <= indice && indice < nbCases);
	int idPion = cases[indice];
	cases[indice] = 0;
	return idPion;
}


void Plateau::testRegression(){
	{
		Plateau plateau;
		assert(plateau.nbCases == 64);
		cout << "Constructeur par défaut valide !" << endl;

		Plateau plateau6(6);
		assert(plateau6.nbCases == 96);
		cout << "Constructeur avec paramètre valide !" << endl;

		plateau.setPion(2, 4);
		assert(plateau.cases[4] == 2);
		cout << "setPion valide !" << endl;

		assert(plateau.getNbCase() == 64);
		assert(plateau6.getNbCase() == 96);
		cout << "getNbCase valide !" << endl;

		int idPion = plateau.getIdPion(4);
		assert(idPion == 2);
		cout << "getIdPion valide !" << endl;

		int case_dep = plateau.getCasesDepart(4);
		assert(case_dep == 48);
		case_dep = plateau6.getCasesDepart(6);
		assert(case_dep == 80);
		cout << "getCasesDepart valide !" << endl;

		int idPion2 = plateau.viderCase(4);
		assert(plateau.cases[4] == 0 && idPion2 == 2);
		cout << "viderCase valide !" << endl;
	}
	cout << "Destructeur valide !" << endl;
}