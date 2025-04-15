#ifndef CONTROLEUR_H
#define CONTROLEUR_H

/**
* @brief Contient la déclaration de la classe Controleur.
*/
#include "core/Jeu.h"
#include "sdl/AffichageGraphique.h"
#include "txt/AffichageConsole.h"


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
		*
		* @return Caractère saisi par l'utilisateur (valeur renvoyée par défaut '0').
		*/
		char saisirCaractere(string coutMessage = "");

		/**
		* @brief Permet d'afficher le message passé en paramètre.
		*
		* @param coutMessage Message à afficher.
		*/
		void afficherMessage(string coutMessage = "");

		/**
		* @brief Affiche le message d'attente entre deux tours.
		*
		* @param couleur Couleur du joueur actif.
		* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
		*/
		void attenteTour(int couleur, bool dev = false);

		/**
		* @brief Joue la carte passée en paramètre.
		*
		* @param valCarte Valeur de la carte jouée par le joueur.
		* @param couleur Couleur du joueur.
		* @param coequipier True si le joueur joue pour son coéquipier, false sinon (géré automatiquement).
		* @param joker True si la carte passée en paramètre est un joker, false sinon (géré automatiquement).
		*
		* @return True si la carte a pu être jouée, False sinon.
		*/
		bool jouerCarte(int valCarte, int couleur, bool coequipier = false, bool joker = false);

		/**
		* @brief Récupère la carte que le joueur souhaite jouer.
		*
		* @param coutMessage Message à afficher avant le cin.
		* @param joueur Le joueur à qui est demandée la carte.
		* 
		* @return Valeur de la carte choisie par le joueur.
		*/
		int choixCarte(string coutMessage, const Joueur& joueur);

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
		* @brief Gère les évenenements
		*
		* @param event L'évenement à gérer
		* @param running Booléen qui definit si le jeu continue de tourner
		* @param joueurActif Couleur du joueur qui joue.
		* @param cartes_visibles True si les cartes du joueur sont visibles, False sinon.
		*/
		void gestionEvent(SDL_Event event, bool &running, int &joueurActif, bool &cartes_visibles);

		/**
		* @brief Affiche le jeu.
		*
		* @param running Permet d'arrêter ou continuer la partie.
		* @param joueurActif Indice du joueur qui joue.
		*/
		void afficherJeu(bool &running, int &joueurActif, bool &cartes_visibles);
};

/**
* @brief Lance le jeu.
* 
* @param versionGraphique True pour une version console, false pour une version graphique.
* @param dev True si exécuté en mode développeur, false sinon (géré automatiquement).
*/
void jouer(bool versionGraphique = false, bool dev = false);

#endif