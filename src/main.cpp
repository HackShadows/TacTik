/**
* @brief Contient l'implémentation du jeu.
*/
#include "Affichage.h"
#include <iostream>

using namespace std;

int main(){
    cout<<"Hello world !\n";
    Jeu jeu(4);
    cout<<jeu.getNbJoueurs();
    //affichage_textuel(jeu);
    return 0;
}
