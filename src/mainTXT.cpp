/**
* @brief Contient l'implémentation du jeu.
*/
#include "./txt/Affichage.h"
#include <iostream>

using namespace std;

int choixCarte(string message, const Joueur& joueur) {
	int val_carte = 0;
	do {
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
			affichageTexte(jeu, couleur-1);
			cout << "Tour de " << intToStr(couleur-1) << " :\n";
			val_carte = choixCarte("\nCarte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			echange_carte[i] = val_carte;
		}

		for (int i = nbJoueurs/2 ; i < nbJoueurs ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, couleur-1);
			cout << "Tour de " << intToStr(couleur-1) << " :\n";
			val_carte = choixCarte("\nCarte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			
			int indJ1;
			if (nbJoueurs == 6) indJ1 = (i != 5) ? (couleur-1)-(nbJoueurs/2-1):4;
			else indJ1 = (couleur-1)-nbJoueurs/2;
			jeu.echangerCartes(indJ1, (couleur-1), echange_carte[((i!=5)?indJ1:2)], val_carte);
		}
}

void tourJoueur(Jeu& jeu, int couleur) {
	int val_carte;
	affichageTexte(jeu, couleur-1);
	cout << "Tour de " << intToStr(couleur-1) << " :\n";
	char choix = 'o';
	do {
		val_carte = choixCarte("\nCarte à jouer : ", jeu.getJoueur(couleur-1));

		if (!jeu.carteJouable(couleur, val_carte)) {
			cout << "\nLa carte ne peut être jouée.\nDéfausser la carte ? (Oui(o) ; Non(n)) : ";
			cin >> choix;
		} else choix = 'o';

	} while (choix == 'n' || choix == 'N');

	if (!jeu.carteJouable(couleur, val_carte)) jeu.defausserCarte(val_carte, couleur);
	else jeu.jouerCarte(val_carte, couleur);
}

int main(){
	srand(time(NULL));
	int nbJoueurs = 4;
	do {
		cout << "\nNombre de joueurs (4 ou 6) : ";
		if(!(cin >> nbJoueurs)) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			nbJoueurs = 0;
		}
	} while (nbJoueurs != 4 && nbJoueurs != 6);
	
	Jeu jeu(nbJoueurs);
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	//int casser = -1, nb_pass = 0, passer[6] = {0}; Implémenter peutJouer + défausser toutes les cartes
	while (true) {
		jeu.distribuer();
		echangeDeCartes(jeu);
		/*Joueur &joueur = jeu.getJoueur(0);
		Carte carte_tmp(-1);
		for (int i = 0 ; i < 4 ; i++) {
			joueur.retirerCarte(0, i);
			joueur.piocherCarte(&carte_tmp);
		}*/
		for (int i = 0 ; i < 4 ; i++) {
			for (int j = 0 ; j < nbJoueurs ; j++) {
				int couleur = (nbJoueurs == 6) ? ordre[j]:j+1;
				tourJoueur(jeu, couleur);
				if (jeu.partieGagnee()) return 0;
			}
		}

	}
}
