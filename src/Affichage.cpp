
#include "Affichage.h"
#include <iostream>

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
        if (jeu.getJoueur(couleur).getMaison()[i] == false) {
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
    affichageId(63);
    cout << "  " << "vert : ";
    affichageMaison(jeu, 1);
    cout << "                           " << "rouge : ";
    affichageMaison(jeu, 2);
    affichageId(16);
    cout << endl;
}


void milieu4p(const Jeu & jeu) {
    for (int i = 0; i < 14; i++) {
        affichageId(63-i);  // 63-i
        for (int j = 0; j < 14; j++) {
            cout << "   ";
        }
        affichageId(16+i); // 16+i
        cout << endl;
    }
}

void maisonBas4p(const Jeu & jeu) {
    affichageId(47);
    cout << "  " << "jaune : ";
    affichageMaison(jeu, 4);
    cout << "                           " << "bleu : ";
    affichageMaison(jeu, 3);
    affichageId(32);
    cout << endl;
}

void ligneBas4p(const Jeu & jeu) {
    for (int i = 0; i < 16; i++){
        affichageId(jeu.getPlateau().getIdPion(47+i));  //47+i
    }
    cout << endl;
}


void ligneHaut6p(const Jeu & jeu) {
    for (int i = 0; i < 32; i++){
        affichageId(jeu.getPlateau().getIdPion(i));  //i;
    }
    cout << endl;
}


void ligneBas6p(const Jeu & jeu) {
    for (int i = 0; i < 32; i++){
        affichageId(jeu.getPlateau().getIdPion(79-i));  //79+i
    }
    cout << endl;
}

void maisonHaut6p(const Jeu & jeu) {
    affichageId(95);
    cout << "  Vert : ";
    affichageMaison(jeu, 1);
    cout << "                Rouge : ";
    affichageMaison(jeu, 2);
    cout << "                Bleu : ";
    affichageMaison(jeu, 3);
    affichageId(32);
    cout << endl;
}

void milieu6p(const Jeu & jeu) {
    for (int i = 0; i < 14; i++) {
        affichageId(jeu.getPlateau().getIdPion(94-i));  // 95-i
        for (int j = 0; j < 30; j++) {
            cout << "   ";
        }
        affichageId(jeu.getPlateau().getIdPion(32+i)); // 32+i
        cout << endl;
    }
}

void maisonBas6p(const Jeu & jeu) {
    affichageId(95);
    cout << "  Blanc : ";
    affichageMaison(jeu, 6);
    cout << "                Noir : ";
    affichageMaison(jeu, 5);
    cout << "                Jaune : ";
    affichageMaison(jeu, 4);
    affichageId(32);
    cout << endl;
}


void grille4p(const Jeu & jeu) {
    ligneHaut4p(jeu);
    maisonHaut4p(jeu);
    milieu4p(jeu);
    maisonBas4p(jeu);
    ligneBas4p(jeu);
}


void grille6p(const Jeu & jeu) {
    ligneHaut6p(jeu);
    maisonHaut6p(jeu);
    milieu6p(jeu);
    maisonBas6p(jeu);
    ligneBas6p(jeu);
}


void affichageCarte(const Jeu & jeu) {
    for (int i = 0; i < jeu.getNbJoueurs(); i++) {
        cout << "Les cartes du joueur " << jeu.getJoueurs().getCouleur() << endl;
        for (int j = 0; j < 4; j++) {
            cout << "Valeur : " << jeu.getJoueurs(i).getCarte(j).getValeur() << endl;
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
    //affichage_carte(jeu);
}


