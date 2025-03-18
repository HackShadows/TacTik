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
		bool jouee; ///<Indique si la carte est jouable
		int valeur; ///<Valeur de la carte (0 : défaut, 1-13, -1 : Joker, -2 : Permutter, 4 : -4)

	public:
		/**
        * @brief Constructeur de la carte.
        */
		Carte();

		/**
        * @brief Défini la valeur de la carte.
        * 
        * @param val Valeur de la carte
        */
		void setCarte(int val);

		/**
        * @brief Renvoie la valeur de la carte.
        * 
        * @return Valeur de la carte
        */
		int getValeur() const ;

		/**
        * @brief Renvoie True si la carte n'a pas encore été jouée par le joueur, False sinon.
        * 
        * @return un booléen
        */
		bool estDansMain() const;

		/**
        * @brief Met à jour la jouabilité de la carte.
        * 
        * @param joue Booléen qui indique si la carte est jouable
        */
		void setJouee(bool joue);
};

#endif