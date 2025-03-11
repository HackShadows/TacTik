#ifndef _Pion_H
#define _Pion_H

/**
* @brief Contient la déclaration de la classe Piece.
*/
#include <iostream>
using namespace std;

/**
* @class Pion
*
* @brief Représente le pion d'un joueur.
*/

class Pion {

	private:
	bool pieu;
	string image;
	int id, couleur;
};

#endif