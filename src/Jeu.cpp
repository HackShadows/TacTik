
#include "Jeu.h"

#include <iostream>
#include <cassert>
#include <stdlib.h>

using namespace std;


Jeu::Jeu() : nbJoueurs(4), plateau(nbJoueurs), pioche(){
    joueurs = new Joueur * [nbJoueurs];
	pions = new Pion [4*nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i] = new Joueur(i+1);
		for (int j = 0 ; j < 4 ; j++) {
			pions[i*4+j] = Pion(i*4+j+1);
		}
    }
  }

Jeu::Jeu(int nbJ) : nbJoueurs(nbJ), plateau(nbJ), pioche(){
    assert(nbJ == 4 || nbJ == 6);
    joueurs = new Joueur * [nbJoueurs];
	pions = new Pion [4*nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i] = new Joueur(i+1);
		for (int j = 0 ; j < 4 ; j++) {
			pions[i*4+j] = Pion(i*4+j+1);
		}
    }
}

Jeu::~Jeu() {
    for (int i = 0 ; i < nbJoueurs ; i++) {
        delete joueurs[i];
    }
    delete [] joueurs;
    joueurs = nullptr;
    nbJoueurs = 0;
	delete [] pions;
    pions = nullptr;
}

const Plateau& Jeu::getPlateau() const {
    return plateau;
}

int Jeu::getNbJoueurs() const {
    return nbJoueurs;
}

bool intInTab(int element, const int * tab, int taille) {
    for (int i = 0 ; i < taille ; i++) {
        if (tab[i] == element) return true;
    }
    return false;
}

void Jeu::distribuer(){
    int indice_carte[4*nbJoueurs];
    for (int i = 0; i<nbJoueurs; i++) {
        int random_int;
        for (int j = 0 ; j < 4 ; j++) {
            do {
                random_int = rand()%54;
            } while (intInTab(random_int, indice_carte, 4*i + j));
            joueurs[i]->piocherCarte(j, &pioche.getCarte(random_int));
            indice_carte[4*i+j] = random_int;
        }
    }
}

void Jeu::eliminerPion(int position) {
	assert(0 <= indice && indice < plateau.getNbCase());
	int id_pion = plateau.getPion(position);
	Pion& pion = pions[id_pion-1];
	pion.setPos(-1);
}

void Jeu::avancerPion(const Carte & carte, int id_pion) {
	assert(1 <= id_pion && id_pion <= 4*nbJoueurs);
	int val = carte.getValeur();
	int ind = pions[id_pion-1].getPos();
	int nb_cases = plateau.getNbCase();
	Pion* ptr_pion;
	assert(1 <= val && val <= 13 && val != 11);
	for (int i = ind+1 ; i <= ind+val ; i++) {
		ptr_pion = plateau.getPion(i%nb_cases);
		if (ptr_pion != nullptr) {
			if (ptr_pion->estPieu()) {
				return ;
			} else if (val == 7 || i == ind+val) {
				eliminerPion(i);
			}
		}
	}
	plateau.setPion(&plateau.viderCase(ind), ind+val);
}

void Jeu::testRegression(){
    {
		Jeu jeu;
		assert(jeu.nbJoueurs == 4);
		cout << "Constructeur par défaut valide !" << endl;

		Jeu jeu2(6);
		assert(jeu2.nbJoueurs == 6);
		cout << "Constructeur avec paramètres valide !" << endl;

		const Plateau& plateau = jeu.getPlateau();
		assert(plateau.getNbCase() == 64);
		cout << "getPlateau valide !" << endl;

		int nbJ = jeu.getNbJoueurs();
		assert(nbJ == 4);
		cout << "getNbJoueurs valide !" << endl;

		jeu.distribuer();
		cout << "distribuer valide !" << endl;
	}
	cout << "Destructeur valide !" << endl;
}

