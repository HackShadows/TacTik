#ifndef _Plateau_H
#define _Plateau_H

/**
* @brief Contient la déclaration de la classe Plateau.
*/
#include "Pion.h"
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

		/**
        * @brief Renvoie le nombre de cases du plateau.
        * 
        * @return Nombre de cases.
        */
		int getNbCase();

		/**
        * @brief Renvoie le pion se trouvant à l'indice 'indice'.
		* 
		* @param indice Indice où chercher le pion.
        * 
        * @return Pion se trouvant à l'indice 'indice'.
        */
		Pion& getPion(int indice);

		/**
        * @brief Affiche le plateau de jeu.
        */
		void afficher() const;
};

#endif