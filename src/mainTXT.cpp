/**
* @brief Contient l'implémentation du jeu.
*/
#include "./txt/Affichage.h"
#include <iostream>

using namespace std;

int main(){
	srand(time(NULL));
	int nbJoueurs = 6;
	do {
		cout << "\nNombre de joueurs (4 ou 6) : ";
		cin >> nbJoueurs;
		cout << endl;
	} while (nbJoueurs != 4 && nbJoueurs != 6);
	
	Jeu jeu(nbJoueurs);
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	int val_carte, couleur;
	while (true) {
		jeu.distribuer();
		int echange_carte[3] = {0, 0, 0};
		for (int i = 0 ; i < nbJoueurs/2 ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, couleur-1);
			cout << "\nTour de " << intToStr(couleur-1) << " :\n";
			do {
				cout << "\nCarte à donner à ton coéquipier : ";
				cin >> val_carte;
			} while (!jeu.getJoueur(i).estDansMain(val_carte));
			echange_carte[i] = val_carte;
		}
		
		for (int i = nbJoueurs/2 ; i < nbJoueurs ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, couleur-1);
			cout << "\nTour de " << intToStr(couleur-1) << " :\n";
			do {
				cout << "\nCarte à donner à ton coéquipier : ";
				cin >> val_carte;
			} while (!jeu.getJoueur(i).estDansMain(val_carte));
			jeu.echangerCartes(i, i-nbJoueurs/2, val_carte, echange_carte[i-nbJoueurs/2]);
		}

		for (int i = 0 ; i < 4 ; i++) {
			for (int j = 0 ; j < nbJoueurs ; j++) {
				couleur = (nbJoueurs == 6) ? ordre[j]:j+1;
				affichageTexte(jeu, couleur-1);
				cout << "\nTour de " << intToStr(couleur-1) << " :\n";
				do {
					cout << "\nCarte à jouer : ";
					cin >> val_carte;
				} while (!jeu.getJoueur(j).estDansMain(val_carte));
				if(!jeu.jouerCarte(val_carte, couleur)) jeu.defausserCarte(val_carte, couleur);
				if (jeu.partieGagnee()) return 0;
			}
		}
	}
}
