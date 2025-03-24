
#include "Affichage.h"
#include <iostream>
#include <cassert>

using namespace std;

void affichageId(int id){
    if (id/10 == 0) {
        cout << id << "  ";
    }
    else {
        cout << id << " ";
    }
}


void affichageMaison(const Jeu & jeu, int couleur) {
    for (int i = 0; i < 4; i++) {
        if (jeu.getJoueur(couleur-1).getMaison()[i] == false) {
            cout << "0 ";
        }
        else {
            cout << "1 ";
        }
    }
}



void ligneHaut(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 8*(nbJ-2); i++){
        affichageId(jeu.getPlateau().getIdPion(i));  //i;
    }
    cout << endl;
}

void maisonHaut(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    affichageId(jeu.getPlateau().getIdPion(nbCase-1));  //63
    if (jeu.getNbJoueurs() == 4) {
        cout << "  " << "Vert : ";
        affichageMaison(jeu, 1);
        cout << "     " << "Rouge : ";
        affichageMaison(jeu, 2);
        cout << "    ";
    }
    else {
        cout << "  Vert : ";
        affichageMaison(jeu, 1);
        cout << "                  Rouge : ";
        affichageMaison(jeu, 2);
        cout << "                 Noir : ";
        affichageMaison(jeu, 5);
        cout << "       ";
    }
    affichageId(jeu.getPlateau().getIdPion(8*(nbJ-2))); //16
    cout << endl;
}

void reserveHaut(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    affichageId(jeu.getPlateau().getIdPion(nbCase-2)); //62
    if (jeu.getNbJoueurs() == 4) {
        cout << "  " << "Réserve : " << jeu.getJoueur(0).getReserve() << "         ";
        cout << "Réserve : " << jeu.getJoueur(1).getReserve() << "         ";
    }
    else {
        cout << "  Réserve : " << jeu.getJoueur(0).getReserve();
        cout << "                      Réserve : " << jeu.getJoueur(1).getReserve();
        cout << "                      Réserve : " << jeu.getJoueur(4).getReserve();
        cout << "           ";
    }
    affichageId(jeu.getPlateau().getIdPion(8*(nbJ-2)+1)); //62
    cout << endl;
}

void milieu(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 12; i++) {
        affichageId(jeu.getPlateau().getIdPion(nbCase-3-i));  // 61-i
        for (int j = 0; j < 8*(nbJ-2)-2; j++) {
            cout << "   ";
        }
        affichageId(jeu.getPlateau().getIdPion(8*(nbJ-2)+2+i)); // 18+i
        cout << endl;
    }
}


void reserveBas(const Jeu & jeu, int nbCase) {
    affichageId(jeu.getPlateau().getIdPion(nbCase-15)); //49
    if (jeu.getNbJoueurs() == 4){
        cout << "  " << "Réserve : " << jeu.getJoueur(3).getReserve() << "         ";
        cout << "Réserve : " << jeu.getJoueur(2).getReserve() << "         ";
    }
    else {
        cout << "  Réserve : " << jeu.getJoueur(5).getReserve();
        cout << "                      Réserve : " << jeu.getJoueur(3).getReserve();
        cout << "                      Réserve : " << jeu.getJoueur(2).getReserve();
        cout << "           ";
    }
    affichageId(jeu.getPlateau().getIdPion((nbCase-1)/2-1)); //30
    cout << endl;
}


void maisonBas(const Jeu & jeu, int nbCase) {
    affichageId(jeu.getPlateau().getIdPion(nbCase-16)); // 48
    if (jeu.getNbJoueurs() == 4) {
        cout << "  " << "Bleu : ";
        affichageMaison(jeu, 4);
        cout << "     " << "Jaune : ";
        affichageMaison(jeu, 3);
        cout << "    ";
    }
    else {
        cout << "  Blanc : ";
        affichageMaison(jeu, 6);
        cout << "                 Jaune : ";
        affichageMaison(jeu, 4);
        cout << "                 Bleu : ";
        affichageMaison(jeu, 3);
        cout << "       ";
    }
    affichageId(jeu.getPlateau().getIdPion(nbCase/2-1));  // 31
    cout << endl;
}


void ligneBas(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 8*(nbJ-2); i++) {
        affichageId(jeu.getPlateau().getIdPion(nbCase -17 -i));  //47-i
    }
    cout << endl;
}



void grille(const Jeu & jeu, int nbCase) {
    ligneHaut(jeu, nbCase);
    maisonHaut(jeu, nbCase);
    reserveHaut(jeu, nbCase);
    milieu(jeu, nbCase);
    reserveBas(jeu, nbCase);
    maisonBas(jeu, nbCase);
    ligneBas(jeu, nbCase);
}



void affichageCarte(const Jeu & jeu) {
    for (int i = 0; i < jeu.getNbJoueurs(); i++) {
        cout << "Les cartes du joueur " << jeu.getJoueur(i).getCouleur() << endl;
        for (int j = 0; j < 4; j++) {
            if(jeu.getJoueur(i).getCarte(j) != nullptr) {
                cout << "Valeur : " << jeu.getJoueur(i).getCarte(j)->getValeur() << endl;
            }
            else {
                cout << "La carte a déjà été jouée !" << endl;
            }
        }
    }
}



void affichageTexte(const Jeu & jeu){
    int nbCase = jeu.getPlateau().getNbCase();
    grille(jeu, nbCase);
    cout << endl;
    //affichageCarte(jeu);
}


