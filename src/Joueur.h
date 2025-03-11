#ifndef _Joueur_H
#define _Joueur_H

/**
* @brief Contient la déclaration de la classe Joueur.
*/
#include "Carte.h"
#include <iostream>
using namespace std;

/**
* @class Plateau
*
* @brief Représente le plateau de jeu.
*/

class Joueur {

	private:
	bool maison[4];
	Carte main[4];
	string pseudo;
	int couleur, reserve;
};

#endif