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
		bool maison[4]; ///<La maison du joueur
		Carte* main[4]; ///<Les 4 cartes de la main du joueur
		string pseudo; ///<Le pseudo du joueur
		int couleur, reserve; ///<La couleur et le nombre de pions en réserve du joueur

	public:
		/**
        * @brief Constructeur du joueur.
        */
		Joueur();

		/**
		* @brief Constructeur du joueur.
		*
		* @param id_couleur Couleur du joueur (1 : vert, 2 : rouge, 3 : bleu, 4 : jaune, 5 : blanc, 6 : noir)
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
        * @param etat État dans lequel mettre la case.
        */
		void setMaison(int indice, bool etat);

		/**
        * @brief Renvoie la carte se trouvant à l'indice 'indice'.
		* 
		* @param indice Indice où chercher la carte (0-3).
        * 
        * @return Carte se trouvant à l'indice 'indice'.
        */
	   	Carte* getCarte(int indice) const;

		/**
        * @brief Renvoie la carte que le joueur souhaite jouer.
        * 
        * @param valeur Valeur de la carte à renvoyer
		* @return Pointeur constant vers la carte jouée
        */
		Carte* jouerCarte(int valeur);

		/**
        * @brief Ajoute la carte passée en paramètre à la main du joueur.
        * 
        * @param carte Carte à ajouter à la main.
        * @param indice Position de la carte dans la main.
        */
		void piocherCarte(int indice, Carte* carte);

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