
#include "Jeu.h"

#include <iostream>
#include <cassert>
#include <stdlib.h>

using namespace std;


Jeu::Jeu(){
    nbJoueurs = 4;
    joueurs = new Joueur * [nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        *joueurs[i] = Joueur(i+1);
    }
    pioche = Pioche();
    plateau = Plateau(nbJoueurs);
  }

Jeu::Jeu(int nbJ){
    assert(nbJ == 4 || nbJ == 6);
    nbJoueurs = nbJ;
    joueurs = new Joueur * [nbJoueurs];
    for (int i = 0; i < nbJoueurs; i++) {
        *joueurs[i] = Joueur(i+1);
    }
    pioche = Pioche();
    plateau = Plateau(nbJ);
}

Jeu::~Jeu() {
    for (int i = 0 ; i < nbJoueurs ; i++) {
        delete joueurs[i];
    }
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
    for (int i = 0; i<nbJoueurs; i++) {
        int random_int;
        for (int j = 0 ; j < 4 ; j++) {
            do {
                random_int = rand()%54;
            } while (intInTab(random_int, indice_carte, 4*i + j));
            joueurs[i]->piocherCarte(j, &pioche.getCarte(random_int));
            indice_carte[4*i+j] = random_int;
        }
    }
}

void Jeu::testRegression(){
    Jeu jeu;
    assert(jeu.nbJoueurs == 4);
    cout << "Constructeur par défaut valide !" << endl;

    Jeu jeu2(6);
    assert(jeu2.nbJoueurs == 6);
    cout << "Constructeur avec paramètres valide !" << endl;

    Plateau plateau = jeu.getPlateau();
    assert(plateau.getNbCase() == 64);
    cout << "getPlateau valide !" << endl;

    int nbJ = jeu.getNbJoueurs();
    assert(nbJ == 4);
    cout << "getNbJoueurs valide !" << endl;

    jeu.distribuer();
    cout << "distribuer valide !" << endl;

    jeu.~Jeu();
    jeu2.~Jeu();
    assert(jeu.joueurs == nullptr && jeu2.joueurs == nullptr);
    cout << "Destructeur valide !" << endl;
}

