#ifndef AFFICHERTXT_H
#define AFFICHERTXT_H

#include "../core/Jeu.h"


/**
* @brief Clear le terminal.
*/
void clearTerminal();

/**
* @brief Permet de saisir un entier en gérant les erreurs de saisi.
*
* @param coutMessage Message à afficher avant le cin (non obligatoire).
*
* @return Entier saisi par l'utilisateur (valeur renvoyée par défaut 0).
*/
int cinProtectionInt(string coutMessage = "");

/**
* @brief Permet de saisir un caractère en gérant les erreurs de saisi.
*
* @param coutMessage Message à afficher avant le cin (non obligatoire).
*
* @return Caractère saisi par l'utilisateur (valeur renvoyée par défaut '0').
*/
char cinProtectionChar(string coutMessage = "");

/**
* @brief Affiche un nombre prenant 2 espaces dans le terminal.
*
* @param id Le nombre que l'on veut afficher.
* @param indice L'indice de la case a afficher.
*/
void affichageId(int id, int indice);

/**
* @brief Convertie la couleur entière du joueur en string.
*
* @param entier Couleur à convertir en string.
*/
string intToStr(int entier);

/**
* @brief Affiche la maison d'une couleur dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param couleur La couleur dont on veut afficher la maison
*/
void affichageMaison(const Jeu & jeu, int couleur);

/**
* @brief Affiche la premiere ligne d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
* @param joueurActif Le joueur qui joue
*/
void ligneHaut(const Jeu & jeu, int nbCase, int joueurActif);

/**
* @brief Affiche la deuxieme ligne d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
* @param joueurActif Le joueur qui joue

*/
void maisonHaut(const Jeu & jeu, int nbCase, int joueurActif);

/**
* @brief Affiche la troisieme ligne d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
* @param joueurActif Le joueur qui joue
*/
void reserveHaut(const Jeu & jeu, int nbCase, int joueurActif);

/**
* @brief Affiche la quatrième ligne d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
*/
void idPionHaut(const Jeu & jeu, int nbCase);


/**
* @brief Affiche les lignes du milieu d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
*/
void milieu(const Jeu & jeu, int nbCase);

/**
* @brief Affiche la quatrième ligne du bas d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
*/
void idPionBas(const Jeu & jeu, int nbCase);


/**
* @brief Affiche les reserves sur la 3eme ligne du bas d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
* @param joueurActif Le joueur qui joue
*/
void reserveBas(const Jeu & jeu, int nbCase, int joueurActif);

/**
* @brief Affiche les maisons sur la deuxieme ligne du bas d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
* @param joueurActif Le joueur qui joue
*/
void maisonBas(const Jeu & jeu, int nbCase, int joueurActif);

/**
* @brief Affiche la dernière ligne d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
* @param joueurActif Le joueur qui joue
*/
void ligneBas(const Jeu & jeu, int nbCase, int joueurActif);


/**
* @brief Affiche la grille entière d'une partie dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param nbCase Le nombre de case du plateau
* @param joueurActif Le joueur qui joue
*/
void grille(const Jeu & jeu, int nbCase, int joueurActif);


/**
* @brief Affiche les cartes des joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param indiceJoueur L'indice du joueur dont on veut afficher les cartes.
* @param joueurActif Le joueur qui joue
*/
void affichageCarte(const Jeu & jeu, int indiceJoueur, int joueurActif);

/**
* @brief Affiche l'état du jeu sous format texte dans le terminal.
*
* @param jeu Le jeu à afficher.
* @param joueurActif Le joueur qui joue
*/
void affichageTexte(const Jeu & jeu, int joueurActif);


// Fonctions pour le déroulé du jeu

/**
* @brief Récupère la carte que le joueur souhaite jouer.
*
* @param message Message à afficher avant le cin.
* @param joueur Le joueur à qui est demandée la carte.
* 
* @return Valeur de la carte choisie par le joueur.
*/
int choixCarte(string message, const Joueur& joueur);

/**
* @brief Effectue l'échange de cartes entre les joueurs au début de chaque tour.
*
* @param jeu Jeu en cours.
*/
void echangeDeCartes(Jeu& jeu);

/**
* @brief Effectue un tour de jeu pour un joueur.
*
* @param jeu Jeu en cours.
* @param couleur Couleur du joueur qui joue.
* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
*/
void tourJoueur(Jeu& jeu, int couleur, bool dev = false);

/**
* @brief Lance le jeu.
* 
* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
*
* @return Couleur du gagnant.
*/
int jouer(bool dev = false);

#endif