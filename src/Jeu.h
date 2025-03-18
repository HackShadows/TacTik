#ifndef _Jeu_H
#define _Jeu_H

/**
* @brief Contient la déclaration de la classe Carte.
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
        int nb_joueurs;
		Plateau plateau; ///<Indique si la carte est jouable
		Pioche pioche; ///<Chemin relatif vers l'image de la carte
		Joueur * joueurs; ///<Valeur de la carte (0 : défaut, 1-13, -1 : Joker, -2 : Permutter, 4 : -4)

	public:
		/**
        * @brief Constructeur par défaut du jeu.
        */
		Jeu();

        /**
        * @brief Constructeur de la carte.
        */
		Jeu(int nbJ);

		/**
        * @brief Défini la valeur et l'image de la carte.
        * 
        * @param val Valeur de la carte
		* @param chemin Chemin relatif vers l'image de la carte
        */
		void setCarte(int val, string chemin);

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
        * @param joue Booléen qui indique si la carte est jouable
        */
		void setJouee(bool joue);
};

#endif