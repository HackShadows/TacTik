#ifndef _Plateau_H
#define _Plateau_H

/**
* @brief Contient la déclaration de la classe Plateau.
*/
#include "Pioche.h"
#include "Pion.h"
#include "Joueur.h"
#include <iostream>
using namespace std;

/**
* @class Plateau
*
* @brief Représente le plateau de jeu.
*/

class Plateau {

	private:
		Pion * cases; ///<Les 64 ou 96 cases du plateau de jeu
		Pioche pioche; ///<La pioche et le tas
		string image; ///<Chemin relatif vers l'image du plateau
		Joueur * joueurs; ///<Tableau de 4 ou 6 joueurs

	public:
		/**
        * @brief Constructeur avec paramètre.
        *
        * Crée le plateau de jeu en fonction du nombre de joueurs.
        * 
        * @param nbJoueurs Nombre de joueurs
        */
		Plateau(int nbJoueurs);

		/**
        * @brief Distribue 4 cartes à chaque joueur.
        */
		void distribuer();

		/**
        * @brief Affiche le plateau de jeu.
        */
		void afficher() const;
};

#endif