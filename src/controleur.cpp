#include "controleur.h"

bool Jeu::jouerCarte(int valCarte, int couleur, int (getIdPion)(const Plateau &, string), int (cinInt)(string), char (cinChar)(string), void (message)(string), bool coequipier, bool joker) {
	assert(valCarte == -4 || (-1 <= valCarte && valCarte <= 13 && valCarte != 0 && valCarte != 4));
	assert(1 <= couleur && couleur <= nbJoueurs);
	int nb_possible = 0, idPion = 0, c1 = couleur;
	Joueur& j1 = joueurs[couleur-1];
	if (coequipier) couleur = 1 + ((couleur < 5) ? (couleur+1)%4 : 10-couleur);
	Joueur& joueur = joueurs[couleur-1];
	
	// Cas du permutter
	if (valCarte == 11) {
		for (int i = (couleur-1)*4 ; i < couleur*4 ; i++) {
			if (pions[i].getPos() >= 0) {
				idPion = i+1;
				nb_possible++;
			}
		}
		if (nb_possible > 1) idPion = 0;
		nb_possible = 0;
		while (idPion < 1 || idPion > 4*nbJoueurs || pions[idPion-1].getPos() < 0 || (idPion-1)/4 != couleur-1) idPion = getIdPion(plateau, "Id du pion à permutter (pion du joueur) : ");
		int idPion2 = 0;
		while (idPion2 < 1 || idPion2 > 4*nbJoueurs || pions[idPion2-1].estPieu() || idPion2 == idPion) idPion2 = getIdPion(plateau, "Id du deuxième pion avec lequel permutter : ");
		if (!permutter(idPion, idPion2)) return false;
	} 
	
	// Cas du joker
	else if (valCarte == -1) {
		bool continuer = true;
		while (continuer) {
			do {
				valCarte = cinInt("Valeur désirée pour le joker : ");
			} while (valCarte != -4 && (valCarte < 1 || valCarte > 13 || valCarte == 4));
			if (!carteJouable(c1, valCarte, coequipier, true)) message("Action impossible ! Choisissez une autre valeur pour le joker.");
			else continuer = false;
		}
		
		return jouerCarte(valCarte, c1, getIdPion, cinInt, cinChar, message, coequipier, true);
	} 
	
	// Cas du démarrer
	else if (valCarte == 1 || valCarte == 10 || valCarte == 13) {
		char choix = '0';
		if (joueur.getReserve() == 4) choix = 'D';
		else if (!demarrer(couleur, true)) choix = 'A';
		else if (joueur.getReserve() > 0) {
			int nb = 0;
			for (int id = (couleur-1)*4+1 ; id <= 4*couleur ; id++) {
				if (avancerPion(valCarte, id, true)) {
					nb = 1;
					break;
				}
			}
			choix = (nb == 0) ? 'D':'0';
		}
		while (choix != 'D' && choix != 'A' && choix != 'd' && choix != 'a') choix = cinChar("Utiliser la carte comme démarrer(D) ou avancer(A) : ");
		if ((choix == 'D' || choix == 'd') && !demarrer(couleur)) return false;
		else if (choix == 'A' || choix == 'a') {
			for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
				if (avancerPion(valCarte, i, true)) {
					idPion = i;
					nb_possible++;
				}
			}
			if (nb_possible == 0) return false;
			if (nb_possible > 1 ) idPion = 0;
			while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion(plateau, "Id du pion à avancer : ");
			if (!avancerPion(valCarte, idPion)) return false;
		}
	} 
	
	// Cas du 7x1
	else if (valCarte == 7 && joueur.getReserve() < 3) {
		int val, somme = 0;
		for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
			val = 1;
			while (val < 7 && avancerPion(val, i, true)) val++;
			somme += val-1;
			if (val == 7 && avancerPion(val, i, true)) idPion = i;
		}
		if (somme < 7 && idPion == 0) return false;
		if (somme == 6 && !avancerPion(7, idPion)) return false;
		else if (somme == 6) ;
		else {
			somme = 0;
			while (somme < 7) {
				bool continuer = true;
				while (continuer) {
					idPion = 0;
					while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion(plateau, "Id du pion à avancer : ");
					val = 0;
					while (val < 1 || somme + val > 7) val = cinInt("Nombre de cases à avancer : ");
					if (!avancerPion(val, idPion, true)) message("Ce déplacement est impossible !");
					else continuer = false;
				}
				avancerPion(val, idPion, false, true);
				somme += val;
			}
		}
	} 
	
	// Cas du avancer
	else {
		for (int i = (couleur-1)*4 +1 ; i <= couleur*4 ; i++) {
			if (avancerPion(valCarte, i, true)) {
				idPion = i;
				nb_possible++;
			}
		}
		if (nb_possible == 0) return false;
		if (nb_possible > 1 ) idPion = 0;
		while (idPion < 1 || idPion > 4*nbJoueurs || (idPion-1)/4 != couleur-1) idPion = getIdPion(plateau, "Id du pion à avancer : ");
		if (!avancerPion(valCarte, idPion)) return false;
	}
	
	// Affichage sur le tas
	if (joker) valCarte = -1;
	pioche.setTas(j1.retirerCarte(valCarte));
	return true;
}

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

void afficherVainqueur(int couleurVainqueur, bool versionGraphique) {
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

void jouer(bool versionGraphique, bool dev){
	srand(time(NULL));
	if (versionGraphique) {

	}
	ImageViewer image(jeu);
    image.afficher(jeu);
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
					return afficherVainqueur(couleur, versionGraphique);
				}
			}
		}
	}
}