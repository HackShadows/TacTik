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
		int * cases; ///<Tableau de 64 ou 96 cases les indices des pions (0 par défaut)
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
        * @brief Renvoie l'id du pion se trouvant à l'indice 'indice'.
		* 
		* @param indice Indice où chercher le pion.
        * 
        * @return Id du pion se trouvant à l'indice 'indice'.
        */
	   	int getIdPion(int indice) const;

		/**
		* @brief Définit la valeur de la case d'indice 'indice'.
		*
		* @param id_pion Id du pion à ajouter.
		* @param indice Indice de la nouvelle case du pion.
		*/
		void setPion(int id_pion, int indice);

		/**
		* @brief supprime le pion de la case d'indice 'indice'.
		*
		* @param indice Indice de la case à vider.
		*
		* @return Id du pion se trouvant à l'indice 'indice'.
		*/
		int viderCase(int indice);

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