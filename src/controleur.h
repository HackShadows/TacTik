#ifndef CONTROLEUR_H
#define CONTROLEUR_H

/**
* @brief Contient la déclaration de la classe Controleur.
*/
#include "core/Jeu.h"
#include "sdl/AffichageGraphique.h"
#include "txt/AffichageConsole.h"

#include <array>


/**
* @class Controleur
*
* @brief Permet de jouer une partie.
*/
class Controleur {

	private:
		ImageConsole * console; ///<Représente le contenu à afficher lors d'un affichage console.
		ImageViewer * graphique; ///<Représente la fenêtre à afficher lors d'un affichage graphique.
		bool versionGraphique; ///<True pour une version graphique, false pour une version console.
		int joueurActif; ///<Indice du joueur qui joue.
		bool running; ///<False pour arrêter la partie, true sinon.

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
		* @brief Renvoie running.
		*
		* @return False pour arrêter la partie, true sinon.
		*/
		bool getRunning();

		/**
		* @brief Renvoie le jeu en cours.
		*
		* @param indJoueurActif Indice du joueur qui joue.
		*/
		void setJoueurActif(int indJoueurActif);

		/**
		* @brief Permet de saisir un entier l'identifiant d'un pion.
		*
		* @param coutMessage Message à afficher (non obligatoire).
		*
		* @return Identifiant saisi par l'utilisateur (valeur renvoyée par défaut 0).
		*/
		int getIdPion(string coutMessage = "");

		/**
		* @brief Permet de saisir un entier en gérant les erreurs de saisi.
		*
		* @param coutMessage Message à afficher (non obligatoire).
		*
		* @return Entier saisi par l'utilisateur (valeur renvoyée par défaut 0).
		*/
		int saisirEntier(string coutMessage = "");

		/**
		* @brief Permet de saisir un caractère en gérant les erreurs de saisi.
		*
		* @param coutMessage Message à afficher (non obligatoire).
		* @param choix Entier pour indiquer la valeur des boutons (0 : 4/6 ; 1 : A/D ; 2 : O/N)
		*
		* @return Caractère saisi par l'utilisateur (valeur renvoyée par défaut '0').
		*/
		char saisirCaractere(string coutMessage = "", int choix = -1);

		/**
		* @brief Permet d'afficher le message passé en paramètre.
		*
		* @param coutMessage Message à afficher.
		*/
		void afficherMessage(string coutMessage = "");

		/**
		* @brief Affiche le message d'attente entre deux tours.
		*
		* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
		*/
		void attenteTour(bool dev = false);

		/**
		* @brief Joue la carte passée en paramètre.
		*
		* @param valCarte Valeur de la carte jouée par le joueur.
		* @param coequipier True si le joueur joue pour son coéquipier, false sinon (géré automatiquement).
		* @param joker True si la carte passée en paramètre est un joker, false sinon (géré automatiquement).
		*
		* @return True si la carte a pu être jouée, False sinon.
		*/
		bool jouerCarte(int valCarte, bool coequipier = false, bool joker = false);

		/**
		* @brief Récupère la carte que le joueur souhaite jouer.
		*
		* @param coutMessage Message à afficher.
		* @param joueur Le joueur à qui est demandée la carte.
		* 
		* @return La valeur de la carte choisie par le joueur.
		*/
		int choixCarte(string coutMessage, const Joueur& joueur);

		/**
		* @brief Effectue l'échange de cartes entre les joueurs au début de chaque tour.
		*/
		void echangeDeCartes();

		/**
		* @brief Effectue un tour de jeu pour un joueur.
		*
		* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
		*/
		void tourJoueur(bool dev = false);

		/**
		* @brief Affiche les gagnants de la partie.
		* 
		* @param couleurVainqueur Couleur du vainqueur.
		*/
		void afficherVainqueur(int couleurVainqueur);

		/**
		* @brief Gère les évenenements
		*
		* @param event L'évenement à gérer.
		*
		* @return Deux entiers : le numéro de l'étape correspondant à l'action effectuée par le joueur, 
		* et la valeur associée (numéro de la carte, indice de la case ...)
		*/
		array<int, 2> gestionEvent(SDL_Event event);

		/**
		* @brief Affiche le jeu.
		*
		* @param etapeActuel Etape en cours d'éxecution (-1 = Attente entre deux tours ; 1 = Attente d'une carte ; 2 =  ; 3 = ).
		* @param coutMessage Message à afficher.
		* 
		* @return La valeur souhaitée (numéro de la carte, indice de la case ...)
		*/
		int afficherJeu(int etapeActuel = -1, string coutMessage = "");
};

/**
* @brief Lance le jeu.
* 
* @param versionGraphique True pour une version console, false pour une version graphique.
* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
*/
void jouer(bool versionGraphique = false, bool dev = false);

#endif