#ifndef _IA_H
#define _IA_H

/**
* @brief Contient la déclaration de la classe IA.
*/
#include "Joueur.h"
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Jeu;

/**
* @class IA
*
* @brief Représente une ia.
*/

class IA {

    private:
		int couleur; ///<Couleur du joueur auquel est associée l'ia.
        
	public:
		/**
        * @brief Constructeur par défaut de l'ia.
        */
		IA();

        /**
		* @brief Constructeur avec paramètres de l'ia.
		*
		* @param id_couleur Couleur du joueur (1 : vert, 2 : rouge, 3 : bleu, 4 : jaune, 5 : noir, 6 : blanc).
		*/
		IA(int id_couleur);

        /**
        * @brief Destructeur de l'ia.
        */
		~IA();

        /**
		* @brief C
		*/
        void jouerCoup(Jeu &jeu, vector<pair<int, int>> vect) const;

        /**
		* @brief Génère la liste des coups possibles.
        *
        * @return Liste de pairs de coups possible contenant l'id du pion et sa nouvelle position.
		*/
		vector<pair<int, int>> genererCoups(Jeu &jeu) const;

        /**
        * @brief Test les fonctionnalités de la classe.
        *
        * Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
        * et que les données membres de l'objet sont conformes en tout temps.
        */
        static void testRegression();
};

#endif