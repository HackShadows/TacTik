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
    //jouer(true);
	ImageViewer image(4, 0);
    //image.afficher();
    
	return 0;
}
