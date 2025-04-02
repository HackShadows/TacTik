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

	/* Début de l'espace modifiable */	
	
	int vainqueurs = jouer(true);
	int j1 = 4, j2 = 5;
	if (vainqueurs < 5) {
		j1 = (vainqueurs+3)%4;
		j2 = (vainqueurs+1)%4;
	}
	cout << "\nLes " << intToStr(j1) << "s et " << intToStr(j2) << "s ont gagné !\n" << endl;
	
	/* Fin de l'espace modifiable */	
	return 0;
}