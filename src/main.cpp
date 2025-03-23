/**
* @brief Contient l'implémentation du jeu.
*/
#include "Affichage.h"
#include <iostream>

using namespace std;

int main(){
	int nbJoueurs;
	do {
		cout << "\nNombre de joueurs (4 ou 6) : ";
		cin >> nbJoueurs;
		cout << endl;
	} while (nbJoueurs != 4 && nbJoueurs != 6);
	Jeu jeu(nbJoueurs);
	
    affichageTexte(jeu);
    return 0;
}
