
#include "Affichage.h"

using namespace std;

void affichage_textuel(const Jeu & jeu){
    cout<<jeu.getPlateau().getPion(0).getId();
    /*
    for (int i = 0; i<jeu.getPlateau().getNbCase()/4; i++){
        cout << jeu.getPlateau().getPion(i).getId() << " ";
    }*/
}