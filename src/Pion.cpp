/**
* @brief Contient l'implémentation de la classe Pion.
*/
#include "Pion.h"

#include <iostream>
#include <cassert>

using namespace std;


Pion::Pion(): pieu(true), position(-1), id(0), couleur(0){}

Pion::Pion(int identifiant): pieu(true), position(-1), id(identifiant), couleur((identifiant-1)/4+1) {}

Pion::~Pion() {
    pieu = true;
	position = -1;
    id = 0;
    couleur = 0;
}

void Pion::setPos(int indice) {
	position = indice;
}

void Pion::setPieu(bool etat) {
	pieu = etat;
}

int Pion::getId() {
    return id;
}

int Pion::getPos() {
    return position;
}

bool Pion::estPieu() {
    return pieu;
}

void Pion::testRegression(){
    {
		Pion pion2;
		assert(pion2.pieu);
		assert(pion2.position == -1);
		assert(pion2.id == 0);
		assert(pion2.couleur == 0);
		cout << "Constructeur par défaut valide !" << endl;

		Pion pion(4);
		assert(pion.pieu);
		assert(pion.position == -1);
		assert(pion.id == 4);
		assert(pion.couleur == 1);
		cout << "Constructeur avec paramètre valide !" << endl;

		pion.setPos(3);
		assert(pion.position == 3);
		cout << "setPos valide !" << endl;

		assert(pion.getId()==4);
		cout << "getPion valide !" << endl;

		assert(pion.getPos()==3);
		cout << "getPos valide !" << endl;

		assert(pion.estPieu());
		cout << "estPieu valide !" << endl;

		pion.setPieu(false);
		assert(!pion.estPieu());
		cout << "setPieu valide !" << endl;

		/*cout << "Méthode affichage : " << endl;
		pion.afficher();
		cout << "afficher valide !" << endl;*/
	}
    cout << "Destructeur valide !" << endl;
}

void Pion::afficher() const {
    cout << "Id : " << id << " ; Couleur : " << couleur << " ; C'est un " << ((pieu) ? "pieu":"pion") << endl;
}