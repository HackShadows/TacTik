
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
    cout<<"BOOOOOOOOOOOOOM";
    delete [] joueurs;
    joueurs = nullptr;
    cout<<"BOOOOOOOOOOOOOM";
}

Plateau Jeu::getPlateau() const {
    return plateau;
}

int Jeu::getNbJoueurs() const {
    return nbJoueurs;
}

void Jeu::distribuer(){
    for (int i = 0; i<nbJoueurs; i++){
        for (int j = 0; j<4; j++){
            int r = rand()%54;
            joueurs[i].piocherCarte(pioche.getPile()[r]);
        }
    }
}

void Jeu::testRegression(){
    Pioche pioche;
}