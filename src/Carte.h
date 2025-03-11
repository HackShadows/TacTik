#ifndef _Carte_H
#define _Carte_H

/**
* @brief Contient la déclaration de la classe Carte.
*/
#include <iostream>
using namespace std;

/**
* @class Carte
*
* @brief Représente une carte à jouer.
*/

class Carte {

	private:
	string image; ///<Chemin relatif vers l'image de la carte
	int valeur; ///<Valeur de la carte

	public:
	Carte(int valeur, string chemin);

	int getValeur();

	string getImage();
};

#endif