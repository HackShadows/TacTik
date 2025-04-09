#ifndef CONTROLEUR_H
#define CONTROLEUR_H

#include "core/Jeu.h"
#include "sdl/AffichageSDL.h"
#include "txt/AffichageConsole.h"

/**
* @brief Joue la carte passée en paramètre.
*
* @param valCarte Valeur de la carte jouée par le joueur.
* @param couleur Couleur du joueur.
* @param getIdPion Fonction permettant de récupérer l'identifiant d'un pion.
* @param cinInt Fonction permettant de récupérer un entier.
* @param cinChar Fonction permettant de récupérer un caractère.
* @param message Fonction permettant d'afficher un message.
* @param coequipier True si le joueur joue pour son coéquipier, false sinon (géré automatiquement).
* @param joker True si la carte passée en paramètre est un joker, false sinon (géré automatiquement).
*
* @return True si la carte a pu être jouée, False sinon.
*/
bool jouerCarte(int valCarte, int couleur, int (getIdPion)(const Plateau &, string), int (cinInt)(string), char (cinChar)(string), void (message)(string) = messageDefaut, bool coequipier = false, bool joker = false);

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
* @brief Affiche les gagnants de la partie.
* 
* @param couleurVainqueur Couleur du vainqueur.
* @param versionGraphique True pour une version console, false pour une version graphique.
*/
void afficherVainqueur(int couleurVainqueur, bool versionGraphique);

/**
* @brief Lance le jeu.
* 
* @param versionGraphique True pour une version console, false pour une version graphique.
* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
*/
void jouer(bool versionGraphique = false, bool dev = false);

#endif