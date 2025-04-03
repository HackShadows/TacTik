/**
* @brief Contient l'implémentation de la classe IA.
*/
#include "IA.h"
#include "Jeu.h"

#include <iostream>
#include <cassert>

using namespace std;

IA::IA(): couleur(0) {}

IA::IA(int id_couleur): couleur(id_couleur) {
    assert(1 <= id_couleur && id_couleur <= 6);
}

IA::~IA() {}

void IA::jouerCoup(Jeu &jeu, vector<pair<int, int>> vect) const {
    if (vect.size() == 0) jeu.defausserJoueur(couleur);
}

vector<pair<int, int>> IA::genererCoups(Jeu &jeu) const {
    vector<pair<int, int>> coups;
    const Joueur &joueur = jeu.getJoueur(couleur-1);
    bool coequipier = joueur.maisonRemplie();
    for (int i = (couleur-1)*4 ; i < couleur*4 ; i++) {
        for (int j = 0 ; j < 4 ; j++) {
            int val = joueur.getCarte(j)->getValeur();
            if (jeu.carteJouable(couleur, val, coequipier)) coups.push_back({i+1, val});
        }
    }
    return coups;
}

void IA::testRegression() {
    {
        IA ia;
		assert(ia.couleur == 0);
		cout << "Constructeur par défaut valide !" << endl;

		IA ia2(3);
		assert(ia2.couleur == 3);
		cout << "Constructeur avec paramètres valide !" << endl;
    }
    cout << "Destructeur valide !" << endl;
}