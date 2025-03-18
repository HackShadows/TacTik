
#include "Jeu.h"
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


void Jeu::distribuer(){
    for (int i = 0; i<nbJoueurs; i++){
        for (int j = 0; j<4; j++){
            int r = rand()%54;
            joueurs[i].piocherCarte(pioche.getPile()[r]);
        }
    }
}