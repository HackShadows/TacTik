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
	Carte main[4]; ///<Le 4 cartes de la main du joueur
	string pseudo; ///<Le pseudo du joueur
	int couleur, reserve; ///<La couleur et le nombre de pions en réserve du joueur
};

#endif