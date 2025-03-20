
#include "Jeu.h"

#include <iostream>
#include <cassert>
#include <stdlib.h>

using namespace std;


Jeu::Jeu(){
    nbJoueurs = 4;
    joueurs = new Joueur[nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i] = Joueur(i+1);
    }
    pioche = Pioche();
    plateau = Plateau(nbJoueurs);
  }

Jeu::Jeu(int nbJ){
    assert(nbJ == 4 || nbJ == 6);
    nbJoueurs = nbJ;
    joueurs = new Joueur[nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        joueurs[i] = Joueur(i+1);
    }
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

bool intInTab(int element, const int * tab, int taille) {
    for (int i = 0 ; i < taille ; i++) {
        if (tab[i] == element) return true;
    }
    return false;
}

void Jeu::distribuer(){
    int indice_carte[4*nbJoueurs];
    for (int i = 0; i<nbJoueurs; i++){
        int random_int;
        for (int j = 0; j<4; j++){
            do {
                random_int = rand()%54;
                joueurs[i].piocherCarte(j, pioche.getPile()[random_int]);
            } while (!intInTab(random_int, indice_carte));
            indice_carte[i] = random_int;
        }
    }
}

void Jeu::testRegression(){
    Jeu jeu;
    assert(jeu.nbJoueurs ==4);
    for (int i = 0; i < 52; i++) {
        cout << jeu.pioche.getPile()[i].getValeur();
        //assert(jeu.pioche.getPile()[i].getValeur() == i/4);
    }


    //jeu.distribuer();

}

