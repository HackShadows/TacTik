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
		int nbCases; ///<Nombres de cases

	public:
		/**
        * @brief Constructeur par défaut.
        *
        * Crée le plateau de jeu pour 4 joueurs.
        */
		Plateau();

		/**
        * @brief Destructeur du plateau.
        */
	   	~Plateau();

		/**
        * @brief Constructeur avec paramètre.
        *
        * Crée le plateau de jeu en fonction du nombre de joueurs.
        * 
        * @param nbJ Nombre de joueurs
        */
		Plateau(int nbJ);

		int getNbCase();

		Pion& getPion(int indice);

		/**
        * @brief Affiche le plateau de jeu.
        */
		void afficher() const;
};

#endif