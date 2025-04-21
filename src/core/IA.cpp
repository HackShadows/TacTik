/**
* @brief Contient l'implémentation de la classe IA.
*/
#include "IA.h"
#include "Jeu.h"

#include <iostream>
#include <cassert>

using namespace std;

IA::IA() {}

IA::~IA() {}

void IA::jouerCoup(Jeu &jeu, vector<pair<int, int>> vect, int couleur) const {
	const Joueur &joueur = jeu.getJoueur(couleur-1);
	int valeurs [11] = {-4, 1, 2, 3, 5, 6, 8, 9, 10, 12, 13};
	if (vect.size() == 0 && joueur.getReserve() == 4) jeu.defausserJoueur(couleur);
	else if (vect.size() == 0) cout << "Non traité" << endl;
	else {
		int val = vect[rand()%vect.size()].second;
		if (val == -1 && jeu.demarrer(couleur)) return ;
		//else if (val == -1) jeu.jouerCarte(valeurs[rand()%11], couleur);
		//else jeu.jouerCarte(val, couleur);
	}
}

vector<pair<int, int>> IA::genererCoups(Jeu &jeu, int couleur) const {
	vector<pair<int, int>> coups;
	const Joueur &joueur = jeu.getJoueur(couleur-1);
	bool coequipier = joueur.maisonRemplie();
	for (int i = (couleur-1)*4 ; i < couleur*4 ; i++) {
		for (int j = 0 ; j < 4 ; j++) {
			Carte* carte = joueur.getCarte(j);
			if (carte == nullptr) continue;
			int val = carte->getValeur();
			if (jeu.carteJouable(couleur, val, coequipier)) coups.push_back({i+1, val});
		}
	}
	jouerCoup(jeu, coups, couleur);
	return coups;
}

void IA::testRegression() {
	{
		IA ia;
		cout << "Constructeur par défaut valide !" << endl;
	}
	cout << "Destructeur valide !" << endl;
}