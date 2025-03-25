//Gérer permutter infini avec la défausse et finir la gestion rentrerDansMaison
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

const Pion& Jeu::getPion(int id_pion) const {
	assert(0 < id_pion && id_pion <= 4*nbJoueurs);
	return pions[id_pion-1];
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
            joueurs[i].piocherCarte(&pioche.getCarte(random_int));
            indice_carte[4*i+j] = random_int;
        }
    }
}

void Jeu::echangerCartes(int indJ1, int indJ2, int val_carteJ1, int val_carteJ2) {
	assert((indJ1 == 0 && indJ2 == 2) || (indJ1 == 1 && indJ2 == 3) || (indJ1 == 4 && indJ2 == 5 && nbJoueurs == 6));
	Carte* carteJ1 = joueurs[indJ1].retirerCarte(val_carteJ1);
	Carte* carteJ2 = joueurs[indJ2].retirerCarte(val_carteJ2);
	joueurs[indJ1].piocherCarte(carteJ2);
	joueurs[indJ2].piocherCarte(carteJ1);
}

bool Jeu::defausserCarte(int val_carte, int couleur) {
	assert(1 <= couleur && couleur <= nbJoueurs);
	Carte* carte = joueurs[couleur-1].retirerCarte(val_carte);
	if (carte == nullptr) return false;
	pioche.setTas(carte);
	return true;
}

void Jeu::eliminerPion(int id_pion) {
	assert(1 <= id_pion && id_pion <= 4*nbJoueurs);
	Pion &pion = pions[id_pion-1];
	plateau.viderCase(pion.getPos());
	pion.setPos(-1);
	pion.setPieu(true);
	joueurs[(id_pion-1)/4].setReserve(1);
}

bool Jeu::demarrer(int couleur, bool test) {
	if (joueurs[couleur-1].getReserve() == 0) return false;
	int id_pion = 0;
	for (int i = 4*(couleur-1) ; i < 4*couleur ; i++) {
		if (pions[i].getPos() == -1) {
			id_pion = i+1;
			break;
		}
	}
	int case_dep = plateau.getCasesDepart(couleur);
	int id_pion_tmp = plateau.getIdPion(case_dep);
	if (id_pion_tmp != 0) {
		if (pions[id_pion_tmp-1].estPieu()) return false;
		else if (!test) eliminerPion(id_pion_tmp);
	}
	if (!test) {
		joueurs[couleur-1].setReserve(-1);
		pions[id_pion-1].setPos(case_dep);
		plateau.setPion(id_pion, case_dep);
	}
	return true;
}

bool Jeu::avancerPion(int val_carte, int id_pion, bool test) {
	assert(1 <= id_pion && id_pion <= 4*nbJoueurs);
	assert((val_carte == -4 || (1 <= val_carte && val_carte <= 13 && val_carte != 11 && val_carte != 4)));
	
	Pion &pion = pions[id_pion-1];
	int position = pion.getPos();
	if (position == -1) return false;
	if (position == -2) return avancerMaison(val_carte, id_pion, test);
	
	int nb_cases = plateau.getNbCase();
	int a_eliminer[4*nbJoueurs-1] = {0};
	int nb_elimines = 0;
	int i_deb = position+1, i_fin = position+val_carte;
	if (val_carte == -4) {i_deb = i_fin; i_fin = position-1;}
	
	for (int i = i_deb ; i <= i_fin ; i++) {
		int id_tmp = plateau.getIdPion(i%nb_cases);
		if (id_tmp != 0) {
			if (pions[id_tmp-1].estPieu()) {
				return false;
			} else if (val_carte == 7 || i == position+val_carte) {
				a_eliminer[nb_elimines] = plateau.getIdPion(i%nb_cases);
				nb_elimines++;
			}
		}
	}
	if (!test) {
		for (int i = 0 ; i < nb_elimines ; i++) {
			eliminerPion(a_eliminer[i]);
		}
		int new_pos = (position+val_carte)%nb_cases;
		pion.setPieu(false);
		pion.setPos(new_pos);
		plateau.setPion(plateau.viderCase(position), new_pos);
	}
	return true;
}

bool Jeu::avancerMaison(int val_carte, int id_pion, bool test) {
	assert(1 <= id_pion && id_pion <= 4*nbJoueurs);
	if (!(0 < val_carte && val_carte <= 4)) return false;
	int i_deb = 0, couleur = (id_pion-1)/nbJoueurs;
	const int* mais = joueurs[couleur-1].getMaison();
	Pion pion = pions[id_pion-1];
	if (pion.getPos() == -2) {
		for (int i = 0 ; i < val_carte ; i++) {
			if (mais[i] == id_pion) {
				i_deb = i+1;
				break;
			}
		}
	}
	if (i_deb + val_carte > 4) return false;

	for (int i = i_deb ; i < i_deb + val_carte ; i++) {
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
		joueurs[couleur-1].setMaison(i_deb+val_carte-1, id_pion);
	}
	return true;
}

bool Jeu::permutter(int id_pion1, int id_pion2, bool test) {
	assert(0 < id_pion1 && id_pion1 <= 4*nbJoueurs && 0 < id_pion2 && id_pion2 <= 4*nbJoueurs && id_pion1 != id_pion2);
	if (pions[id_pion1-1].getPos() < 0) return false;
	if (pions[id_pion2-1].estPieu()) return false;
	if (!test) {
		Pion &pion1 = pions[id_pion1-1], &pion2 = pions[id_pion2-1];
		int pos1 = pion1.getPos(), pos2 = pion2.getPos();
		pion1.setPieu(false);
		pion1.setPos(pos2);
		pion2.setPos(pos1);
		plateau.viderCase(pos1);
		plateau.viderCase(pos2);
		plateau.setPion(id_pion1, pos2);
		plateau.setPion(id_pion2, pos1);
	}
	return true;
}

bool Jeu::partieGagnee() {
	if ((joueurs[0].maisonRemplie() && joueurs[2].maisonRemplie()) || 
	(joueurs[1].maisonRemplie() && joueurs[3].maisonRemplie()) ||
	(nbJoueurs == 6 && joueurs[4].maisonRemplie() && joueurs[5].maisonRemplie())) return true;
	return false;
}

bool Jeu::jouerCarte(int val_carte, int couleur, bool joker) {
	assert(val_carte == -4 || (-1 <= val_carte && val_carte <= 13 && val_carte != 0 && val_carte != 4));
	assert(1 <= couleur && couleur <= nbJoueurs);
	int id_pion = 0;
	if (val_carte == 11) {
		do {
			cout << "\nId du pion à permutter (pion du joueur) : ";
			cin >> id_pion;
		} while (id_pion < 1 || id_pion > 4*nbJoueurs || pions[id_pion-1].getPos() < 0 || (id_pion-1)/4 != couleur-1);
		int id_pion2;
		do {
			cout << "\nId du deuxième pion avec lequel permutter : ";
			cin >> id_pion2;
		} while (id_pion2 < 1 || id_pion2 > 4*nbJoueurs || pions[id_pion2-1].estPieu());
		if (!permutter(id_pion, id_pion2)) return false;
	} else if (val_carte == -1) {
		do {
			cout << "\nValeur désirée pour le joker : ";
			cin >> val_carte;
		} while (val_carte != -4 && (val_carte < 1 || val_carte > 13));
		return jouerCarte(val_carte, couleur, true);
	} else if (val_carte == 1 || val_carte == 10 || val_carte == 13) {
		char choix;
		do {
			cout << "\nUtiliser la carte comme démarrer(D) ou avancer(A) : ";
			cin >> choix;
		} while (choix != 'D' && choix != 'A');
		if (choix == 'D' && !demarrer(couleur)) return false;
		else if (choix == 'A') {
			do {
				cout << "\nId du pion à avancer : ";
				cin >> id_pion;
			} while (id_pion < 1 || id_pion > 4*nbJoueurs || (id_pion-1)/4 != couleur-1);
			if (!avancerPion(val_carte, id_pion)) return false;
		}
	} else {
		do {
			cout << "\nId du pion à avancer : ";
			cin >> id_pion;
		} while (id_pion < 1 || id_pion > 4*nbJoueurs || (id_pion-1)/4 != couleur-1);
		if (!avancerPion(val_carte, id_pion)) return false;
	}
	if (joker) val_carte = -1;
	pioche.setTas(joueurs[couleur-1].retirerCarte(val_carte));
	return true;
}

/*bool Jeu::carteJouable(int couleur, int val_carte) {
	assert(1 <= couleur && couleur <= nbJoueurs);
	assert(val_carte == -4 || (-1 <= val_carte && val_carte <= 13 && val_carte != 0 && val_carte != 4));
	Carte* carte = joueurs[couleur-1].retirerCarte(val_carte);
	if (carte == nullptr) return false;
	for (int i = 0 ; i < 4 ; i++) {
		Carte* carte_tmp = joueurs[couleur-1].getCarte(i);
		if (carte_tmp == nullptr) continue;
		val = carte_tmp->getValeur();
		if (val == -1) {
			cartes[nb_cartes] = -1;
			nb_cartes++;
		}
		else {
			for (int j = 0 ; j < 4 ; j++) {
				int id_pion = pions[i*4+j].getId();
				switch (val)
				{
				case 11:
					for (int id_pion2 = 1 ; id_pion2 <= 4*nbJoueurs ; id_pion2++) {
						if (id_pion2 == id_pion) continue;
						if (permutter(id_pion, id_pion2, true)) car
					}
				
				case 1:
				case 10: 
				case 13:
					
					break;
				
				default:
					break;
				}
			}
		}
	}

	return true;
}*/

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

		jeu.distribuer();
		cout << "distribuer valide !" << endl;
		
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
	}
	cout << "Destructeur valide !" << endl;
}