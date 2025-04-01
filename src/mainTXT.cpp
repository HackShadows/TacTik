/**
* @brief Contient l'implémentation du jeu.
*/
#ifdef _WIN32
#include <windows.h>
#endif
#include "./txt/Affichage.h"
#include <iostream>
#include <ctime>

using namespace std;

int choixCarte(string message, const Joueur& joueur) {
	int val_carte = 0;
	do {
		cin.clear();
		cout << message;
		val_carte = cinProtection();
	} while (!joueur.estDansMain(val_carte));
	
	return val_carte;
}

void echangeDeCartes(Jeu& jeu) {
	int val_carte, couleur, nbJoueurs = jeu.getNbJoueurs();
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	int echange_carte[3] = {0, 0, 0};
		for (int i = 0 ; i < nbJoueurs/2 ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, -1);
			cout << "\nTour de " << intToStr(couleur-1) << " (Entrée pour continuer)" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			affichageTexte(jeu, couleur-1);
			cout << "\nTour de " << intToStr(couleur-1) << " :" << endl;
			val_carte = choixCarte("\nCarte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			echange_carte[i] = val_carte;
		}

		for (int i = nbJoueurs/2 ; i < nbJoueurs ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, -1);
			cout << "\nTour de " << intToStr(couleur-1) << " (Entrée pour continuer)" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			affichageTexte(jeu, couleur-1);
			cout << "\nTour de " << intToStr(couleur-1) << " :" << endl;
			val_carte = choixCarte("\nCarte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			
			int indJ1;
			if (nbJoueurs == 6) indJ1 = (i != 5) ? (couleur-1)-(nbJoueurs/2-1):4;
			else indJ1 = (couleur-1)-nbJoueurs/2;
			jeu.echangerCartes(indJ1, (couleur-1), echange_carte[((i!=5)?indJ1:2)], val_carte);
		}
}

void tourJoueur(Jeu& jeu, int couleur) {
	if (jeu.getJoueur(couleur-1).mainVide()) return ;
	char choix = 'o';
	int val_carte;
	bool peut_jouer = true, coequipier = (jeu.getJoueur(couleur-1).maisonRemplie());
	affichageTexte(jeu, -1);
	cout << "\nTour de " << intToStr(couleur-1) << " (Entrée pour continuer)" << endl;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	affichageTexte(jeu, couleur-1);
	cout << "\nTour de " << intToStr(couleur-1) << " :" << endl;
	if (!jeu.peutJouer(couleur, coequipier)) {
		cout << "Aucune carte ne peut être jouée. Défausser toutes les cartes ? (Oui(o) ; Non(n)) : ";
		cin >> choix;
		if (choix == 'o' || choix == 'O') {
			jeu.defausserJoueur(couleur);
			return ;
		}
		peut_jouer = false;
	}
	do {
		val_carte = choixCarte(((peut_jouer) ? "\nCarte à jouer : " : "\nCarte à défausser : "), jeu.getJoueur(couleur-1));

		if (!jeu.carteJouable(couleur, val_carte, coequipier) && peut_jouer) {
			cout << "\nCette carte ne peut pas être jouée ! Choisissez-en une autre." << endl;
			choix = 'n';
		} else choix = 'o';

	} while (choix == 'n');

	if (!jeu.carteJouable(couleur, val_carte, coequipier)) jeu.defausserCarte(val_carte, couleur);
	else jeu.jouerCarte(val_carte, couleur, coequipier, false);
}

int jouer(){
	srand(time(NULL));
	int nbJoueurs = 4;
	do {
		cout << "\nNombre de joueurs (4 ou 6) : ";
		nbJoueurs = cinProtection();
	} while (nbJoueurs != 4 && nbJoueurs != 6);
	
	Jeu jeu(nbJoueurs);
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	// Affichage du tableau ligne maison bas modifié à droite quand 2 chiffres dans maisons bas
	while (true) {
		jeu.distribuer();
		echangeDeCartes(jeu);
		/* 
		//Enlever le const de getJoueur
		Carte carte_tmp(-1);
		for (int i = 0 ; i < 4 ; i++) {
			for (int j = 0 ; j < nbJoueurs ; j++) {
				Joueur &joueur = jeu.getJoueur(j);
				joueur.piocherCarte(&carte_tmp);
		}}*/
		for (int i = 0 ; i < 4 ; i++) {
			for (int j = 0 ; j < nbJoueurs ; j++) {
				int couleur = (nbJoueurs == 6) ? ordre[j]:j+1;
				tourJoueur(jeu, couleur);
				if (jeu.partieGagnee()) return couleur;
			}
		}

	}
}

int main() {
	#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

	int vainqueurs = jouer();
	int j1 = 4, j2 = 5;
	if (vainqueurs < 5) {
		j1 = (vainqueurs+3)%4;
		j2 = (vainqueurs+1)%4;
	}
	cout << "\nLes " << intToStr(j1) << "s et " << intToStr(j2) << "s ont gagné !\n" << endl;
	return 0;
}