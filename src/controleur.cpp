#include "controleur.h"

#include <iostream>
#include <cassert>

using namespace std;


int cinProtectionInt(string coutMessage) {
	int val = 0;
	cout << "\n" + coutMessage;
    cin.clear();
	if(!(cin >> val)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		val = 0;
	}
	return val;
}

void message(string coutMessage) {cout << "\n" + coutMessage << endl;}

Controleur::Controleur() : jeu(), im(), versionGraphique(false) {}

/*Controleur::Controleur() : jeu(), versionGraphique(false) {}

Controleur::Controleur(int nbJ, int nbIA, bool affichageGraphique) : jeu(nbJ, nbIA), versionGraphique(affichageGraphique) {
	assert(nbIA >= 0 && nbJ >= 0 && (nbJ + nbIA == 4 || nbJ + nbIA == 6));
}*/

Controleur::Controleur(int nbJ, int nbIA, bool affichageGraphique) : jeu(nbJ, nbIA), im(nbJ, nbIA), versionGraphique(affichageGraphique) {
	assert(nbIA >= 0 && nbJ >= nbIA && (nbJ == 4 || nbJ == 6));
}

Controleur::~Controleur() {}

Jeu& Controleur::getJeu() {
	return jeu;
}

int Controleur::getIdPion(string coutMessage) {
	if (versionGraphique) return im.getIndicePionEvent(coutMessage);
    return saisirEntier(coutMessage);
}

int Controleur::saisirEntier(string coutMessage) {
	if (versionGraphique) return im.getEventNumber(coutMessage);
	return cinProtectionInt(coutMessage);
}

char Controleur::saisirCaractere(string coutMessage) {
	if (versionGraphique) return im.getEventChar(coutMessage);
	char val = '0';
	cout << "\n" + coutMessage;
    cin.clear();
	if(!(cin >> val)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		val = '0';
	}
	return val;
}

bool Controleur::jouerCarte(int valCarte, int couleur, void (message)(string), bool coequipier, bool joker) {
	int nbJoueurs = jeu.getNbJoueurs();
	assert(valCarte == -4 || (-1 <= valCarte && valCarte <= 13 && valCarte != 0 && valCarte != 4));
	assert(1 <= couleur && couleur <= nbJoueurs);
	int nb_possible = 0, idPion = 0, c1 = couleur;
	Joueur& j1 = jeu.getJoueurNonConst(couleur-1);
	if (coequipier) couleur = 1 + ((couleur < 5) ? (couleur+1)%4 : 10-couleur);
	Joueur& joueur = jeu.getJoueurNonConst(couleur-1);
	
	// Cas du permutter
	if (valCarte == 11) {
		for (int i = (couleur-1)*4 ; i < couleur*4 ; i++) {
			if (jeu.getPion(i+1).getPos() >= 0) {
				idPion = i+1;
				nb_possible++;
			}
		}
		if (nb_possible > 1) idPion = 0;
		nb_possible = 0;
		while (idPion < 1 || idPion > 4*nbJoueurs || jeu.getPion(idPion).getPos() < 0 || (idPion-1)/4 != couleur-1) idPion = getIdPion("Id du pion à permutter (pion du joueur) : ");
		int idPion2 = 0;
		while (idPion2 < 1 || idPion2 > 4*nbJoueurs || jeu.getPion(idPion2).estPieu() || idPion2 == idPion) idPion2 = getIdPion("Id du deuxième pion avec lequel permutter : ");
		if (!jeu.permutter(idPion, idPion2)) return false;
	} 
	
	// Cas du joker
	else if (valCarte == -1) {
		bool continuer = true;
		while (continuer) {
			do {
				valCarte = saisirEntier("Valeur désirée pour le joker : ");
			} while (valCarte != -4 && (valCarte < 1 || valCarte > 13 || valCarte == 4));
			if (!jeu.carteJouable(c1, valCarte, coequipier, true)) message("Action impossible ! Choisissez une autre valeur pour le joker.");
			else continuer = false;
		}
		
		return jouerCarte(valCarte, c1, message, coequipier, true);
	} 
	
	// Cas du démarrer
	else if (valCarte == 1 || valCarte == 10 || valCarte == 13) {
		char choix = '0';
		if (joueur.getReserve() == 4) choix = 'D';
		else if (!jeu.demarrer(couleur, true)) choix = 'A';
		else if (joueur.getReserve() > 0) {
			int nb = 0;
			for (int id = (couleur-1)*4+1 ; id <= 4*couleur ; id++) {
				if (jeu.avancerPion(valCarte, id, true)) {
					nb = 1;
					break;
				}
			}
			choix = (nb == 0) ? 'D':'0';
		}
		while (choix != 'D' && choix != 'A' && choix != 'd' && choix != 'a') choix = saisirCaractere("Utiliser la carte comme démarrer(D) ou avancer(A) : ");
		if ((choix == 'D' || choix == 'd') && !jeu.demarrer(couleur)) return false;
		else if (choix == 'A' || choix == 'a') {
			for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
				if (jeu.avancerPion(valCarte, i, true)) {
					idPion = i;
					nb_possible++;
				}
			}
			if (nb_possible == 0) return false;
			if (nb_possible > 1 ) idPion = 0;
			while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion("Id du pion à avancer : ");
			if (!jeu.avancerPion(valCarte, idPion)) return false;
		}
	} 
	
	// Cas du 7x1
	else if (valCarte == 7 && joueur.getReserve() < 3) {
		int val, somme = 0;
		for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
			val = 1;
			while (val < 7 && jeu.avancerPion(val, i, true)) val++;
			somme += val-1;
			if (val == 7 && jeu.avancerPion(val, i, true)) idPion = i;
		}
		if (somme < 7 && idPion == 0) return false;
		if (somme == 6 && !jeu.avancerPion(7, idPion)) return false;
		else if (somme == 6) ;
		else {
			somme = 0;
			while (somme < 7) {
				bool continuer = true;
				while (continuer) {
					idPion = 0;
					while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion("Id du pion à avancer : ");
					val = 0;
					while (val < 1 || somme + val > 7) val = saisirEntier("Nombre de cases à avancer : ");
					if (!jeu.avancerPion(val, idPion, true)) message("Ce déplacement est impossible !");
					else continuer = false;
				}
				jeu.avancerPion(val, idPion, false, true);
				somme += val;
			}
		}
	} 
	
	// Cas du avancer
	else {
		for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
			if (jeu.avancerPion(valCarte, i, true)) {
				idPion = i;
				nb_possible++;
			}
		}
		if (nb_possible == 0) return false;
		if (nb_possible > 1 ) idPion = 0;
		while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion("Id du pion à avancer : ");
		if (!jeu.avancerPion(valCarte, idPion)) return false;
	}
	
	// Affichage sur le tas
	if (joker) valCarte = -1;
	jeu.setTas(j1.retirerCarte(valCarte));
	return true;
}

int Controleur::choixCarte(string message, const Joueur& joueur) {
	int valCarte = 0;
    while (!joueur.estDansMain(valCarte)) valCarte = saisirEntier(message);	
	return valCarte;
}

void Controleur::echangeDeCartes() {
	int valCarte, couleur, nbJoueurs = jeu.getNbJoueurs();
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	int echange_carte[3] = {0, 0, 0};
		for (int i = 0 ; i < nbJoueurs/2 ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, -1);
			message("Tour de " + intToStr(couleur-1) + " (Entrée pour continuer)");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			affichageTexte(jeu, couleur-1);
			message("\nTour de " + intToStr(couleur-1) + " :");
			valCarte = choixCarte("Carte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			echange_carte[i] = valCarte;
		}

		for (int i = nbJoueurs/2 ; i < nbJoueurs ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, -1);
			message("Tour de " + intToStr(couleur-1) + " (Entrée pour continuer)");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			affichageTexte(jeu, couleur-1);
			message("\nTour de " + intToStr(couleur-1) + " :");
			valCarte = choixCarte("Carte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			
			int indJ1;
			if (nbJoueurs == 6) indJ1 = (i != 5) ? (couleur-1)-(nbJoueurs/2-1):4;
			else indJ1 = (couleur-1)-nbJoueurs/2;
			jeu.echangerCartes(indJ1, (couleur-1), echange_carte[((i!=5)?indJ1:2)], valCarte);
		}
}

void Controleur::tourJoueur(int couleur, bool dev) {
	if (jeu.getJoueur(couleur-1).mainVide()) return ;
	char choix = 'o';
	int valCarte;
	bool peut_jouer = true, coequipier = (jeu.getJoueur(couleur-1).maisonRemplie());
    IA ia;
	if (!dev) {
		affichageTexte(jeu, -1);
		message("Tour de " + intToStr(couleur-1) + " (Entrée pour continuer)");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
	}
    if (jeu.getJoueur(couleur-1).estIA()) ia.genererCoups(jeu, couleur);
    else {
        affichageTexte(jeu, couleur-1);
        message("\nTour de " + intToStr(couleur-1) + " :");
        if (!jeu.peutJouer(couleur, coequipier)) {
            choix = saisirCaractere("Aucune carte ne peut être jouée. Défausser toutes les cartes ? (Oui(o) ; Non(n)) : ");
            if (choix == 'o' || choix == 'O') {
                jeu.defausserJoueur(couleur);
                return ;
            }
            peut_jouer = false;
        }
        do {
            valCarte = choixCarte(((peut_jouer) ? "Carte à jouer : " : "Carte à défausser : "), jeu.getJoueur(couleur-1));

            if (!jeu.carteJouable(couleur, valCarte, coequipier) && peut_jouer) {
                message("Cette carte ne peut pas être jouée ! Choisissez-en une autre.");
                choix = 'n';
            } else choix = 'o';

        } while (choix == 'n');

        if (!jeu.carteJouable(couleur, valCarte, coequipier)) jeu.defausserCarte(valCarte, couleur);
        else jouerCarte(valCarte, couleur, message, coequipier);
    }
}

void Controleur::afficherVainqueur(int couleurVainqueur) {
	int vainqueurs = couleurVainqueur;
	int j1 = 4, j2 = 5;
	if (vainqueurs < 5) {
		j1 = (vainqueurs+3)%4;
		j2 = (vainqueurs+1)%4;
	}
	if (versionGraphique) {

	} else {
		cout << "\nLes " << intToStr(j1) << "s et " << intToStr(j2) << "s ont gagné !\n" << endl;
	}
}

void Controleur::afficherImage() {im.afficher();}

void jouer(bool versionGraphique, bool dev){
	srand(time(NULL));
	if (versionGraphique) {

	}
	int nbIA = -1, nbJoueurs = 0;
	
	while (nbJoueurs != 4 && nbJoueurs != 6) nbJoueurs = cinProtectionInt("Nombre de joueurs (4 ou 6) : ");

    while (nbIA < 0 || nbIA > nbJoueurs) nbIA = cinProtectionInt("Nombre d'IA parmis les joueurs (0-" + to_string(nbJoueurs) + ") : ");
	
	Controleur controleur(nbJoueurs, nbIA, versionGraphique);
	Jeu &jeu = controleur.getJeu();
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	while (true) {
		if (!dev) {
			jeu.distribuer();
			controleur.echangeDeCartes();
		} else {
			for (int i = 0 ; i < 4 ; i++) {
				for (int j = 0 ; j < nbJoueurs ; j++) {
					jeu.attribuerCarte(-1, j+1);
				}
			}
		}

		for (int i = 0 ; i < 4 ; i++) {
			for (int j = 0 ; j < nbJoueurs ; j++) {
				int couleur = (nbJoueurs == 6) ? ordre[j]:j+1;
				controleur.tourJoueur(couleur, dev);
				if (jeu.partieGagnee()) {
					affichageTexte(jeu, 7);
					return controleur.afficherVainqueur(couleur);
				}
			}
		}
	}
}