
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

int getIdPion(const Plateau &plateau, string coutMessage) {
    return cinProtectionInt(coutMessage);
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
	int valCarte = 0;
    while (!joueur.estDansMain(valCarte)) valCarte = cinProtectionInt(message);	
	return valCarte;
}

void echangeDeCartes(Jeu& jeu) {
	int valCarte, couleur, nbJoueurs = jeu.getNbJoueurs();
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	int echange_carte[3] = {0, 0, 0};
		for (int i = 0 ; i < nbJoueurs/2 ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, -1);
			message("Tour de " + intToStr(couleur-1) + " (Entrée pour continuer)");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			affichageTexte(jeu, couleur-1);
			message("\nTour de " + intToStr(couleur-1) + " :");
			valCarte = choixCarte("Carte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			echange_carte[i] = valCarte;
		}

		for (int i = nbJoueurs/2 ; i < nbJoueurs ; i++) {
			couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
			affichageTexte(jeu, -1);
			message("Tour de " + intToStr(couleur-1) + " (Entrée pour continuer)");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
			affichageTexte(jeu, couleur-1);
			message("\nTour de " + intToStr(couleur-1) + " :");
			valCarte = choixCarte("Carte à donner à ton coéquipier : ", jeu.getJoueur(couleur-1));
			
			int indJ1;
			if (nbJoueurs == 6) indJ1 = (i != 5) ? (couleur-1)-(nbJoueurs/2-1):4;
			else indJ1 = (couleur-1)-nbJoueurs/2;
			jeu.echangerCartes(indJ1, (couleur-1), echange_carte[((i!=5)?indJ1:2)], valCarte);
		}
}

void tourJoueur(Jeu& jeu, int couleur, bool dev) {
	if (jeu.getJoueur(couleur-1).mainVide()) return ;
	char choix = 'o';
	int valCarte;
	bool peut_jouer = true, coequipier = (jeu.getJoueur(couleur-1).maisonRemplie());
    IA ia;
	if (!dev) {
		affichageTexte(jeu, -1);
		message("Tour de " + intToStr(couleur-1) + " (Entrée pour continuer)");
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
	}
    if (jeu.getJoueur(couleur-1).estIA()) ia.genererCoups(jeu, couleur);
    else {
        affichageTexte(jeu, couleur-1);
        message("\nTour de " + intToStr(couleur-1) + " :");
        if (!jeu.peutJouer(couleur, coequipier)) {
            choix = cinProtectionChar("Aucune carte ne peut être jouée. Défausser toutes les cartes ? (Oui(o) ; Non(n)) : ");
            if (choix == 'o' || choix == 'O') {
                jeu.defausserJoueur(couleur);
                return ;
            }
            peut_jouer = false;
        }
        do {
            valCarte = choixCarte(((peut_jouer) ? "Carte à jouer : " : "Carte à défausser : "), jeu.getJoueur(couleur-1));

            if (!jeu.carteJouable(couleur, valCarte, coequipier) && peut_jouer) {
                message("Cette carte ne peut pas être jouée ! Choisissez-en une autre.");
                choix = 'n';
            } else choix = 'o';

        } while (choix == 'n');

        if (!jeu.carteJouable(couleur, valCarte, coequipier)) jeu.defausserCarte(valCarte, couleur);
        else jeu.jouerCarte(valCarte, couleur, getIdPion, cinProtectionInt, cinProtectionChar, message, coequipier);
    }
}

int jouer(bool dev){
	int nbIA = 0, nbJoueurs = 4;
	while (nbJoueurs != 4 && nbJoueurs != 6) nbJoueurs = cinProtectionInt("Nombre de joueurs (4 ou 6) : ");

    while (nbIA < 0 || nbIA > nbJoueurs) nbIA = cinProtectionInt("Nombre d'IA (0-" + to_string(nbJoueurs) + ") : ");
	
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