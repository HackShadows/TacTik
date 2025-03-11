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
		string image; ///<Chemin relatif vers l'image de la carte
		int valeur; ///<Valeur de la carte (0 : défaut, 1-13, -1 : Joker, -2 : Permutter, 4 : -4)

	public:
		/**
        * @brief Constructeur de la carte.
        */
		Carte();

		/**
        * @brief Défini la valeur et l'image de la carte.
        * 
        * @param valeur Valeur de la carte
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

		/**
        * @brief Renvoie True si la carte n'a pas encore été jouée par le joueur, False sinon.
        * 
        * @return un booléen
        */
		bool estDansMain() const;

		/**
        * @brief Met à jour la jouabilité de la carte.
        * 
        * @param jouee Booléen qui indique si la carte est jouable
        */
		void setJouee(bool jouee);
};

#endif