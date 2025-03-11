#ifndef _Plateau_H
#define _Plateau_H

/**
* @brief Contient la déclaration de la classe Plateau.
*/
#include "Pioche.h"
#include "Piece.h"
#include "Joueur.h"
#include <iostream>
using namespace std;

/**
* @class Plateau
*
* @brief Représente le plateau de jeu.
*/

class Plateau {

	private:
	Piece cases[64];
	Pioche pioche;
	string image;
	Joueur joueurs[6];
};

#endif