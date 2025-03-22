/**
* @brief Contient l'implémentation de la classe Pion.
*/
#include "Pion.h"

#include <iostream>
#include <cassert>

using namespace std;


Pion::Pion(): pieu(true), position(-1), id(0), couleur(0){}

Pion::~Pion() {
    pieu = true;
	position = -1;
    id = 0;
    couleur = 0;
}

void Pion::setPion(int identifiant) {
    id = identifiant;
    couleur = (id/4)+1;
}

void Pion::setPos(int indice) {
	position = indice;
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
		Pion pion;
		assert(pion.pieu);
		assert(pion.position == -1);
		assert(pion.id == 0);
		assert(pion.couleur == 0);
		cout << "Constructeur valide !" << endl;

		pion.setPion(4);
		assert(pion.id == 4);
		cout << "setPion valide !" << endl;

		pion.setPos(3);
		assert(pion.position == 3);
		cout << "setPos valide !" << endl;

		assert(pion.getId()==4);
		cout << "getPion valide !" << endl;

		assert(pion.getPos()==3);
		cout << "getPos valide !" << endl;

		assert(pion.estPieu());
		cout << "estPieu valide !" << endl;

		/*cout << "Méthode affichage : " << endl;
		pion.afficher();
		cout << "afficher valide !" << endl;*/
	}
    cout << "Destructeur valide !" << endl;
}

void Pion::afficher() const {
    cout << "Id : " << id << " ; Couleur : " << couleur << " ; C'est un " << ((pieu) ? "pieu":"pion") << endl;
}