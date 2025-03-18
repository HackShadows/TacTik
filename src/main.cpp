/**
* @brief Contient l'implémentation du jeu.
*/
#include "Carte.h"
#include "Joueur.h"
#include "Pion.h"
#include "Pioche.h"
#include "Plateau.h"
#include "Jeu.h"
#include "Affichage.h"
#include <iostream>

using namespace std;

int main(){
    cout<<"Hello world !\n";
    Jeu jeu(4);
    affichage_textuel(jeu);
    return 0;
}
