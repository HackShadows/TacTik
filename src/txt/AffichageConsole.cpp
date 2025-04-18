
#include "AffichageConsole.h"
#include <iostream>
#include <cassert>

using namespace std;

void clearTerminal() {
	#ifdef _WIN32
		system("cls");  // Commande Windows
	#else
		system("clear");  // Commande Linux/Mac
	#endif
}

void affichageId(int id, int indice){
    assert(indice>=0 && indice<96);
    if (indice%16 == 0 && id == 0){
        cout << "[] ";
    }
    else{
        if (id/10 == 0) {
        cout << id << "  ";
        }
        else {
            cout << id << " ";
        }
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

int cinProtectionInt(string coutMessage) {
	int val = 0;
	cout << "\n" + coutMessage;
    cin.clear();
	if(!(cin >> val)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		val = 0;
	}
	return val;
}

char cinProtectionChar(string coutMessage) {
	char val = '0';
	cout << "\n" + coutMessage;
    cin.clear();
	if(!(cin >> val)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		val = '0';
	}
	return val;
}

void message(string coutMessage) {cout << "\n" + coutMessage << endl;}



ImageConsole::ImageConsole() : jeu(nullptr), nbCase(jeu->getPlateau().getNbCase()) {
	
}

ImageConsole::~ImageConsole() {}

void ImageConsole::initJeu(int nbJoueurs, int nbIA) {
    assert(nbIA >= 0 && nbJoueurs >= nbIA && (nbJoueurs == 4 || nbJoueurs == 6));
}

Jeu& ImageConsole::getJeu() {return *jeu;}

void ImageConsole::affichageCarte(int indiceJoueur, int joueurActif) {
    cout << "     Les cartes du joueur " << intToStr(indiceJoueur) << " : [ ";
    for (int j = 0; j < 4; j++) {
        if(jeu->getJoueur(indiceJoueur).getCarte(j) != nullptr) {
            if (joueurActif == indiceJoueur || joueurActif == 6) {
                cout << jeu->getJoueur(indiceJoueur).getCarte(j)->getValeur() << " ";
            }
            else {
                cout << "* ";
            }
        }
    }
    cout << "]";
}


void ImageConsole::affichageMaison(int couleur) {
    for (int i = 0; i < 4; i++) {
        cout << jeu->getJoueur(couleur-1).getMaison()[i] << " ";
    }
}



void ImageConsole::ligneHaut(int joueurActif) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 8*(nbJ-2); i++){
        affichageId(jeu->getPlateau().getIdPion(i), i);  //i;
    }
    affichageCarte(0, joueurActif);
    cout << endl;
}

void ImageConsole::maisonHaut(int joueurActif) {
    int nbJ = nbCase/16;
    affichageId(jeu->getPlateau().getIdPion(nbCase-1), nbCase-1);  //63
    if (jeu->getNbJoueurs() == 4) {
        cout << "  " << "Vert : ";
        affichageMaison(1);
        cout << "     " << "Rouge : ";
        affichageMaison(2);
        cout << "    ";
    }
    else {
        cout << "  Vert : ";
        affichageMaison(1);
        cout << "                  Rouge : ";
        affichageMaison(2);
        cout << "                 Noir : ";
        affichageMaison(5);
        for (int i = 17 ; i <= 20 ; i++) cout << ((jeu->getPion(i).getPos() == -2) ? "":" ");
        cout << "   ";
    }
    affichageId(jeu->getPlateau().getIdPion(8*(nbJ-2)), 8*(nbJ-2)); //16
    affichageCarte(1, joueurActif);
    cout << endl;
}

void ImageConsole::reserveHaut(int joueurActif) {
    int nbJ = nbCase/16;
    affichageId(jeu->getPlateau().getIdPion(nbCase-2), nbCase-2); //62
    if (nbJ == 4) {
        cout << "  " << "Réserve : " << jeu->getJoueur(0).getReserve() << "         ";
        cout << "Réserve : " << jeu->getJoueur(1).getReserve() << "         ";
    }
    else {
        cout << "  Réserve : " << jeu->getJoueur(0).getReserve();
        cout << "                      Réserve : " << jeu->getJoueur(1).getReserve();
        cout << "                      Réserve : " << jeu->getJoueur(4).getReserve();
        cout << "           ";
    }
    affichageId(jeu->getPlateau().getIdPion(8*(nbJ-2)+1), 8*(nbJ-2)+1); //62
    if (nbJ == 6) {
        affichageCarte(4, joueurActif);
    }
    cout << endl;
}

void ImageConsole::idPionHaut() {
    int nbJ = nbCase/16;
    affichageId(jeu->getPlateau().getIdPion(nbCase-3), nbCase-3); //62
    if (nbJ == 4) {
        cout << "  " << "Pions : 1 2 3 4"  << "     ";
        cout << "Pions : 5 6 7 8"  << "     ";
    }
    else {
        cout << "  Pions : 1 2 3 4";
        cout << "                  Pions : 5 6 7 8";
        cout << "                  Pions : 17 18 19 20   ";
    }
    affichageId(jeu->getPlateau().getIdPion(8*(nbJ-2)+2), 8*(nbJ-2)+2); //62
    cout << endl;
}



void ImageConsole::milieu() {
    int nbJ = nbCase/16;
    for (int i = 0; i < 10; i++) {
        affichageId(jeu->getPlateau().getIdPion(nbCase-4-i), nbCase-4-i);  // 61-i
        if (i == 5) {
            for (int j = 0 ; j < 4*(nbJ-2)-2; j++) {
                cout << "   ";
            }
            Carte* tas = jeu->getPioche().getTas();
            if (tas == nullptr) cout << "0  ";
            else {
                int val = tas->getValeur();
                if (val < 0) cout << val << " ";
                else affichageId(val, 1);
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
        affichageId(jeu->getPlateau().getIdPion(8*(nbJ-2)+3+i), 8*(nbJ-2)+3+i); // 18+i
        cout << endl;
    }
}

void ImageConsole::idPionBas() {
    int nbJ = nbCase/16;
    affichageId(jeu->getPlateau().getIdPion(nbCase-14), nbCase-14);
    if (nbJ == 4) {
        cout << "  " << "Pions : 13 14 15 16"  << " ";
        cout << "Pions : 9 10 11 12"  << "  ";
    }
    else {
        cout << "  Pions : 21 22 23 24";
        cout << "              Pions : 13 14 15 16";
        cout << "              Pions : 9 10 11 12    ";
    }
    affichageId(jeu->getPlateau().getIdPion((nbCase-1)/2-2), (nbCase-1)/2-2);
    cout << endl;
}

void ImageConsole::reserveBas(int joueurActif) {
    affichageId(jeu->getPlateau().getIdPion(nbCase-15), nbCase-15); //49
    if (jeu->getNbJoueurs() == 4){
        cout << "  " << "Réserve : " << jeu->getJoueur(3).getReserve() << "         ";
        cout << "Réserve : " << jeu->getJoueur(2).getReserve() << "         ";
    }
    else {
        cout << "  Réserve : " << jeu->getJoueur(5).getReserve();
        cout << "                      Réserve : " << jeu->getJoueur(3).getReserve();
        cout << "                      Réserve : " << jeu->getJoueur(2).getReserve();
        cout << "           ";
    }
    affichageId(jeu->getPlateau().getIdPion((nbCase-1)/2-1), (nbCase-1)/2-1); //30
    if (nbCase/16 == 6) {
        affichageCarte(2, joueurActif);
    }
    cout << endl;
}


void ImageConsole::maisonBas(int joueurActif) {
    affichageId(jeu->getPlateau().getIdPion(nbCase-16), nbCase-16); // 48
    if (jeu->getNbJoueurs() == 4) {
        cout << "  " << "Jaune : ";
        affichageMaison(4);
        for (int i = 13 ; i <= 16 ; i++) cout << ((jeu->getPion(i).getPos() == -2) ? "":" ");
        cout << "Bleu : ";
        affichageMaison(3);
        for (int i = 10 ; i <= 12 ; i++) cout << ((jeu->getPion(i).getPos() == -2) ? "":" ");
        cout << "  ";
    }
    else {
        cout << "  Blanc : ";
        affichageMaison(6);
        for (int i = 21 ; i <= 24 ; i++) cout << ((jeu->getPion(i).getPos() == -2) ? "":" ");
        cout << "             Jaune : ";
        affichageMaison(4);
        for (int i = 13 ; i <= 16 ; i++) cout << ((jeu->getPion(i).getPos() == -2) ? "":" ");
        cout << "             Bleu : ";
        affichageMaison(3);
        for (int i = 10 ; i <= 12 ; i++) cout << ((jeu->getPion(i).getPos() == -2) ? "":" ");
        cout << "    ";
    }
    affichageId(jeu->getPlateau().getIdPion(nbCase/2-1), nbCase/2-1);  // 31
    if (jeu->getNbJoueurs() == 6) {
        affichageCarte(3, joueurActif);
    }
    else {
        affichageCarte(2, joueurActif);
    }
    cout << endl;
}


void ImageConsole::ligneBas(int joueurActif) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 8*(nbJ-2); i++) {
        affichageId(jeu->getPlateau().getIdPion(nbCase -17 -i), nbCase-17-i);  //47-i
    }
    if (jeu->getNbJoueurs() == 6) {
        affichageCarte(5, joueurActif);
    }
    else {
        affichageCarte(3, joueurActif);
    }
    cout << endl;
}



void ImageConsole::grille(int joueurActif) {
    ligneHaut(joueurActif);
    maisonHaut(joueurActif);
    reserveHaut(joueurActif);
    idPionHaut();
    milieu();
    idPionBas();
    reserveBas(joueurActif);
    maisonBas(joueurActif);
    ligneBas(joueurActif);
}



void ImageConsole::affichageTexte(int joueurActif){
	clearTerminal();
    grille(joueurActif);
}
