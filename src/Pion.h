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
        * @brief Destructeur du pion.
        */
	   	~Pion();

		/**
        * @brief Défini les données membres du pion.
        * 
        * @param identifiant Id du pion
        */
		void setPion(int identifiant);

		/**
        * @brief Renvoie l'id du pion.
		*
		* @return L'id pion.
        */
		int getId();

		/**
        * @brief Test les fonctionnalités de la classe.
        *
        * Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
        * et que les données membres de l'objet sont conformes en tout temps.
        */
	   	static void testRegression();

		/**
        * @brief Affiche le pion.
        */
	   	void afficher() const;
};

#endif