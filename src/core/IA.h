#ifndef _IA_H
#define _IA_H

/**
* @brief Contient la déclaration de la classe IA.
*/
#include "Joueur.h"
#include <iostream>
#include <vector>
#include <utility>

using namespace std;


class Jeu;

/**
* @class IA
*
* @brief Représente une ia.
*/
class IA {

public:
	/**
	* @brief Constructeur de l'ia.
	*/
	IA();

	/**
	* @brief Destructeur de l'ia.
	*/
	~IA();

	/**
	* @brief Permet à l'ia d'effectuer un coups parmis ses différents coups possibles.
	*/
	void jouerCoup(Jeu &jeu, int couleur) const;

	/**
	* @brief Permet à l'ia d'effectuer un coups parmis ses différents coups possibles.
	*/
	int jouerCarte(Jeu &jeu, int indice);

	/**
	* @brief Génère la liste des coups possibles.
	*
	* @return Liste de paires de coups possible contenant l'id du pion et sa nouvelle position.
	*/
	vector<pair<int, int>> genererCoups(Jeu &jeu, int couleur) const;

	/**
	* @brief Teste les fonctionnalités de la classe.
	*
	* Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
	* et que les données membres de l'objet sont conformes en tout temps.
	*/
	static void testRegression();
};

#endif