
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

int cinProtectionInt(string cout_message) {
	int val = 0;
	cout << cout_message;
	if(!(cin >> val)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		val = 0;
	}
	return val;
}

char cinProtectionChar(string cout_message) {
	char val = '0';
	cout << cout_message;
	if(!(cin >> val)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		val = '0';
	}
	return val;
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

void affichageCarte(const Jeu & jeu, int indiceJoueur, int joueurActif) {
    cout << "     Les cartes du joueur " << intToStr(indiceJoueur) << " : [ ";
    for (int j = 0; j < 4; j++) {
        if(jeu.getJoueur(indiceJoueur).getCarte(j) != nullptr) {
            if (joueurActif == indiceJoueur || joueurActif == 7) {
                cout << jeu.getJoueur(indiceJoueur).getCarte(j)->getValeur() << " ";
            }
            else {
                cout << "* ";
            }
        }
    }
    cout << "]";
}


void affichageMaison(const Jeu & jeu, int couleur) {
    for (int i = 0; i < 4; i++) {
        cout << jeu.getJoueur(couleur-1).getMaison()[i] << " ";
    }
}



void ligneHaut(const Jeu & jeu, int nbCase, int joueurActif) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 8*(nbJ-2); i++){
        affichageId(jeu.getPlateau().getIdPion(i), i);  //i;
    }
    affichageCarte(jeu, 0, joueurActif);
    cout << endl;
}

void maisonHaut(const Jeu & jeu, int nbCase, int joueurActif) {
    int nbJ = nbCase/16;
    affichageId(jeu.getPlateau().getIdPion(nbCase-1), nbCase-1);  //63
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
        for (int i = 17 ; i <= 20 ; i++) cout << ((jeu.getPion(i).getPos() == -2) ? "":" ");
        cout << "   ";
    }
    affichageId(jeu.getPlateau().getIdPion(8*(nbJ-2)), 8*(nbJ-2)); //16
    affichageCarte(jeu, 1, joueurActif);
    cout << endl;
}

void reserveHaut(const Jeu & jeu, int nbCase, int joueurActif) {
    int nbJ = nbCase/16;
    affichageId(jeu.getPlateau().getIdPion(nbCase-2), nbCase-2); //62
    if (nbJ == 4) {
        cout << "  " << "Réserve : " << jeu.getJoueur(0).getReserve() << "         ";
        cout << "Réserve : " << jeu.getJoueur(1).getReserve() << "         ";
    }
    else {
        cout << "  Réserve : " << jeu.getJoueur(0).getReserve();
        cout << "                      Réserve : " << jeu.getJoueur(1).getReserve();
        cout << "                      Réserve : " << jeu.getJoueur(4).getReserve();
        cout << "           ";
    }
    affichageId(jeu.getPlateau().getIdPion(8*(nbJ-2)+1), 8*(nbJ-2)+1); //62
    if (nbJ == 6) {
        affichageCarte(jeu, 4, joueurActif);
    }
    cout << endl;
}

void idPionHaut(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    affichageId(jeu.getPlateau().getIdPion(nbCase-3), nbCase-3); //62
    if (nbJ == 4) {
        cout << "  " << "Pions : 1 2 3 4"  << "     ";
        cout << "Pions : 5 6 7 8"  << "     ";
    }
    else {
        cout << "  Pions : 1 2 3 4";
        cout << "                  Pions : 5 6 7 8";
        cout << "                  Pions : 17 18 19 20   ";
    }
    affichageId(jeu.getPlateau().getIdPion(8*(nbJ-2)+2), 8*(nbJ-2)+2); //62
    cout << endl;
}



void milieu(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 10; i++) {
        affichageId(jeu.getPlateau().getIdPion(nbCase-4-i), nbCase-4-i);  // 61-i
        if (i == 5) {
            for (int j = 0 ; j < 4*(nbJ-2)-2; j++) {
                cout << "   ";
            }
            Carte* tas = jeu.getPioche().getTas();
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
        affichageId(jeu.getPlateau().getIdPion(8*(nbJ-2)+3+i), 8*(nbJ-2)+3+i); // 18+i
        cout << endl;
    }
}

void idPionBas(const Jeu & jeu, int nbCase) {
    int nbJ = nbCase/16;
    affichageId(jeu.getPlateau().getIdPion(nbCase-14), nbCase-14);
    if (nbJ == 4) {
        cout << "  " << "Pions : 13 14 15 16"  << " ";
        cout << "Pions : 9 10 11 12"  << "  ";
    }
    else {
        cout << "  Pions : 21 22 23 24";
        cout << "              Pions : 13 14 15 16";
        cout << "              Pions : 9 10 11 12    ";
    }
    affichageId(jeu.getPlateau().getIdPion((nbCase-1)/2-2), (nbCase-1)/2-2);
    cout << endl;
}

void reserveBas(const Jeu & jeu, int nbCase, int joueurActif) {
    affichageId(jeu.getPlateau().getIdPion(nbCase-15), nbCase-15); //49
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
    affichageId(jeu.getPlateau().getIdPion((nbCase-1)/2-1), (nbCase-1)/2-1); //30
    if (nbCase/16 == 6) {
        affichageCarte(jeu, 2, joueurActif);
    }
    cout << endl;
}


void maisonBas(const Jeu & jeu, int nbCase, int joueurActif) {
    affichageId(jeu.getPlateau().getIdPion(nbCase-16), nbCase-16); // 48
    if (jeu.getNbJoueurs() == 4) {
        cout << "  " << "Jaune : ";
        affichageMaison(jeu, 4);
        for (int i = 13 ; i <= 16 ; i++) cout << ((jeu.getPion(i).getPos() == -2) ? "":" ");
        cout << "Bleu : ";
        affichageMaison(jeu, 3);
        for (int i = 10 ; i <= 12 ; i++) cout << ((jeu.getPion(i).getPos() == -2) ? "":" ");
        cout << "  ";
    }
    else {
        cout << "  Blanc : ";
        affichageMaison(jeu, 6);
        for (int i = 21 ; i <= 24 ; i++) cout << ((jeu.getPion(i).getPos() == -2) ? "":" ");
        cout << "             Jaune : ";
        affichageMaison(jeu, 4);
        for (int i = 13 ; i <= 16 ; i++) cout << ((jeu.getPion(i).getPos() == -2) ? "":" ");
        cout << "             Bleu : ";
        affichageMaison(jeu, 3);
        for (int i = 10 ; i <= 12 ; i++) cout << ((jeu.getPion(i).getPos() == -2) ? "":" ");
        cout << "    ";
    }
    affichageId(jeu.getPlateau().getIdPion(nbCase/2-1), nbCase/2-1);  // 31
    if (jeu.getNbJoueurs() == 6) {
        affichageCarte(jeu, 3, joueurActif);
    }
    else {
        affichageCarte(jeu, 2, joueurActif);
    }
    cout << endl;
}


void ligneBas(const Jeu & jeu, int nbCase, int joueurActif) {
    int nbJ = nbCase/16;
    for (int i = 0; i < 8*(nbJ-2); i++) {
        affichageId(jeu.getPlateau().getIdPion(nbCase -17 -i), nbCase-17-i);  //47-i
    }
    if (jeu.getNbJoueurs() == 6) {
        affichageCarte(jeu, 5, joueurActif);
    }
    else {
        affichageCarte(jeu, 3, joueurActif);
    }
    cout << endl;
}



void grille(const Jeu & jeu, int nbCase, int joueurActif) {
    ligneHaut(jeu, nbCase, joueurActif);
    maisonHaut(jeu, nbCase, joueurActif);
    reserveHaut(jeu, nbCase, joueurActif);
    idPionHaut(jeu, nbCase);
    milieu(jeu, nbCase);
    idPionBas(jeu, nbCase);
    reserveBas(jeu, nbCase, joueurActif);
    maisonBas(jeu, nbCase, joueurActif);
    ligneBas(jeu, nbCase, joueurActif);
}



void affichageTexte(const Jeu & jeu, int joueurActif){
    int nbCase = jeu.getPlateau().getNbCase();
	clearTerminal();
    grille(jeu, nbCase, joueurActif);
}


// Fonctions pour le déroulé du jeu

int choixCarte(string message, const Joueur& joueur) {
	int val_carte = 0;
	do {
		cin.clear();
		cout << message;
		val_carte = cinProtectionInt();
	} while (!joueur.estDansMain(val_carte));
	
	return val_carte;
}

void echangeDeCartes(Jeu& jeu) {
	int val_carte, couleur, nbJoueurs = jeu.getNbJoueurs();
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	int echange_carte[3] = {0, 0, 0};
		for (int i = 0 ; i < nbJoueurs/2 ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, -1);
			cout << "\nTour de " << intToStr(couleur-1) << " (Entrée pour continuer)" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			affichageTexte(jeu, couleur-1);
			cout << "\nTour de " << intToStr(couleur-1) << " :" << endl;
			val_carte = choixCarte("\nCarte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			echange_carte[i] = val_carte;
		}

		for (int i = nbJoueurs/2 ; i < nbJoueurs ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, -1);
			cout << "\nTour de " << intToStr(couleur-1) << " (Entrée pour continuer)" << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			affichageTexte(jeu, couleur-1);
			cout << "\nTour de " << intToStr(couleur-1) << " :" << endl;
			val_carte = choixCarte("\nCarte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			
			int indJ1;
			if (nbJoueurs == 6) indJ1 = (i != 5) ? (couleur-1)-(nbJoueurs/2-1):4;
			else indJ1 = (couleur-1)-nbJoueurs/2;
			jeu.echangerCartes(indJ1, (couleur-1), echange_carte[((i!=5)?indJ1:2)], val_carte);
		}
}

void tourJoueur(Jeu& jeu, int couleur, bool dev) {
	if (jeu.getJoueur(couleur-1).mainVide()) return ;
	char choix = 'o';
	int val_carte;
	bool peut_jouer = true, coequipier = (jeu.getJoueur(couleur-1).maisonRemplie());
    IA ia;
	if (!dev) {
		affichageTexte(jeu, -1);
		cout << "\nTour de " << intToStr(couleur-1) << " (Entrée pour continuer)" << endl;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
	}
    if (jeu.getJoueur(couleur-1).estIA()) ia.genererCoups(jeu, couleur);
    else {
        affichageTexte(jeu, couleur-1);
        cout << "\nTour de " << intToStr(couleur-1) << " :" << endl;
        if (!jeu.peutJouer(couleur, coequipier)) {
            cout << "Aucune carte ne peut être jouée. Défausser toutes les cartes ? (Oui(o) ; Non(n)) : ";
            cin >> choix;
            if (choix == 'o' || choix == 'O') {
                jeu.defausserJoueur(couleur);
                return ;
            }
            peut_jouer = false;
        }
        do {
            val_carte = choixCarte(((peut_jouer) ? "\nCarte à jouer : " : "\nCarte à défausser : "), jeu.getJoueur(couleur-1));

            if (!jeu.carteJouable(couleur, val_carte, coequipier) && peut_jouer) {
                cout << "\nCette carte ne peut pas être jouée ! Choisissez-en une autre." << endl;
                choix = 'n';
            } else choix = 'o';

        } while (choix == 'n');

        if (!jeu.carteJouable(couleur, val_carte, coequipier)) jeu.defausserCarte(val_carte, couleur);
        else jeu.jouerCarte(val_carte, couleur, cinProtectionInt, cinProtectionChar, coequipier, false);
    }
}

int jouer(bool dev){
	int nbIA = 0, nbJoueurs = 4;
	do {
		cout << "\nNombre de joueurs (4 ou 6) : ";
		nbJoueurs = cinProtectionInt();
	} while (nbJoueurs != 4 && nbJoueurs != 6);

    do {
		cout << "\nNombre d'IA (0-" << nbJoueurs << ") : ";
		nbIA = cinProtectionInt();
	} while (nbIA < 0 || nbIA > nbJoueurs);
	
	Jeu jeu(nbJoueurs, nbIA);
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	while (true) {
		if (!dev) {
			jeu.distribuer();
			echangeDeCartes(jeu);
		} else {
			for (int i = 0 ; i < 4 ; i++) {
				for (int j = 0 ; j < nbJoueurs ; j++) {
					jeu.attribuerCarte(-1, j+1);
				}
			}
		}

		for (int i = 0 ; i < 4 ; i++) {
			for (int j = 0 ; j < nbJoueurs ; j++) {
				int couleur = (nbJoueurs == 6) ? ordre[j]:j+1;
				tourJoueur(jeu, couleur, dev);
				if (jeu.partieGagnee()) {
					affichageTexte(jeu, 7);
					return couleur;
				}
			}
		}
	}
}