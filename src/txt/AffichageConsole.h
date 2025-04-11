#ifndef AFFICHERTXT_H
#define AFFICHERTXT_H

#include "../core/Jeu.h"


/**
* @brief Clear le terminal.
*/
void clearTerminal();

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
* @brief Contient la déclaration de la classe ImageConsole.
*/
class ImageConsole {
	private:
		Jeu jeu; ///<Jeu à afficher
		int nbCase; ///<Nombre de cases du plateau de jeu

	public:
		/**
        * @brief Constructeur avec paramètres de la classe ImageConsole
        * 
		* @param nbJoueurs Nombre de joueurs
		* @param nbIA Nombre d'IA
        */
	   ImageConsole(int nbJoueurs = 4, int nbIA = 0);

	   /**
	   * @brief Destructeur de la classe ImageConsole
	   */
	   ~ImageConsole();

	   /**
	   * @brief Renvoie le jeu en cours.
	   *
	   * @return Le jeu en cours.
	   */
	   Jeu& getJeu();
	
		/**
		* @brief Affiche la maison d'une couleur dans le terminal.
		*
		* @param couleur La couleur dont on veut afficher la maison
		*/
		void affichageMaison(int couleur);

		/**
		* @brief Affiche la premiere ligne d'une partie dans le terminal.
		*
		* @param joueurActif Le joueur qui joue
		*/
		void ligneHaut(int joueurActif);

		/**
		* @brief Affiche la deuxieme ligne d'une partie dans le terminal.
		*
		* @param joueurActif Le joueur qui joue

		*/
		void maisonHaut(int joueurActif);

		/**
		* @brief Affiche la troisieme ligne d'une partie dans le terminal.
		*
		* @param joueurActif Le joueur qui joue
		*/
		void reserveHaut(int joueurActif);

		/**
		* @brief Affiche la quatrième ligne d'une partie dans le terminal.
		*/
		void idPionHaut();

		/**
		* @brief Affiche les lignes du milieu d'une partie dans le terminal.
		*/
		void milieu();

		/**
		* @brief Affiche la quatrième ligne du bas d'une partie dans le terminal.
		*/
		void idPionBas();

		/**
		* @brief Affiche les reserves sur la 3eme ligne du bas d'une partie dans le terminal.
		*
		* @param joueurActif Le joueur qui joue
		*/
		void reserveBas(int joueurActif);

		/**
		* @brief Affiche les maisons sur la deuxieme ligne du bas d'une partie dans le terminal.
		*
		* @param joueurActif Le joueur qui joue
		*/
		void maisonBas(int joueurActif);

		/**
		* @brief Affiche la dernière ligne d'une partie dans le terminal.
		*
		* @param joueurActif Le joueur qui joue
		*/
		void ligneBas(int joueurActif);


		/**
		* @brief Affiche la grille entière d'une partie dans le terminal.
		*
		* @param joueurActif Le joueur qui joue
		*/
		void grille(int joueurActif);


		/**
		* @brief Affiche les cartes des joueurs dans le terminal.
		*
		* @param indiceJoueur L'indice du joueur dont on veut afficher les cartes.
		* @param joueurActif Le joueur qui joue
		*/
		void affichageCarte(int indiceJoueur, int joueurActif);

		/**
		* @brief Affiche l'état du jeu sous format texte dans le terminal.
		*
		* @param joueurActif Le joueur qui joue
		*/
		void affichageTexte(int joueurActif);
};

#endif