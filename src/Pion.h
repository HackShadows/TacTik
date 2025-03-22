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
		bool pieu; ///<État du pion (Pieu : true ; Pion : false)
		int position;	///<Position du pion sur le plateau (-1 : reserve, -2 : maison)
		int id, couleur; ///<Id (1-24), couleur du pion

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
        * @brief Défini l'identifiant et la couleur du pion.
        * 
        * @param identifiant Id du pion
        */
		void setPion(int identifiant);

		/**
        * @brief Modifie la position du pion.
        * 
        * @param indice Nouvelle position du pion sur le plateau.
        */
	   	void setPos(int indice);

		/**
        * @brief Renvoie l'id du pion.
		*
		* @return L'id pion.
        */
		int getId();

		/**
        * @brief Renvoie la position du pion.
		*
		* @return La position du pion.
        */
	   	int getPos();

		/**
        * @brief Renvoie True si c'est un pieu, False pour un pion.
		*
		* @return Le booléen correspondant.
        */
	   	bool estPieu();

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