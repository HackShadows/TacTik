
#include "Jeu.h"

/**
* @brief Affiche un nombre prenant 2 espaces dans le terminal.
*
* @param id Le nombre que l'on veut afficher
*/
void affichageId(int id);

/**
* @brief Affiche la maison d'une couleur dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
* @param couleur la couleur dont on veut afficher la maison
*/
void affichageMaison(const Jeu & jeu, int couleur);

/**
* @brief Affiche la premiere ligne d'une partie 4 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void ligneHaut(const Jeu & jeu);

/**
* @brief Affiche la deuxieme ligne d'une partie 4 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void maisonHaut(const Jeu & jeu);

/**
* @brief Affiche la troisieme ligne d'une partie 4 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void reserveHaut(const Jeu & jeu);

/**
* @brief Affiche les lignes du milieu d'une partie 4 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void milieu(const Jeu & jeu);

/**
* @brief Affiche les reserves sur la 3eme ligne du bas d'une partie 4 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void reserveBas(const Jeu & jeu);

/**
* @brief Affiche les maisons sur la deuxieme ligne du bas d'une partie 4 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void maisonBas(const Jeu & jeu);

/**
* @brief Affiche la dernière ligne d'une partie 4 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void ligneBas(const Jeu & jeu);

/**
* @brief Affiche la premiere ligne d'une partie 6 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void ligneHaut6p(const Jeu & jeu);

/**
* @brief Affiche la deuxieme ligne d'une partie 6 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void maisonHaut6p(const Jeu & jeu);

/**
* @brief Affiche la troisieme ligne d'une partie 6 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void reserveHaut6p(const Jeu & jeu);

/**
* @brief Affiche les lignes du milieu d'une partie 6 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void milieu6p(const Jeu & jeu);

/**
* @brief Affiche les reserves sur la 3eme ligne du bas d'une partie 6 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void reserveBas6p(const Jeu & jeu);

/**
* @brief Affiche les maisons sur la deuxieme ligne du bas d'une partie 6 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void maisonBas6p(const Jeu & jeu);

/**
* @brief Affiche la dernière ligne d'une partie 6 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void ligneBas6p(const Jeu & jeu);

/**
* @brief Affiche la grille entière d'une partie 4 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void grille4p(const Jeu & jeu);

/**
* @brief Affiche la grille entière d'une partie 6 joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void grille6p(const Jeu & jeu);

/**
* @brief Affiche les cartes des joueurs dans le terminal.
*
* @param jeu Le jeu que l'on veut afficher
*/
void affichageCarte(const Jeu & jeu);

/**
* @brief Affiche l'état du jeu sous format texte dans le terminal.
*
* @param jeu Le jeu à afficher.
*/
void affichageTexte(const Jeu & jeu);