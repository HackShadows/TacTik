
#include "Jeu.h"

#include <iostream>
#include <cassert>

using namespace std;


Jeu::Jeu(){
    nbJoueurs = 4;
    joueurs = new Joueur[nbJoueurs];
    pioche = Pioche();
    plateau = Plateau(nbJoueurs);
  }

Jeu::Jeu(int nbJ){
    assert(nbJ == 4 || nbJ == 6);
    nbJoueurs = nbJ;
    joueurs = new Joueur[nbJoueurs];
    pioche = Pioche();
    plateau = Plateau(nbJ);
}

Jeu::~Jeu() {
    delete [] joueurs;
    joueurs = nullptr;
}

Plateau Jeu::getPlateau() const {
    return plateau;
}

int Jeu::getNbJoueurs() const {
    return nbJoueurs;
}

bool inTabInt(int element, const int * tab) {
    for (int i: tab) {
        if (tab[i] == element) {
            return true;
        }
    }
    return false;
}

void Jeu::distribuer(){
    int indice_carte[];
    for (int i = 0; i<nbJoueurs; i++){
        for (int j = 0; j<4; j++){
            int r = rand()%54;
            do {
                joueurs[i].piocherCarte(pioche.getPile()[r]);

            } while (!inTabInt(r, indice_carte));

        }
    }
}

void Jeu::testRegression(){
    Pioche pioche;
}

