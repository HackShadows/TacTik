#include <iostream>
using namespace std;


class Carte {

	private:
	string image;
	int valeur;
};

class Pioche {

	private:
	Carte tas;
	Carte pile[100];
};

class Piece {

	private:
	bool pieu;
	string image;
	int id, couleur;
};


class Joueur {

	private:
	bool maison[4];
	Carte main[4];
	string pseudo;
	int couleur, reserve;
};

class Plateau {

	private:
	Piece cases[64];
	Pioche pioche;
	string image;
	Joueur joueurs[6];
};