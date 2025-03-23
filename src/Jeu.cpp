
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
			int id_pion = i*4+j+1;
			pions[id_pion-1] = Pion(id_pion);
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
			int id_pion = i*4+j+1;
			pions[id_pion-1] = Pion(id_pion);
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

const Joueur& Jeu::getJoueur(int indice) const {
	assert(0 <= indice && indice < nbJoueurs);
	return joueurs[indice];
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

void Jeu::demarrer(int id_pion) {
	Pion& pion = pions[id_pion-1];
	int couleur = (id_pion-1)/4;
	joueurs[couleur].setReserve(-1);
	if (nbJoueurs == 4) {
		pion.setPos(16*couleur);
		plateau.setPion(id_pion, 16*couleur);
	} else {
		if (couleur == 2 || couleur == 3) couleur++;
		else if (couleur == 4) couleur = 2;
		pion.setPos(16*couleur);
		plateau.setPion(id_pion, 16*couleur);
	}
}

void Jeu::eliminerPion(int id_pion) {
	assert(1 <= id_pion && id_pion <= 4*nbJoueurs);
	Pion& pion = pions[id_pion-1];
	plateau.viderCase(pion.getPos());
	pion.setPos(-1);
	joueurs[(id_pion-1)/4].setReserve(1);
}

void Jeu::avancerPion(int val_carte, int id_pion) {
	assert(1 <= id_pion && id_pion <= 4*nbJoueurs);
	assert((val_carte == -4 || (1 <= val_carte && val_carte <= 13 && val_carte != 11 && val_carte != 4)));
	Pion& pion = pions[id_pion-1];
	int position = pion.getPos();
	int nb_cases = plateau.getNbCase();
	int a_eliminer[4*nbJoueurs-1] = {0};
	int nb_elimines = 0;
	int i_deb = position+1, i_fin = position+val_carte;
	if (val_carte == -4) {i_deb = i_fin; i_fin = position-1;}
	
	for (int i = i_deb ; i <= i_fin ; i++) {
		int id_tmp = plateau.getIdPion(i%nb_cases);
		if (id_tmp != 0) {
			if (pions[id_tmp-1].estPieu()) {
				return ;
			} else if (val_carte == 7 || i == position+val_carte) {
				a_eliminer[nb_elimines] = plateau.getIdPion(i%nb_cases);
				nb_elimines++;
			}
		}
	}
	for (int i = 0 ; i < nb_elimines ; i++) {
		eliminerPion(a_eliminer[i]);
	}
	int new_pos = (position+val_carte)%nb_cases;
	pion.setPieu(false);
	pion.setPos(new_pos);
	plateau.setPion(plateau.viderCase(position), new_pos);
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

		const Joueur& joueur = jeu.getJoueur(2);
		assert(joueur.getCouleur() == 3);
		cout << "getJoueur valide !" << endl;

		jeu.distribuer();
		cout << "distribuer valide !" << endl;

		jeu.demarrer(2);
		jeu.demarrer(5);
		jeu.demarrer(10);
		jeu.demarrer(14);
		const Plateau& plateau2 = jeu.getPlateau();
		assert(plateau2.getIdPion(0) == 2 && jeu.getJoueur(0).getReserve() == 3);
		assert(plateau2.getIdPion(16) == 5 && jeu.getJoueur(1).getReserve() == 3);
		assert(plateau2.getIdPion(32) == 10 && jeu.getJoueur(2).getReserve() == 3);
		assert(plateau2.getIdPion(48) == 14 && jeu.getJoueur(3).getReserve() == 3);

		jeu2.demarrer(2);
		jeu2.demarrer(5);
		jeu2.demarrer(10);
		jeu2.demarrer(14);
		jeu2.demarrer(17);
		jeu2.demarrer(24);
		const Plateau& plateau3 = jeu2.getPlateau();
		assert(plateau3.getIdPion(0) == 2 && jeu2.getJoueur(0).getReserve() == 3);
		assert(plateau3.getIdPion(16) == 5 && jeu2.getJoueur(1).getReserve() == 3);
		assert(plateau3.getIdPion(48) == 10 && jeu2.getJoueur(2).getReserve() == 3);
		assert(plateau3.getIdPion(64) == 14 && jeu2.getJoueur(3).getReserve() == 3);
		assert(plateau3.getIdPion(32) == 17 && jeu2.getJoueur(4).getReserve() == 3);
		assert(plateau3.getIdPion(80) == 24 && jeu2.getJoueur(5).getReserve() == 3);
		cout << "demarrer valide !" << endl;

		jeu2.eliminerPion(2);
		jeu2.eliminerPion(10);
		const Plateau& plateau4 = jeu2.getPlateau();
		assert(plateau4.getIdPion(0) == 0 && jeu2.getJoueur(0).getReserve() == 4);
		assert(plateau4.getIdPion(48) == 0 && jeu2.getJoueur(2).getReserve() == 4);
		cout << "eliminerPion valide !" << endl;

		jeu.avancerPion(3, 2);
		jeu.avancerPion(13, 14);
		const Plateau& plateau5 = jeu.getPlateau();
		assert(plateau5.getIdPion(3) == 2);
		assert(plateau5.getIdPion(61) == 14);
		jeu.avancerPion(7, 14);
		const Plateau& plateau6 = jeu.getPlateau();
		assert(plateau6.getIdPion(3) == 0 && jeu.getJoueur(0).getReserve() == 4);
		assert(plateau6.getIdPion(4) == 14);
		cout << "avancerPion valide !" << endl;
	}
	cout << "Destructeur valide !" << endl;
}

