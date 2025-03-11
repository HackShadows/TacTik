#ifndef _Pioche_H
#define _Pioche_H

/**
* @brief Contient la déclaration de la classe Pioche.
*/
#include "Carte.h"
#include <iostream>
using namespace std;

/**
* @class Pioche
*
* @brief Représente la pile de cartes et la carte sur le tas.
*/

class Pioche {

	private:
		Carte tas; ///<Dernière carte jouée par un joueur
		Carte * pile; ///<Pile de cartes à distribuer

	public:
		/**
        * @brief Constructeur de la pioche.
        */
		Pioche();

		/**
        * @brief Met à jour le tas.
		*
		* @param carte Carte venant d'être jouée.
        */
		void setTas(const Carte &carte);

		/**
        * @brief Renvoie la carte se trouvant sur le tas.
		*
		* @return Carte se trouvant sur le tas.
        */
		Carte getTas() const;
};

#endif