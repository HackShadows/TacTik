#ifndef _Joueur_H
#define _Joueur_H

/**
* @brief Contient la déclaration de la classe Joueur.
*/
#include "Carte.h"
#include <iostream>
using namespace std;

/**
* @class Joueur
*
* @brief Représente un joueur, avec sa main et sa maison.
*/

class Joueur {

	private:
		string pseudo; ///<Le pseudo du joueur
		int couleur, reserve; ///<La couleur et le nombre de pions en réserve du joueur
		Carte* main[4]; ///<Les 4 cartes de la main du joueur
		int maison[4] = {0}; ///<La maison du joueur

	public:
		/**
        * @brief Constructeur du joueur.
        */
		Joueur();

		/**
		* @brief Constructeur du joueur.
		*
		* @param id_couleur Couleur du joueur (1 : vert, 2 : rouge, 3 : bleu, 4 : jaune, 5 : noir, 6 : blanc)
		*/
		Joueur(int id_couleur);

        /**
        * @brief Destructeur du joueur.
        */
		~Joueur();

		/**
        * @brief Définit le pseudo du joueur.
        * 
        * @param nom Pseudonyme du joueur
        */
		void setPseudo(string nom);

        /**
        * @brief Modifie l'état d'une case de la maison (occupée = True, vide = False).
        * 
        * @param indice Indice de la case à modifier.
        * @param id_pion Id du pion à mettre dans la case (0 si vide).
        */
		void setMaison(int indice, int id_pion);

		/**
        * @brief Augmente ou diminue la réserve de 1.
        * 
        * @param quantite Nombre à ajouter à la réserve.
        */
	   	void setReserve(int quantite);

		/**
        * @brief Renvoie la carte se trouvant à l'indice 'indice'.
		* 
		* @param indice Indice où chercher la carte (0-3).
        * 
        * @return Carte se trouvant à l'indice 'indice'.
        */
	   	Carte* getCarte(int indice) const;

		/**
        * @brief Renvoie le nombre de pions se trouvant dans la réserve.
        * 
        * @return Nombre de pions.
        */
	   	int getReserve() const;

		/**
        * @brief Renvoie la couleur du joueur.
        * 
        * @return Couleur du joueur (1 : vert, 2 : rouge, 3 : bleu, 4 : jaune, 5 : noir, 6 : blanc).
        */
	   	int getCouleur() const;

		/**
        * @brief Renvoie la maison du joueur.
        * 
        * @return Maison du joueur.
        */
	   	const int* getMaison() const;

		/**
        * @brief Ajoute la carte passée en paramètre à la main du joueur.
        * 
        * @param carte Carte à ajouter à la main.
		* 
		* @return True si la carte a pu être ajoutée, False sinon.
        */
	   	bool piocherCarte(Carte* carte);

		/**
        * @brief Retire une carte de valeur 'valeur' de la main du joueur.
        * 
        * @param valeur Valeur de la carte à retirer.
		* 
		* @return Carte retirée.
        */
		Carte* retirerCarte(int valeur);

		/**
        * @brief Renvoie True si la maison du joueur est remplie, False sinon.
        * 
        * @return un booléen.
        */
		bool maisonRemplie() const;

        /**
        * @brief Test les fonctionnalités de la classe.
        *
        * Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
        * et que les données membres de l'objet sont conformes en tout temps.
        */
        static void testRegression();

        /**
        * @brief Affiche le joueur.
        */
        void afficher() const;
};

#endif