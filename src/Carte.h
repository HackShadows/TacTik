#ifndef _Carte_H
#define _Carte_H

/**
* @brief Contient la déclaration de la classe Carte.
*/
#include <iostream>
using namespace std;

/**
* @class Carte
*
* @brief Représente une carte à jouer.
*/

class Carte {

	private:
		string image; ///<Chemin relatif vers l'image de la carte
		int valeur; ///<Valeur de la carte

	public:
		/**
        * @brief Constructeur de la carte.
        */
		Carte();

		/**
        * @brief Défini la valeur et l'image de la carte.
        * 
        * @param valeur Valeur de la carte (1-13, 0 : Joker, -1 : Permutter, 4 : -4)
		* @param chemin Chemin relatif vers l'image de la carte
        */
		void setCarte(int valeur, string chemin);

		/**
        * @brief Renvoie la valeur de la carte.
        * 
        * @return Valeur de la carte
        */
		int getValeur() const ;

		/**
        * @brief Renvoie l'image de la carte.
        * 
        * @return Image de la carte
        */
		string getImage() const;
};

#endif