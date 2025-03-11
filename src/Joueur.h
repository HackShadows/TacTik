#ifndef _Joueur_H
#define _Joueur_H

/**
* @brief Contient la déclaration de la classe Joueur.
*/
#include "Carte.h"
#include <iostream>
using namespace std;

/**
* @class Joueur
*
* @brief Représente un joueur, avec sa main et sa maison.
*/

class Joueur {

	private:
		bool maison[4]; ///<La maison du joueur
		Carte * main; ///<Les 4 cartes de la main du joueur
		string pseudo; ///<Le pseudo du joueur
		int couleur, reserve; ///<La couleur et le nombre de pions en réserve du joueur

	public:
		/**
        * @brief Constructeur du joueur.
        */
		Joueur();

		/**
        * @brief Défini la couleur et le pseudo du joueur.
        * 
        * @param pseudo Pseudonyme du joueur
		* @param couleur Couleur du joueur (1 : vert, 2 : rouge, 3 : bleu, 4 : jaune, 5 : blanc, 6 : noir)
        */
		void setJoueur(string pseudo, int couleur);

		/**
        * @brief Renvoie la carte que le joueur souhaite jouer.
        * 
        * @param valeur Valeur de la carte à renvoyer
		* @return Pointeur constant vers la carte jouée
        */
		const Carte& jouerCarte(int valeur);

		/**
        * @brief Renvoie True si la maison du joueur est remplie, False sinon.
        * 
        * @return un booléen.
        */
		bool maisonRemplie() const;
};

#endif