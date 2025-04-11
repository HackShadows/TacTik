#include "Jeu.h"

#include <iostream>
#include <cassert>
#include <stdlib.h>

using namespace std;

bool intInTab(int element, const int * tab, int taille) {
	for (int i = 0 ; i < taille ; i++) {
		if (tab[i] == element) return true;
	}
	return false;
}

void messageDefaut(string message) {
	cout << message << endl;
}

Jeu::Jeu() : nbJoueurs(4), plateau(nbJoueurs), pioche(){
    joueurs = new Joueur [nbJoueurs];
	pions = new Pion [4*nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i] = Joueur(i+1);
		for (int j = 0 ; j < 4 ; j++) {
			int idPion = i*4+j+1;
			pions[idPion-1] = Pion(idPion);
		}
    }
}

Jeu::Jeu(int nbJ, int nbIA) : nbJoueurs(nbJ), plateau(nbJ), pioche(){
    assert(nbIA >= 0 && nbJ >= nbIA && (nbJ == 4 || nbJ == 6));
    joueurs = new Joueur [nbJoueurs];
	pions = new Pion [4*nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i] = Joueur(i+1, (i < nbIA));
		for (int j = 0 ; j < 4 ; j++) {
			int idPion = i*4+j+1;
			pions[idPion-1] = Pion(idPion);
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

void Jeu::setTas(Carte* carte) {
	pioche.setTas(carte);
}

const Plateau& Jeu::getPlateau() const {
    return plateau;
}

const Pioche& Jeu::getPioche() const {
    return pioche;
}

int Jeu::getNbJoueurs() const {
    return nbJoueurs;
}

const Joueur& Jeu::getJoueur(int indice) const {
	assert(0 <= indice && indice < nbJoueurs);
	return joueurs[indice];
}

Joueur& Jeu::getJoueurNonConst(int indice) {
	assert(0 <= indice && indice < nbJoueurs);
	return joueurs[indice];
}

const Pion& Jeu::getPion(int idPion) const {
	assert(0 < idPion && idPion <= 4*nbJoueurs);
	return pions[idPion-1];
}


void Jeu::distribuer() {
    int indice_carte[4*nbJoueurs];
    for (int i = 0; i<nbJoueurs; i++) {
        int random_int;
        for (int j = 0 ; j < 4 ; j++) {
            do {
                random_int = rand()%54;
            } while (intInTab(random_int, indice_carte, 4*i + j));
            joueurs[i].piocherCarte(&pioche.getCarte(random_int));
            indice_carte[4*i+j] = random_int;
        }
    }
}

bool Jeu::attribuerCarte(int valCarte, int couleur) {
	assert(1 <= couleur && couleur <= nbJoueurs);
	assert((valCarte == -4 || valCarte == -1 || (1 <= valCarte && valCarte <= 13 && valCarte != 4)));
	int ind;
	switch (valCarte)
	{
		case -4:
			ind = 12;
			break;
		
		case -1:
			ind = 52;
			break;
		
		default:
			ind = (valCarte-1)*4;
			break;
	}
	return joueurs[couleur-1].piocherCarte(&pioche.getCarte(ind));
}

void Jeu::echangerCartes(int indJ1, int indJ2, int valCarteJ1, int valCarteJ2) {
	assert((indJ1 == 0 && indJ2 == 2) || (indJ1 == 1 && indJ2 == 3) || (indJ1 == 4 && indJ2 == 5 && nbJoueurs == 6));
	Carte* carteJ1 = joueurs[indJ1].retirerCarte(valCarteJ1);
	Carte* carteJ2 = joueurs[indJ2].retirerCarte(valCarteJ2);
	joueurs[indJ1].piocherCarte(carteJ2);
	joueurs[indJ2].piocherCarte(carteJ1);
}

bool Jeu::defausserCarte(int valCarte, int couleur) {
	assert(1 <= couleur && couleur <= nbJoueurs);
	Carte* carte = joueurs[couleur-1].retirerCarte(valCarte);
	if (carte == nullptr) return false;
	pioche.setTas(carte);
	return true;
}

void Jeu::defausserJoueur(int couleur) {
	assert(1 <= couleur && couleur <= nbJoueurs);
	Carte* carte = joueurs[couleur-1].defausserMain();
	if (carte == nullptr) return ;
	pioche.setTas(carte);
}

void Jeu::eliminerPion(int idPion) {
	assert(1 <= idPion && idPion <= 4*nbJoueurs);
	Pion &pion = pions[idPion-1];
	plateau.viderCase(pion.getPos());
	pion.setPos(-1);
	pion.setPieu(true);
	joueurs[(idPion-1)/4].setReserve(1);
}

bool Jeu::demarrer(int couleur, bool test) {
	if (joueurs[couleur-1].getReserve() == 0) return false;
	int idPion = 0;
	for (int i = 4*(couleur-1) ; i < 4*couleur ; i++) {
		if (pions[i].getPos() == -1) {
			idPion = i+1;
			break;
		}
	}
	int case_dep = plateau.getCasesDepart(couleur);
	int idPion_tmp = plateau.getIdPion(case_dep);
	if (idPion_tmp != 0) {
		if (pions[idPion_tmp-1].estPieu()) return false;
		else if (!test) eliminerPion(idPion_tmp);
	}
	if (!test) {
		joueurs[couleur-1].setReserve(-1);
		pions[idPion-1].setPos(case_dep);
		plateau.setPion(idPion, case_dep);
	}
	return true;
}

bool Jeu::avancerPion(int valCarte, int idPion, bool test, bool septx1) {
	assert(1 <= idPion && idPion <= 4*nbJoueurs);
	assert((valCarte == -4 || (1 <= valCarte && valCarte <= 13 && valCarte != 11)));
	
	Pion &pion = pions[idPion-1];
	int position = pion.getPos(), case_dep = plateau.getCasesDepart((idPion-1)/4+1);
	
	if (position == -1) return false;
	if (position == -2) return avancerMaison(valCarte, idPion, test);
	if (position == case_dep && !pion.estPieu() && avancerMaison(valCarte, idPion, true)) return avancerMaison(valCarte, idPion, test);
	
	int nb_cases = plateau.getNbCase();
	int a_eliminer[7] = {0};
	int nb_elimines = 0;
	int ind, i_deb = position+1, i_fin = position+valCarte;
	int maison = -1;
	if (valCarte == 7) septx1 = true;
	if (valCarte == -4) {i_deb = i_fin; i_fin = position-1;}
	
	for (int i = i_deb ; i <= i_fin ; i++) {
		ind = (i+nb_cases)%nb_cases;
		int id_tmp = plateau.getIdPion(ind);
		if (id_tmp != 0) {
			if (pions[id_tmp-1].estPieu()) {
				return false;
			} else if (septx1 || i == position+valCarte) {
				a_eliminer[nb_elimines] = plateau.getIdPion(ind);
				nb_elimines++;
			}
		}
		if (ind == case_dep && valCarte != -4 && avancerMaison(i_fin-i, idPion, true)) {
			maison = i_fin-i;
			break;
		}
	}
	if (!test) {
		for (int i = 0 ; i < nb_elimines ; i++) {
			eliminerPion(a_eliminer[i]);
		}
		if (maison == -1) {
			int new_pos = (position+valCarte+nb_cases)%nb_cases;
			pion.setPieu(false);
			pion.setPos(new_pos);
			plateau.setPion(plateau.viderCase(position), new_pos);
		} else {
			int new_pos = case_dep;
			pion.setPieu(false);
			pion.setPos(new_pos);
			plateau.setPion(plateau.viderCase(position), new_pos);
			avancerMaison(maison, idPion);
		}
	}
	return true;
}

bool Jeu::avancerMaison(int valCarte, int idPion, bool test) {
	assert(1 <= idPion && idPion <= 4*nbJoueurs);
	if (!(0 < valCarte && valCarte <= 4)) return false;
	int i_deb = 0, couleur = (idPion-1)/4+1;
	const int* mais = joueurs[couleur-1].getMaison();
	Pion &pion = pions[idPion-1];
	if (pion.getPos() == -2) {
		for (int i = 0 ; i < 4 ; i++) {
			if (mais[i] == idPion) {
				i_deb = i+1;
				break;
			}
		}
	}
	if (i_deb + valCarte > 4) return false;

	for (int i = i_deb ; i < i_deb + valCarte ; i++) {
		if (mais[i] != 0) return false;
	}
	if (!test) {
		if (i_deb > 0) {
			joueurs[couleur-1].setMaison(i_deb-1, 0);
		} else {
			plateau.viderCase(plateau.getCasesDepart(couleur));
			pion.setPos(-2);
			pion.setPieu(true);
		} 
		joueurs[couleur-1].setMaison(i_deb+valCarte-1, idPion);
	}
	return true;
}

bool Jeu::permutter(int idPion1, int idPion2, bool test) {
	assert(0 < idPion1 && idPion1 <= 4*nbJoueurs && 0 < idPion2 && idPion2 <= 4*nbJoueurs && idPion1 != idPion2);
	if (pions[idPion1-1].getPos() < 0) return false;
	if (pions[idPion2-1].estPieu()) return false;
	if (!test) {
		Pion &pion1 = pions[idPion1-1], &pion2 = pions[idPion2-1];
		int pos1 = pion1.getPos(), pos2 = pion2.getPos();
		pion1.setPieu(false);
		pion1.setPos(pos2);
		pion2.setPos(pos1);
		plateau.viderCase(pos1);
		plateau.viderCase(pos2);
		plateau.setPion(idPion1, pos2);
		plateau.setPion(idPion2, pos1);
	}
	return true;
}

bool Jeu::partieGagnee() const {
	if ((joueurs[0].maisonRemplie() && joueurs[2].maisonRemplie()) || 
	(joueurs[1].maisonRemplie() && joueurs[3].maisonRemplie()) ||
	(nbJoueurs == 6 && joueurs[4].maisonRemplie() && joueurs[5].maisonRemplie())) return true;
	return false;
}

bool Jeu::carteJouable(int couleur, int valCarte, bool coequipier, bool joker){
	assert(1 <= couleur && couleur <= nbJoueurs);
	assert(valCarte == -4 || (-1 <= valCarte && valCarte <= 13 && valCarte != 0 && valCarte != 4));
	
	Joueur joueur = joueurs[couleur-1];
	if (!joueur.estDansMain(valCarte) && !(joker && joueur.estDansMain(-1))) return false;
	if (valCarte == -1) return true;
	if (coequipier) couleur = 1 + ((couleur < 5) ? (couleur+1)%4 : 10-couleur);
	for (int j = 0 ; j < 4 ; j++) {
		int idPion = pions[(couleur-1)*4+j].getId();
		switch (valCarte)
		{
			case 11:
				for (int idPion2 = 1 ; idPion2 <= 4*nbJoueurs ; idPion2++) {
					if (idPion2 == idPion) continue;
					if (permutter(idPion, idPion2, true)) return true;
				}
				break;
			
			case 1:
			case 10: 
			case 13:
				if (demarrer(couleur, true)) return true;
			
			default:
				if (avancerPion(valCarte, idPion, true)) return true;
				break;
		}
	}

	return false;
}

bool Jeu::peutJouer(int couleur, bool coequipier) {
	assert(1 <= couleur && couleur <= nbJoueurs);
	Joueur joueur = joueurs[couleur-1];
	int val;
	for (int i = 0 ; i < 4 ; i++) {
		Carte* carte = joueur.getCarte(i);
		if (carte == nullptr) continue;
		val = carte->getValeur();
		if (carteJouable(couleur, val, coequipier)) return true;
	}
	return false;
}


void Jeu::testRegression() {
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

		const Pioche& pioche = jeu.getPioche();
		assert(pioche.getTas() == nullptr);
		cout << "getPioche valide !" << endl;

		int nbJ = jeu.getNbJoueurs();
		assert(nbJ == 4);
		cout << "getNbJoueurs valide !" << endl;

		const Joueur& joueur = jeu.getJoueur(2);
		assert(joueur.getCouleur() == 3);
		cout << "getJoueur valide !" << endl;

		const Pion &pion = jeu.getPion(9);
		assert(pion.getId() == 9);
		cout << "getPion valide !" << endl;

		Joueur& joueur2 = jeu.joueurs[0];
		assert(jeu.attribuerCarte(-1, 1));
		assert(joueur2.getCarte(0)->getValeur() == -1);
		assert(jeu.attribuerCarte(-4, 1));
		assert(joueur2.getCarte(1)->getValeur() == -4);
		assert(jeu.attribuerCarte(3, 1));
		assert(joueur2.getCarte(2)->getValeur() == 3);
		assert(jeu.attribuerCarte(13, 1));
		assert(joueur2.getCarte(3)->getValeur() == 13);
		joueur2.defausserMain();

		jeu.distribuer();
		cout << "distribuer valide !" << endl;

		assert(!jeu.attribuerCarte(-1, 1));
		cout << "attribuerCarte valide !" << endl;
		
		int valJ1 = jeu.getJoueur(0).getCarte(0)->getValeur();
		int valJ2 = jeu.getJoueur(2).getCarte(0)->getValeur();
		jeu.echangerCartes(0, 2, valJ1, valJ2);
		assert(jeu.getJoueur(0).getCarte(0)->getValeur() == valJ2 && jeu.getJoueur(2).getCarte(0)->getValeur() == valJ1);
		cout << "echangerCartes valide !" << endl;

		assert(jeu.defausserCarte(valJ1, 3));
		assert(jeu.getJoueur(2).getCarte(0) == nullptr);
		assert(jeu.defausserCarte(valJ2, 1));
		assert(jeu.getJoueur(0).getCarte(0) == nullptr);
		cout << "defausserCarte valide !" << endl;

		assert(!jeu.getJoueur(0).mainVide());
		jeu.defausserJoueur(1);
		assert(jeu.getJoueur(0).mainVide());
		cout << "defausserJoueur valide !" << endl;

		assert(jeu.demarrer(1));
		assert(jeu.demarrer(2));
		assert(jeu.demarrer(3));
		assert(jeu.demarrer(4));
		const Plateau& plateau2 = jeu.getPlateau();
		assert(plateau2.getIdPion(0) == 1 && jeu.getJoueur(0).getReserve() == 3);
		assert(plateau2.getIdPion(16) == 5 && jeu.getJoueur(1).getReserve() == 3);
		assert(plateau2.getIdPion(32) == 9 && jeu.getJoueur(2).getReserve() == 3);
		assert(plateau2.getIdPion(48) == 13 && jeu.getJoueur(3).getReserve() == 3);

		assert(jeu2.demarrer(1));
		assert(jeu2.demarrer(2));
		assert(jeu2.demarrer(3));
		assert(jeu2.demarrer(4));
		assert(jeu2.demarrer(5));
		assert(jeu2.demarrer(6));
		const Plateau& plateau3 = jeu2.getPlateau();
		assert(plateau3.getIdPion(0) == 1 && jeu2.getJoueur(0).getReserve() == 3);
		assert(plateau3.getIdPion(16) == 5 && jeu2.getJoueur(1).getReserve() == 3);
		assert(plateau3.getIdPion(48) == 9 && jeu2.getJoueur(2).getReserve() == 3);
		assert(plateau3.getIdPion(64) == 13 && jeu2.getJoueur(3).getReserve() == 3);
		assert(plateau3.getIdPion(32) == 17 && jeu2.getJoueur(4).getReserve() == 3);
		assert(plateau3.getIdPion(80) == 21 && jeu2.getJoueur(5).getReserve() == 3);
		cout << "demarrer valide !" << endl;

		jeu2.eliminerPion(1);
		jeu2.eliminerPion(9);
		const Plateau& plateau4 = jeu2.getPlateau();
		assert(plateau4.getIdPion(0) == 0 && jeu2.getJoueur(0).getReserve() == 4);
		assert(plateau4.getIdPion(48) == 0 && jeu2.getJoueur(2).getReserve() == 4);
		cout << "eliminerPion valide !" << endl;

		assert(jeu.avancerPion(3, 1));
		assert(jeu.avancerPion(13, 13));
		const Plateau& plateau5 = jeu.getPlateau();
		assert(plateau5.getIdPion(3) == 1);
		assert(plateau5.getIdPion(61) == 13);
		assert(jeu.avancerPion(7, 13));
		const Plateau& plateau6 = jeu.getPlateau();
		assert(plateau6.getIdPion(3) == 0 && jeu.getJoueur(0).getReserve() == 4);
		assert(plateau6.getIdPion(4) == 13);
		cout << "avancerPion valide !" << endl;

		int pos1 = jeu.getPion(9).getPos(), pos2 = jeu.getPion(13).getPos();
		assert(pos1 == 32 && pos2 == 4 && jeu.getPion(9).estPieu());
		assert(!jeu.permutter(13, 9));
		assert(jeu.permutter(9, 13));
		assert(jeu.getPion(9).getPos() == pos2 && jeu.getPion(13).getPos() == pos1 && !jeu.getPion(9).estPieu());
		cout << "permutter valide !" << endl;

		for (int i = 0 ; i < 3 ; i+=2) {
			assert(!jeu.partieGagnee());
			for (int j = 0 ; j < 4 ; j++) jeu.joueurs[i].setMaison(j, 2);
		}
		assert(jeu.partieGagnee());
		cout << "partieGagnee valide !" << endl;

		for (int i = 0 ; i < 4 ; i++) {
			joueur2.retirerCarte(0, i);
		}
		Carte* carte1 = new Carte(1);
		Carte* carte2 = new Carte(2);
		joueur2.piocherCarte(carte1);
		for (int i = 0 ; i < 3 ; i++) {
			joueur2.piocherCarte(carte2);
		}
		assert(jeu.carteJouable(1, 1));
		assert(!jeu.carteJouable(1, 2));
		assert(!jeu.carteJouable(1, 3));
		cout << "carteJouable valide !" << endl;

		assert(jeu.peutJouer(1));
		joueur2.retirerCarte(1);
		joueur2.piocherCarte(carte2);
		assert(!jeu.peutJouer(1));
		cout << "peutJouer valide !" << endl;
		
		delete carte1;
		delete carte2;
	}
	cout << "Destructeur valide !" << endl;
}