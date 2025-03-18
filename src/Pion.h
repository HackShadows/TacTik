#ifndef _Pion_H
#define _Pion_H

/**
* @brief Contient la déclaration de la classe Piece.
*/
#include <iostream>
using namespace std;

/**
* @class Pion
*
* @brief Représente le pion d'un joueur.
*/

class Pion {

	private:
		bool pieu; ///<État du pion (Pieu/Pion)
		int id, couleur; ///<Id (1-24) et couleur du pion

	public:
		/**
        * @brief Constructeur du pion.
        */
		Pion();

		/**
        * @brief Défini les données membres du pion.
        * 
        * @param identifiant Id du pion
        */
		void setPion(int identifiant);
};

#endif