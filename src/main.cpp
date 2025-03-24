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
    jeu.distribuer();
    affichageTexte(jeu);
	cout << "'Entrée' pour passer à l'étape suivante" << endl;
	cin.get();
	cin.get();
	/*
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	if (nbJoueurs == 4) {
		for (int i = 0 ; i < nbJoueurs ; i++) {
			jeu.demarrer(i+1);
			affichageTexte(jeu);
			cout << "'Entrée' pour passer à l'étape suivante" << endl;
			cin.get();
		}
	} else {
		for (int i : ordre) {
			jeu.demarrer(i);
			affichageTexte(jeu);
			cout << "'Entrée' pour passer à l'étape suivante" << endl;
			cin.get();
		}
	}
	
	jeu.avancerPion(3, 1);
	affichageTexte(jeu);
	cout << "'Entrée' pour passer à l'étape suivante" << endl;
	cin.get();
	jeu.avancerPion(13, 13);
	affichageTexte(jeu);
	cout << "'Entrée' pour passer à l'étape suivante" << endl;
	cin.get();
	jeu.avancerPion(7, 13);
	affichageTexte(jeu);*/
	int it = 0, val_carte, couleur;
	while (it < 10) {
		couleur = it%nbJoueurs+1;
		cout << "\nTour de " << intToStr(couleur-1) << " :";
		cout << "\nCarte à jouer : ";
		cin >> val_carte;
		if(!jeu.jouerCarte(val_carte, couleur)) jeu.defausserCarte(val_carte, couleur);
		affichageTexte(jeu);
		it++;
	}
    return 0;
}
