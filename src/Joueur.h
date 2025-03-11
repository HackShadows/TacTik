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
		const Carte * main[4]; ///<Les 4 cartes de la main du joueur
		string pseudo; ///<Le pseudo du joueur
		int couleur, reserve; ///<La couleur et le nombre de pions en réserve du joueur

	public:
		/**
        * @brief Constructeur avec paramètres.
        *
        * Crée le joueur.
        * 
        * @param nbJoueurs Nombre de joueurs
        */
		Joueur(string pseudo, int couleur);

		/**
        * @brief Renvoie la carte se trouvant.
        *
        * Crée le plateau de jeu en fonction du nombre de joueurs.
        * 
        * @param nbJoueurs Nombre de joueurs
        */
		const Carte* jouerCarte(int valeur);

		/**
        * @brief Constructeur avec paramètre.
        *
        * Crée le plateau de jeu en fonction du nombre de joueurs.
        * 
        * @param nbJoueurs Nombre de joueurs
        */
		bool maisonRemplie() const;
};

#endif