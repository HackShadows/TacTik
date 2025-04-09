#ifndef CONTROLEUR_H
#define CONTROLEUR_H

/**
* @brief Contient la déclaration de la classe Controleur.
*/
#include "core/Jeu.h"
#include "sdl/AffichageSDL.h"
#include "txt/AffichageConsole.h"

/**
* @brief Permet de saisir un entier l'identifiant d'un pion.
*
* @param coutMessage Message à afficher avant le cin (non obligatoire).
* @param plateau Plateau de jeu (géré automatiquement).
*
* @return Identifiant saisi par l'utilisateur (valeur renvoyée par défaut 0).
*/
int getIdPion(const Plateau &plateau, string coutMessage);

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
* @brief Permet d'afficher le message passé en paramètre.
*
* @param coutMessage Message à afficher.
*/
void message(string coutMessage = "");

/**
* @class Controleur
*
* @brief Permet de jouer une partie.
*/
class Controleur {

	private:
		Jeu jeu; ///<Représente l'ensemble des éléments du jeu.
		//ImageViewer im; ///<Représente la fenêtre à afficher lors d'un affichage graphique.
		bool versionGraphique; ///<True pour une version graphique, false pour une version console.

	public:
		/**
        * @brief Constructeur par défaut du controleur.
        */
		Controleur();

		/**
		* @brief Constructeur avec paramètres du controleur.
		*
		* @param nbJ Nombre de joueurs.
		* @param nbIA Nombre d'IA.
		* @param affichageGraphique True pour une version graphique, false pour une version console.
		*/
		Controleur(int nbJ, int nbIA = 0, bool affichageGraphique = false);

		/**
		* @brief Destructeur du controleur.
		*/
		~Controleur();

		/**
		* @brief Renvoie le jeu en cours.
		*
		* @return Le jeu en cours.
		*/
		Jeu& getJeu();

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
		*/
		void echangeDeCartes();

		/**
		* @brief Effectue un tour de jeu pour un joueur.
		*
		* @param couleur Couleur du joueur qui joue.
		* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
		*/
		void tourJoueur(int couleur, bool dev = false);

		/**
		* @brief Affiche les gagnants de la partie.
		* 
		* @param couleurVainqueur Couleur du vainqueur.
		*/
		void afficherVainqueur(int couleurVainqueur);

		/**
		* @brief Affiche l'image de jeu en version graphique.
		*/
		void afficherImage();
};

/**
* @brief Lance le jeu.
* 
* @param versionGraphique True pour une version console, false pour une version graphique.
* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
*/
void jouer(bool versionGraphique = false, bool dev = false);

#endif