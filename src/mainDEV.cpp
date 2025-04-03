#ifdef _WIN32
#include <windows.h>
#endif

#include "./txt/AffichageConsole.h"
#include "./sdl/AffichageSDL.h"
#include <iostream>

using namespace std;

int main() {
	#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif

	srand(time(NULL));
	/* Début de l'espace modifiable */	
	
	//int vainqueurs = jouer(true);
	
	Jeu jeu(4);
	jeu.distribuer();
	affichageTexte(jeu, 7);
	IA j1(1);
	IA j2(2);
	IA j3(3);
	IA j4(4);
	vector<pair<int, int>> vect1 = j1.genererCoups(jeu);
	for (auto val : vect1) cout << '(' << val.first << " ; " << val.second << ')';
	cout << endl;
	vector<pair<int, int>> vect2 = j2.genererCoups(jeu);
	for (auto val : vect2) cout << '(' << val.first << " ; " << val.second << ')';
	cout << endl;
	vector<pair<int, int>> vect3 = j3.genererCoups(jeu);
	for (auto val : vect3) cout << '(' << val.first << " ; " << val.second << ')';
	cout << endl;
	vector<pair<int, int>> vect4 = j4.genererCoups(jeu);
	for (auto val : vect4) cout << '(' << val.first << " ; " << val.second << ')';

	int vainqueurs = 1;
	int joueur1 = 4, joueur2 = 5;
	if (vainqueurs < 5) {
		joueur1 = (vainqueurs+3)%4;
		joueur2 = (vainqueurs+1)%4;
	}
	cout << "\nLes " << intToStr(joueur1) << "s et " << intToStr(joueur2) << "s ont gagné !\n" << endl;
	
	/* Fin de l'espace modifiable */	
	return 0;
}