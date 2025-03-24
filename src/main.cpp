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
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	int it = 0, val_carte, couleur;
	while (it < 10) {
		couleur = (nbJoueurs == 6) ? ordre[it%nbJoueurs]:it%nbJoueurs+1;
		cout << "\nTour de " << intToStr(couleur-1) << " :\n\n";
		affichageTexte(jeu, couleur-1);
		cout << "\nCarte à jouer : ";
		cin >> val_carte;
		if(!jeu.jouerCarte(val_carte, couleur)) jeu.defausserCarte(val_carte, couleur);
		it++;
	}
    return 0;
}
