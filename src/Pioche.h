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
		Carte pile[54]; ///<Pile de cartes à distribuer

	public:
		/**
        * @brief Constructeur de la pioche.
        */
		Pioche();

		/**
        * @brief Destructeur de la pioche.
        */
	   	~Pioche();

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

		/**
        * @brief Renvoie la pile de cartes.
		* 
		* @param indice Indice de la carte à récupérer.
		*
		* @return La pile.
        */
		Carte* getCarte(int indice) const;

		/**
        * @brief Test les fonctionnalités de la classe.
        *
        * Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
        * et que les données membres de l'objet sont conformes en tout temps.
        */
	   	static void testRegression();

		/**
        * @brief Affiche la pioche.
        */
	   	void afficher() const;
};

#endif