#ifdef _WIN32
#include <windows.h>
#endif

#include "controleur.h"
#include <iostream>

using namespace std;

int main(){
	#ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
	srand(time(NULL));
    // jouer(true);
    Jeu jeu(6);
    jeu.demarrer(1);
    jeu.demarrer(2);
    jeu.demarrer(3);
    jeu.demarrer(4);
    /*jeu.demarrer(5);
    jeu.demarrer(6);*/
    jeu.distribuer();
    jeu.avancerPion(2, 1);
    cout << jeu.getPlateau().getIdPion(0) << "\n";
	// A retirer
	ImageViewer image(jeu);
    image.afficher(jeu);
    return 0;
}
