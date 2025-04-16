#include "controleur.h"

#include <iostream>
#include <cassert>

using namespace std;


Controleur::Controleur() {
	console = new ImageConsole;
	graphique = nullptr;
	versionGraphique = false;
	joueurActif = -1;
}

Controleur::Controleur(int nbJ, int nbIA, bool affichageGraphique) {
	assert(nbIA >= 0 && nbJ >= nbIA && (nbJ == 4 || nbJ == 6));
	versionGraphique = affichageGraphique;
	joueurActif = -1;
	if (versionGraphique) {
		console = nullptr;
		graphique = new ImageViewer(nbJ, nbIA);
	} else {
		console = new ImageConsole(nbJ, nbIA);
		graphique = nullptr;
	}
}

Controleur::~Controleur() {
	if (console != nullptr) {
		delete console;
		console = nullptr;
	}
	if (graphique != nullptr) {
		delete graphique;
		graphique = nullptr;
	}
}

Jeu& Controleur::getJeu() {
	if (versionGraphique) return graphique->getJeu();
	return console->getJeu();
}

void Controleur::setJoueurActif(int indJoueurActif) {
	assert(-1 <= joueurActif && joueurActif <= 6);
	joueurActif = indJoueurActif;
}

int Controleur::getIdPion(string coutMessage) {
	if (versionGraphique) return graphique->getIndicePionEvent(coutMessage);
    return saisirEntier(coutMessage);
}

int Controleur::saisirEntier(string coutMessage) {
	if (versionGraphique) return graphique->getEventNumber(coutMessage);
	return cinProtectionInt(coutMessage);
}

char Controleur::saisirCaractere(string coutMessage) {
	if (versionGraphique) return graphique->getEventChar(coutMessage);
	return cinProtectionChar(coutMessage);
}

void Controleur::afficherMessage(string coutMessage) {
	if (versionGraphique) afficherJeu(-1, coutMessage);
	else message(coutMessage);
}

bool Controleur::attenteTour(bool dev) {
	if (versionGraphique) {
		if (afficherJeu(-1, "Tour de " + intToStr(joueurActif) + " (Entrée pour continuer)")[0] == 0) return false;
	}
	else {
		if (!dev) {
			console->affichageTexte(-1);
			afficherMessage("Tour de " + intToStr(joueurActif) + " (Entrée pour continuer)");
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.get();
		}
		console->affichageTexte(joueurActif);
		afficherMessage("\nTour de " + intToStr(joueurActif) + " :");
	}
	return true;
}

bool Controleur::jouerCarte(int valCarte, bool coequipier, bool joker) {
	Jeu &jeu = getJeu();
	int nbJoueurs = jeu.getNbJoueurs();
	assert(valCarte == -4 || (-1 <= valCarte && valCarte <= 13 && valCarte != 0 && valCarte != 4));
	int couleur = joueurActif + 1;
	int nb_possible = 0, idPion = 0, c1 = couleur;
	Joueur& j1 = jeu.getJoueurNonConst(couleur-1);
	if (coequipier) couleur = 1 + ((couleur < 5) ? (couleur+1)%4 : 10-couleur);
	Joueur& joueur = jeu.getJoueurNonConst(couleur-1);
	
	// Cas du permutter
	if (valCarte == 11) {
		for (int i = (couleur-1)*4 ; i < couleur*4 ; i++) {
			if (jeu.getPion(i+1).getPos() >= 0) {
				idPion = i+1;
				nb_possible++;
			}
		}
		if (nb_possible > 1) idPion = 0;
		nb_possible = 0;
		while (idPion < 1 || idPion > 4*nbJoueurs || jeu.getPion(idPion).getPos() < 0 || (idPion-1)/4 != couleur-1) idPion = getIdPion("Id du pion à permutter (pion du joueur) : ");
		int idPion2 = 0;
		while (idPion2 < 1 || idPion2 > 4*nbJoueurs || jeu.getPion(idPion2).estPieu() || idPion2 == idPion) idPion2 = getIdPion("Id du deuxième pion avec lequel permutter : ");
		if (!jeu.permutter(idPion, idPion2)) return false;
	} 
	
	// Cas du joker
	else if (valCarte == -1) {
		bool continuer = true;
		while (continuer) {
			do {
				valCarte = saisirEntier("Valeur désirée pour le joker : ");
			} while (valCarte != -4 && (valCarte < 1 || valCarte > 13 || valCarte == 4));
			if (!jeu.carteJouable(c1, valCarte, coequipier, true)) afficherMessage("Action impossible ! Choisissez une autre valeur pour le joker.");
			else continuer = false;
		}
		
		return jouerCarte(valCarte, coequipier, true);
	} 
	
	// Cas du démarrer
	else if (valCarte == 1 || valCarte == 10 || valCarte == 13) {
		char choix = '0';
		if (joueur.getReserve() == 4) choix = 'D';
		else if (!jeu.demarrer(couleur, true)) choix = 'A';
		else if (joueur.getReserve() > 0) {
			int nb = 0;
			for (int id = (couleur-1)*4+1 ; id <= 4*couleur ; id++) {
				if (jeu.avancerPion(valCarte, id, true)) {
					nb = 1;
					break;
				}
			}
			choix = (nb == 0) ? 'D':'0';
		}
		while (choix != 'D' && choix != 'A' && choix != 'd' && choix != 'a') choix = saisirCaractere("Utiliser la carte comme démarrer(D) ou avancer(A) : ");
		if ((choix == 'D' || choix == 'd') && !jeu.demarrer(couleur)) return false;
		else if (choix == 'A' || choix == 'a') {
			for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
				if (jeu.avancerPion(valCarte, i, true)) {
					idPion = i;
					nb_possible++;
				}
			}
			if (nb_possible == 0) return false;
			if (nb_possible > 1 ) idPion = 0;
			while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion("Id du pion à avancer : ");
			if (!jeu.avancerPion(valCarte, idPion)) return false;
		}
	} 
	
	// Cas du 7x1
	else if (valCarte == 7 && joueur.getReserve() < 3) {
		int val, somme = 0;
		for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
			val = 1;
			while (val < 7 && jeu.avancerPion(val, i, true)) val++;
			somme += val-1;
			if (val == 7 && jeu.avancerPion(val, i, true)) idPion = i;
		}
		if (somme < 7 && idPion == 0) return false;
		if (somme == 6 && !jeu.avancerPion(7, idPion)) return false;
		else if (somme == 6) ;
		else {
			somme = 0;
			while (somme < 7) {
				bool continuer = true;
				while (continuer) {
					idPion = 0;
					while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion("Id du pion à avancer : ");
					val = 0;
					while (val < 1 || somme + val > 7) val = saisirEntier("Nombre de cases à avancer : ");
					if (!jeu.avancerPion(val, idPion, true)) afficherMessage("Ce déplacement est impossible !");
					else continuer = false;
				}
				jeu.avancerPion(val, idPion, false, true);
				somme += val;
			}
		}
	} 
	
	// Cas du avancer
	else {
		for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
			if (jeu.avancerPion(valCarte, i, true)) {
				idPion = i;
				nb_possible++;
			}
		}
		if (nb_possible == 0) return false;
		if (nb_possible > 1 ) idPion = 0;
		while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion("Id du pion à avancer : ");
		if (!jeu.avancerPion(valCarte, idPion)) return false;
	}
	
	// Affichage sur le tas
	if (joker) valCarte = -1;
	jeu.setTas(j1.retirerCarte(valCarte));
	return true;
}

array<int, 2> Controleur::choixCarte(string coutMessage, const Joueur& joueur) {
	int valCarte = 0;
	if (versionGraphique) return afficherJeu(1, coutMessage);
    while (!joueur.estDansMain(valCarte)) {
		valCarte = saisirEntier(coutMessage);
	}
	array<int, 2> retour = {1, valCarte};
	return retour;
}

bool Controleur::echangeDeCartes() {
	Jeu &jeu = getJeu();
	int valCarte, couleur, nbJoueurs = jeu.getNbJoueurs();
	int ordre[6] = {1, 2, 5, 3, 4, 6};
	int echange_carte[3] = {0, 0, 0};
	for (int i = 0 ; i < nbJoueurs ; i++) {
		couleur = (nbJoueurs == 6) ? ordre[i]:i+1;
		setJoueurActif(couleur-1);
		attenteTour();
		array<int, 2> result = choixCarte("Carte à donner à " + intToStr(((couleur < 5) ? (couleur+1)%4 : 10-couleur)) + " : ", jeu.getJoueur(joueurActif));
		if (result[0] == 0) return false;
		valCarte = result[1];
		if (i < nbJoueurs/2) echange_carte[i] = valCarte;
		else {
			int indJ1 = (couleur == 6) ? 4:couleur-3;
			jeu.echangerCartes(indJ1, joueurActif, echange_carte[i-nbJoueurs/2], valCarte);
		}
	}
	return true;
}

bool Controleur::tourJoueur(bool dev) {
	Jeu &jeu = getJeu();
	if (jeu.getJoueur(joueurActif).mainVide()) return true;
	char choix = 'o';
	int valCarte;
	bool peut_jouer = true, coequipier = (jeu.getJoueur(joueurActif).maisonRemplie());
    IA ia;
	
	attenteTour(dev);
    
	if (jeu.getJoueur(joueurActif).estIA()) ia.genererCoups(jeu, joueurActif + 1);
    else {
        if (!jeu.peutJouer(joueurActif + 1, coequipier)) {
            choix = saisirCaractere("Aucune carte ne peut être jouée. Défausser toutes les cartes ? (Oui(o) ; Non(n)) : ");
            if (choix == 'o' || choix == 'O') {
                jeu.defausserJoueur(joueurActif + 1);
                return true;
            }
            peut_jouer = false;
        }
        do {
			array<int, 2> result = choixCarte(((peut_jouer) ? "Carte à jouer : " : "Carte à défausser : "), jeu.getJoueur(joueurActif));
			if (result[0] == 0) return false;
			valCarte = result[1];

            if (!jeu.carteJouable(joueurActif + 1, valCarte, coequipier) && peut_jouer) {
                afficherMessage("Cette carte ne peut pas être jouée ! Choisissez-en une autre.");
                choix = 'n';
            } else choix = 'o';

        } while (choix == 'n');

        if (!jeu.carteJouable(joueurActif + 1, valCarte, coequipier)) jeu.defausserCarte(valCarte, joueurActif + 1);
        else jouerCarte(valCarte, joueurActif + 1, coequipier);
    }
	return true;
}

void Controleur::afficherVainqueur(int couleurVainqueur) {
	int vainqueurs = couleurVainqueur;
	int j1 = 4, j2 = 5;
	if (vainqueurs < 5) {
		j1 = (vainqueurs+3)%4;
		j2 = (vainqueurs+1)%4;
	}
	if (versionGraphique) {

	} else {
		cout << "\nLes " << intToStr(j1) << "s et " << intToStr(j2) << "s ont gagné !\n" << endl;
	}
}

array<int, 2> Controleur::afficherJeu(int etapeActuel, string coutMessage) {
	array<int, 2> retour = {1, 0};
	if (versionGraphique) {
    	SDL_Event event;
		array<int, 2> etape_info = {-2, -2};
		if (etapeActuel == -1) graphique->setTextureCartes(-1);
		while (etape_info[0] != etapeActuel) {
			while (SDL_PollEvent(&event)) {
				etape_info = gestionEvent(event);
			}
			if (etape_info[0] == 0) {
				retour[0] = 0;
				return retour;
			}
			graphique->afficher(joueurActif);
		}
		if (etapeActuel == -1) graphique->setTextureCartes(joueurActif);
		retour[1] = etape_info[1];
	}
	else console->affichageTexte(joueurActif);
	return retour;
}

array<int, 2> Controleur::gestionEvent(SDL_Event event) {
    
	array<int, 2> infos = {-2, -2};

    if (event.type == SDL_QUIT) {
		infos[0] = 0;
		return infos;
    }

    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            infos[0] = 0;
			return infos;
        }
        if (event.key.keysym.sym == SDLK_t) {
            graphique->grossissement(true);
        }
        if (event.key.keysym.sym == SDLK_q) {
            graphique->grossissement(false);
        }

        // if (event.key.keysym.sym == SDLK_u) {
        //     cout << graphique->getEventChar();
        // }
        // if (event.key.keysym.sym == SDLK_0) {
        //     joueurActif = 0;
        // }
        // if (event.key.keysym.sym == SDLK_1) {
        //     joueurActif = 1;
        // }
        // if (event.key.keysym.sym == SDLK_2) {
        //     joueurActif = 2;
        // }
        // if (event.key.keysym.sym == SDLK_3) {
        //     joueurActif = 3;
        // }

		// // if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_0
		// // 										|| event.key.keysym.sym == SDLK_1
		// // 										|| event.key.keysym.sym == SDLK_2
		// // 										|| event.key.keysym.sym == SDLK_3) {
		// // 	if (joueurActif >= 0 && cartes_visibles && event.key.keysym.sym == SDLK_RETURN) {
		// // 		joueurActif = -1;
		// // 		cartes_visibles = false;
		// // 	} else if (joueurActif >= 0) cartes_visibles = true;
		// // 	graphique->setTextureCartes(joueurActif);
        // // }

		if (event.key.keysym.sym == SDLK_RETURN) {
			infos[0] = -1;
			return infos;
		}
    }
    if (event.type == SDL_MOUSEBUTTONDOWN && joueurActif >= 0) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            //cout << getIndiceCase(event.button.x, event.button.y, coordonnees, zoom) << endl;
            if (event.button.x > graphique->getImgWidth()) {
                int indiceCase = event.button.y / (250 * graphique->getZoom());
                cout << indiceCase << endl;
                if (indiceCase < 4 && getJeu().getJoueur(joueurActif).getCarte(indiceCase)) {
                    int valeur = getJeu().getJoueur(joueurActif).getCarte(indiceCase)->getValeur();
                    cout << "La valeur de la carte : " << valeur << endl;
                    if (getJeu().carteJouable(joueurActif + 1, valeur)) {
                        cout << "La carte est jouable" << endl;
                    }
					infos[0] = 1;
					infos[1] = valeur;
                }
				return infos;
            }
			cout << graphique->getIndicePion(event.button.x, event.button.y) << endl;
			infos[0] = 2;
			return infos;
        }
    }
	return infos;
}



void jouer(bool versionGraphique, bool dev){
	srand(time(NULL));
	if (versionGraphique) {
		
	}
	int nbIA = -1, nbJoueurs = 0;
	
	while (nbJoueurs != 4 && nbJoueurs != 6) nbJoueurs = cinProtectionInt("Nombre de joueurs (4 ou 6) : ");

    while (nbIA < 0 || nbIA > nbJoueurs) nbIA = cinProtectionInt("Nombre d'IA parmis les joueurs (0-" + to_string(nbJoueurs) + ") : ");
	
	Controleur controleur(nbJoueurs, nbIA, versionGraphique);
	Jeu &jeu = controleur.getJeu();
	int ordre[6] = {1, 2, 5, 3, 4, 6};

	while (true) {
		if (!dev) {
			jeu.distribuer();
			if (!controleur.echangeDeCartes()) return ;
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
				controleur.setJoueurActif(couleur-1);
				controleur.tourJoueur(dev);
				if (jeu.partieGagnee()) {
					controleur.setJoueurActif(6);
					controleur.afficherJeu(6);
					return controleur.afficherVainqueur(couleur);
				}
			}
		}
	}
}
