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
		int valeur; ///<Valeur de la carte (0 : défaut, -1 : Joker, Cartes 1-13 (sauf 4 et 11), 11 : Permutter, -4 : Carte -4)
		
	public:
		/**
		* @brief Constructeur par défaut de la carte.
		*/
		Carte();

		/**
		* @brief Constructeur avec paramètre de la carte.
		* 
		* @param val Valeur de la carte.
		*/
		Carte(int val);

		/**
		* @brief Destructeur de la carte.
		*/
		~Carte();

		/**
		* @brief Renvoie la valeur de la carte.
		* 
		* @return Valeur de la carte.
		*/
		int getValeur() const;

		/**
		* @brief Teste les fonctionnalités de la classe.
		*
		* Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
		* et que les données membres de l'objet sont conformes en tout temps.
		*/
		static void testRegression();
};

#endif