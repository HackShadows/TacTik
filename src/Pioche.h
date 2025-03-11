#ifndef _Pioche_H
#define _Pioche_H

/**
* @brief Contient la déclaration de la classe Pioche.
*/
#include "Carte.h"
#include <iostream>
using namespace std;

/**
* @class Pioche
*
* @brief Représente la pile de cartes et la carte sur le tas.
*/

class Pioche {

	private:
	Carte tas; ///<Dernière carte jouée par un joueur
	Carte pile[100]; ///<Pile de cartes à distribuer

	public:
	Pioche();

	void melanger();
};

#endif