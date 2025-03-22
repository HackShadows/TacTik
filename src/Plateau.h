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
		Pion ** cases; ///<Les 64 ou 96 cases du plateau de jeu
		int nbCases; ///<Nombres de cases

	public:
		/**
        * @brief Constructeur par défaut.
        *
        * Crée le plateau de jeu pour 4 joueurs.
        */
		Plateau();

		/**
        * @brief Constructeur avec paramètre.
        *
        * Crée le plateau de jeu en fonction du nombre de joueurs.
        * 
        * @param nbJ Nombre de joueurs
        */
		Plateau(int nbJ);

		// Désactivation du constructeur par copie et de l'opérateur d'affectation
		Plateau(const Plateau&) = delete;
		Plateau& operator=(const Plateau&) = delete;

        /**
        * @brief Destructeur du plateau.
        */
	   	~Plateau();

		/**
        * @brief Renvoie le nombre de cases du plateau.
        * 
        * @return Nombre de cases.
        */
		int getNbCase() const;

		/**
        * @brief Renvoie le pion se trouvant à l'indice 'indice'.
		* 
		* @param indice Indice où chercher le pion.
        * 
        * @return Pion se trouvant à l'indice 'indice'.
        */
	   	Pion* getPion(int indice) const;

		/**
		* @brief définit la valeur de la case d'indice indice.
		*
		* @param pion Pointeur vers le pion.
		* @param indice Indice de la nouvelle case du pion.

		*/
		void setPion(Pion* pion, int indice);

		/**
		* @brief supprime le pion de la case d'indice indice.
		*
		* @param indice Indice de la case à vider.

		*/
		void viderCase(int indice);

        /**
        * @brief Test les fonctionnalités de la classe.
        *
        * Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
        * et que les données membres de l'objet sont conformes en tout temps.
        */
	   	static void testRegression();

		/**
        * @brief Affiche le plateau de jeu.
        */
		void afficher() const;
};

#endif