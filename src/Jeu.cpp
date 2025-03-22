
#include "Jeu.h"

#include <iostream>
#include <cassert>
#include <stdlib.h>

using namespace std;


Jeu::Jeu() : nbJoueurs(4), plateau(nbJoueurs), pioche(){
    joueurs = new Joueur [nbJoueurs];
	pions = new Pion [4*nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i] = Joueur(i+1);
		for (int j = 0 ; j < 4 ; j++) {
			pions[i*4+j] = Pion(i*4+j+1);
		}
    }
  }

Jeu::Jeu(int nbJ) : nbJoueurs(nbJ), plateau(nbJ), pioche(){
    assert(nbJ == 4 || nbJ == 6);
    joueurs = new Joueur [nbJoueurs];
	pions = new Pion [4*nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i] = Joueur(i+1);
		for (int j = 0 ; j < 4 ; j++) {
			pions[i*4+j] = Pion(i*4+j+1);
		}
    }
}

Jeu::~Jeu() {
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
            joueurs[i].piocherCarte(j, &pioche.getCarte(random_int));
            indice_carte[4*i+j] = random_int;
        }
    }
}

void Jeu::eliminerPion(int position) {
	assert(0 <= position && position < plateau.getNbCase());
	int id_pion = plateau.getIdPion(position);
	Pion& pion = pions[id_pion-1];
	pion.setPos(-1);
	joueurs[(id_pion-1)/4].setReserve(1);
}

void Jeu::avancerPion(const Carte & carte, int id_pion) {
	assert(1 <= id_pion && id_pion <= 4*nbJoueurs);
	int val = carte.getValeur();
	int ind = pions[id_pion-1].getPos();
	int nb_cases = plateau.getNbCase();
	int id_tmp;
	assert(1 <= val && val <= 13 && val != 11);
	for (int i = ind+1 ; i <= ind+val ; i++) {
		id_tmp = plateau.getIdPion(i%nb_cases);
		if (id_tmp != 0) {
			Pion& pion = pions[id_tmp-1];
			if (pion.estPieu()) {
				return ;
			} else if (val == 7 || i == ind+val) {
				pion.setPos(-1);
				joueurs[(id_tmp-1)/4].setReserve(1);
			}
		}
	}
	plateau.setPion(plateau.viderCase(ind), ind+val);
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

