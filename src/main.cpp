/**
* @brief Contient l'implémentation du jeu.
*/
#include "Affichage.h"
#include <iostream>

using namespace std;

int main(){
	srand(time(NULL));
	int nbJoueurs;
	do {
		cout << "\nNombre de joueurs (4 ou 6) : ";
		cin >> nbJoueurs;
		cout << endl;
	} while (nbJoueurs != 4 && nbJoueurs != 6);
	
	Jeu jeu(nbJoueurs);
    jeu.distribuer();
    affichageTexte(jeu);

	for (int i = 0 ; i < nbJoueurs ; i++) {
		jeu.demarrer(i+1);
		affichageTexte(jeu);
		cout << "'Entrée' pour passer à l'étape suivante" << endl;
		cin.get();
	}
    affichageTexte(jeu);
	jeu.avancerPion(3, 1);
	affichageTexte(jeu);
	cout << "'Entrée' pour passer à l'étape suivante" << endl;
	cin.get();
	jeu.avancerPion(13, 13);
	affichageTexte(jeu);
	cout << "'Entrée' pour passer à l'étape suivante" << endl;
	cin.get();
	jeu.avancerPion(7, 13);
	affichageTexte(jeu);
    return 0;
}
