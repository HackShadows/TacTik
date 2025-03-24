
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

string intToStr(int entier) {
    switch (entier) {
        case 0:
            return "Vert";
        case 1:
            return "Rouge";
        case 2:
            return "Bleu";
        case 3:
            return "Jaune";
        case 4:
            return "Noir";
        case 5:
            return "Blanc";
        default:
            return "";
    }
}

void affichageCarte(const Jeu & jeu, int indiceJoueur) {
    cout << "     Les cartes du joueur " << intToStr(indiceJoueur) << " : [ ";
    for (int j = 0; j < 4; j++) {
        if(jeu.getJoueur(indiceJoueur).getCarte(j) != nullptr) {
            cout << jeu.getJoueur(indiceJoueur).getCarte(j)->getValeur() << " ";
        }
    }
    cout << "]";
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
    affichageCarte(jeu, 0);
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
    affichageCarte(jeu, 1);
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
    if (nbJ == 6) {
        affichageCarte(jeu, 4);
    }
    cout << endl;
}

void milieu(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 12; i++) {
        affichageId(jeu.getPlateau().getIdPion(nbCase-3-i));  // 61-i
        if (i == 5) {
            for (int j = 0 ; j < 4*(nbJ-2)-2; j++) {
                cout << "   ";
            }
            Carte* tas = jeu.getPioche().getTas();
            if (tas == nullptr) cout << "0  ";
            else {
                int val = tas->getValeur();
                if (val < 0) cout << val;
                else affichageId(val);
            }
            for (int j = 4*(nbJ-2)-1; j < 8*(nbJ-2)-2; j++) {
                cout << "   ";
            }
        }
        else {
            for (int j = 0; j < 8*(nbJ-2)-2; j++) {
                cout << "   ";
            }
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
    if (nbCase/16 == 6) {
        affichageCarte(jeu, 2);
    }
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
    affichageCarte(jeu, 3);
    cout << endl;
}


void ligneBas(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 8*(nbJ-2); i++) {
        affichageId(jeu.getPlateau().getIdPion(nbCase -17 -i));  //47-i
    }
    if (jeu.getNbJoueurs() == 6) {
        affichageCarte(jeu, 5);
    }
    else {
        affichageCarte(jeu, 2);
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







void affichageTexte(const Jeu & jeu){
    int nbCase = jeu.getPlateau().getNbCase();
    grille(jeu, nbCase);
    cout << endl;
    //affichageCarte(jeu);
}


