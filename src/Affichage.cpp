
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



void ligneHaut4p(const Jeu & jeu) {
    for (int i = 0; i < 16; i++){
        affichageId(jeu.getPlateau().getIdPion(i));  //i;
    }
    cout << endl;
}

void maisonHaut4p(const Jeu & jeu) {
    affichageId(jeu.getPlateau().getIdPion(63));  //63
    cout << "  " << "Maison : ";
    affichageMaison(jeu, 1);
    cout << "   " << "Maison : ";
    affichageMaison(jeu, 2);
    cout << "   ";
    affichageId(jeu.getPlateau().getIdPion(16)); //16
    cout << endl;
}

void reserveHaut4p(const Jeu & jeu) {
    affichageId(jeu.getPlateau().getIdPion(62)); //62
    cout << "  " << "Réserve : " << jeu.getJoueur(0).getReserve() << "         ";
    cout << "Réserve : " << jeu.getJoueur(1).getReserve() << "         ";
    affichageId(jeu.getPlateau().getIdPion(17)); //17
    cout << endl;
}

void milieu4p(const Jeu & jeu) {
    for (int i = 0; i < 12; i++) {
        affichageId(jeu.getPlateau().getIdPion(61-i));  // 61-i
        for (int j = 0; j < 14; j++) {
            cout << "   ";
        }
        affichageId(jeu.getPlateau().getIdPion(18+i)); // 18+i
        cout << endl;
    }
}

void reserveBas4p(const Jeu & jeu) {
    affichageId(jeu.getPlateau().getIdPion(49)); //49
    cout << "  " << "Réserve : " << jeu.getJoueur(3).getReserve() << "         ";
    cout << "Réserve : " << jeu.getJoueur(2).getReserve() << "         ";
    affichageId(jeu.getPlateau().getIdPion(30)); //30
    cout << endl;
}


void maisonBas4p(const Jeu & jeu) {
    affichageId(jeu.getPlateau().getIdPion(48)); // 48
    cout << "  " << "Maison : ";
    affichageMaison(jeu, 4);
    cout << "   " << "Maison : ";
    affichageMaison(jeu, 3);
    cout << "   ";
    affichageId(jeu.getPlateau().getIdPion(31));  // 31
    cout << endl;
}

void ligneBas4p(const Jeu & jeu) {
    for (int i = 0; i < 16; i++){
        affichageId(jeu.getPlateau().getIdPion(47-i));  //47-i
    }
    cout << endl;
}


void ligneHaut6p(const Jeu & jeu) {
    for (int i = 0; i < 32; i++){
        affichageId(jeu.getPlateau().getIdPion(i));  //i;
    }
    cout << endl;
}


void maisonHaut6p(const Jeu & jeu) {
    affichageId(jeu.getPlateau().getIdPion(95)); // 95
    cout << "  Maison : ";
    affichageMaison(jeu, 1);
    cout << "                Maison : ";
    affichageMaison(jeu, 2);
    cout << "                Maison : ";
    affichageMaison(jeu, 3);
    cout << "     ";
    affichageId(jeu.getPlateau().getIdPion(32)); //32
    cout << endl;
}


void reserveHaut6p(const Jeu & jeu) {
    affichageId(jeu.getPlateau().getIdPion(94)); // 94
    cout << "  Réserve : " << jeu.getJoueur(0).getReserve();
    cout << "                      Réserve : " << jeu.getJoueur(1).getReserve();
    cout << "                      Réserve : " << jeu.getJoueur(2).getReserve();
    cout << "           ";
    affichageId(jeu.getPlateau().getIdPion(33)); //33
    cout << endl;
}


void milieu6p(const Jeu & jeu) {
    for (int i = 0; i < 12; i++) {
        affichageId(jeu.getPlateau().getIdPion(93-i));  // 93-i
        for (int j = 0; j < 30; j++) {
            cout << "   ";
        }
        affichageId(jeu.getPlateau().getIdPion(34+i)); // 34+i
        cout << endl;
    }
}

void reserveBas6p(const Jeu & jeu) {
    affichageId(jeu.getPlateau().getIdPion(81)); // 81
    cout << "  Réserve : " << jeu.getJoueur(5).getReserve();
    cout << "                      Réserve : " << jeu.getJoueur(4).getReserve();
    cout << "                      Réserve : " << jeu.getJoueur(3).getReserve();
    cout << "           ";
    affichageId(jeu.getPlateau().getIdPion(46)); // 46
    cout << endl;
}


void maisonBas6p(const Jeu & jeu) {
    affichageId(jeu.getPlateau().getIdPion(80));  // 80
    cout << "  Maison : ";
    affichageMaison(jeu, 6);
    cout << "                Maison : ";
    affichageMaison(jeu, 5);
    cout << "                Maison : ";
    affichageMaison(jeu, 4);
    cout << "     ";
    affichageId(jeu.getPlateau().getIdPion(47));  // 47
    cout << endl;
}


void ligneBas6p(const Jeu & jeu) {
    for (int i = 0; i < 32; i++){
        affichageId(jeu.getPlateau().getIdPion(79-i));  //79+i
    }
    cout << endl;
}

void grille4p(const Jeu & jeu) {
    ligneHaut4p(jeu);
    maisonHaut4p(jeu);
    reserveHaut4p(jeu);
    milieu4p(jeu);
    reserveBas4p(jeu);
    maisonBas4p(jeu);
    ligneBas4p(jeu);
}


void grille6p(const Jeu & jeu) {
    ligneHaut6p(jeu);
    maisonHaut6p(jeu);
    reserveHaut6p(jeu);
    milieu6p(jeu);
    reserveBas6p(jeu);
    maisonBas6p(jeu);
    ligneBas6p(jeu);
}


void affichageCarte(const Jeu & jeu) {
    for (int i = 0; i < jeu.getNbJoueurs(); i++) {
        cout << "Les cartes du joueur " << jeu.getJoueur(i).getCouleur() << endl;
        for (int j = 0; j < 4; j++) {
            if(jeu.getJoueur(i).getCarte(j) != nullptr) {
                cout << "Valeur : " << jeu.getJoueur(i).getCarte(j)->getValeur() << endl;
            }
            else {
                cout << "La carte n'a pas été définie !" << endl;
            }
        }
    }
}



void affichageTexte(const Jeu & jeu){
    if (jeu.getNbJoueurs() == 4) {
        grille4p(jeu);
    }
     else{
        grille6p(jeu);
    }
    cout << endl;
    //affichageCarte(jeu);
}


