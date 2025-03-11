#ifndef _Joueur_H
#define _Joueur_H

#include "Carte.h"
#include <iostream>
using namespace std;


class Joueur {

	private:
	bool maison[4];
	Carte main[4];
	string pseudo;
	int couleur, reserve;
};

#endif