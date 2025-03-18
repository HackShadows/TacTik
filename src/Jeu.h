#ifndef _Jeu_H
#define _Jeu_H

/**
* @brief Contient la déclaration de la classe Jeu.
*/
#include "Joueur.h"
#include "Pioche.h"
#include "Plateau.h"
#include <iostream>
using namespace std;

/**
* @class Jeu
*
* @brief Représente l'ensemble des règles du jeu.
*/

class Jeu {

	private:
        int nbJoueurs; ///<Nombres de joueurs.
		Plateau plateau; ///<Le plateau de jeu.
		Pioche pioche; ///<La pioche et le tas.
		Joueur * joueurs; ///<Tableau de 4 ou 6 joueurs.

	public:
		/**
        * @brief Constructeur par défaut du jeu.
        */
		Jeu();

        /**
        * @brief Constructeur du jeu.
        */
		Jeu(int nbJ);

        /**
        * @brief Destructeur du jeu.
        */
		~Jeu();

        /**
        * @brief Renvoie le plateau de jeu.
		*
		* @return Le plateau de jeu.
        */
		Plateau getPlateau() const;

        /**
        * @brief Distribue 4 cartes à chaque joueur.
        */
		void distribuer();
};

#endif