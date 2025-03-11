#ifndef _Carte_H
#define _Carte_H

#include "Pioche.h"
#include "Piece.h"
#include "Joueur.h"
#include <iostream>
using namespace std;


class Plateau {

	private:
	Piece cases[64];
	Pioche pioche;
	string image;
	Joueur joueurs[6];
};

#endif