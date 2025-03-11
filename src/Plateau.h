#ifndef _Plateau_H
#define _Plateau_H

/**
* @brief Contient la déclaration de la classe Plateau.
*/
#include "Pioche.h"
#include "Pion.h"
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
	Piece cases[64]; ///<Les 64 cases du plateau de jeu
	Pioche pioche; ///<La pioche et le tas
	string image; ///<Chemin relatif de l'image du plateau
	Joueur joueurs[6]; ///<Tableau des 6 joueurs
};

#endif