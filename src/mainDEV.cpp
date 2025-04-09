#ifdef _WIN32
#include <windows.h>
#endif

#include "controleur.h"
#include <iostream>

using namespace std;

int main() {
	#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

	srand(time(NULL));
	//int vainqueurs = jouer(true);
	
	/* Début de l'espace modifiable */	
	
	Jeu jeu(4);
	jeu.distribuer();
	affichageTexte(jeu, 7);
	IA ia;
	for (int j = 0 ; j < 4 ; j++) {
		for (int i = 0 ; i < 4 ; i++) {
			cout << intToStr(i) << " : ";
			vector<pair<int, int>> vect = ia.genererCoups(jeu, i+1);
			for (auto val : vect) cout << '(' << val.first << " ; " << val.second << ')';
			cout << endl;
		}
		
		cin.get();
		affichageTexte(jeu, 7);
	}

	/* Fin de l'espace modifiable */
		
	return 0;
}