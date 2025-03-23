#ifndef _Jeu_H
#define _Jeu_H

/**
* @brief Contient la déclaration de la classe Jeu.
*/
#include "Joueur.h"
#include "Pioche.h"
#include "Plateau.h"
#include <iostream>
using namespace std;

/**
* @class Jeu
*
* @brief Représente l'ensemble des règles du jeu.
*/

class Jeu {

	private:
        int nbJoueurs; ///<Nombres de joueurs.
		Plateau plateau; ///<Le plateau de jeu.
		Pioche pioche; ///<La pioche et le tas.
		Joueur * joueurs; ///<Tableau de 4 ou 6 joueurs.
		Pion * pions; ///< Tableau de tous les pions en jeu (16 ou 24).

	public:
		/**
        * @brief Constructeur par défaut du jeu.
        */
		Jeu();

        /**
        * @brief Constructeur du jeu.
        */
		Jeu(int nbJ);

        /**
        * @brief Destructeur du jeu.
        */
		~Jeu();

        /**
        * @brief Renvoie le plateau de jeu.
		*
		* @return Le plateau de jeu.
        */
        const Plateau& getPlateau() const;

        /**
        * @brief Renvoie le nombre de joueurs.
		*
		* @return Le nombre de joueurs.
        */
        int getNbJoueurs() const;

		/**
        * @brief Renvoie le joueur se trouvant à l'indice 'indice'.
		* 
		* @param indice Indice du joueur à retourner.
		*
		* @return Le joueur se trouvant à l'indice 'indice'.
        */
	   	const Joueur& getJoueur(int indice) const;

		/**
        * @brief Renvoie le pion d'identifiant 'id_pion'.
		* 
		* @param id_pion Id du pion à retourner.
		*
		* @return Le pion d'identifiant 'id_pion'.
        */
	   	const Pion& getPion(int id_pion) const;

        /**
        * @brief Distribue 4 cartes à chaque joueur.
        */
		void distribuer();

		/**
        * @brief Echange une carte entre deux joueurs de la même équipe.
		* 
		* @param indJ1 Indice du joueur1 (indJ1 < indJ2).
		* @param indJ2 Indice du joueur2 (indJ2 > indJ1).
		* @param val_carteJ1 Valeur de la carte du joueur1 à donner au joueur2.
		* @param val_carteJ2 Valeur de la carte du joueur2 à donner au joueur1.
        */
	   	void echangerCartes(int indJ1, int indJ2, int val_carteJ1, int val_carteJ2);

		/**
		* @brief Elimine le pion se trouvant à l'indice 'indice'.
		*
		* @param position Position du pion sur le plateau.
		*/
		void eliminerPion(int position);

		/**
		* @brief Sort un pion de la réserve et le place sur sa case de départ.
		*
		* @param couleur Couleur du pion à démarrer.
		*
		* @return True si un pion a pu démarrer, False sinon.
		*/
		bool demarrer(int couleur);

		/**
		* @brief Avance le pion du nombre passé en paramètre.
		*
		* @param val_carte Valeur de la carte jouée par le joueur.
		* @param id_pion Id du pion à déplacer.
		*
		* @return True si le pion a pu avancer, False sinon.
		*/
		bool avancerPion(int val_carte, int id_pion);

		/**
		* @brief Permutte le pion du joueur avec un autre pion.
		*
		* @param id_pion1 Id du pion du joueur.
		* @param id_pion2 Id du pion avec lequel permutter.
		*
		* @return True si le pion a pu être permutté, False sinon.
		*/
		bool permutter(int id_pion1, int id_pion2);

		/**
		* @brief Joue la carte passée en paramètre.
		*
		* @param val_carte Valeur de la carte jouée par le joueur.
		*
		* @return True si la carte a pu être jouée, False sinon.
		*/
		//bool jouerCarte(int val_carte);

        /**
        * @brief Test les fonctionnalités de la classe.
        *
        * Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
        * et que les données membres de l'objet sont conformes en tout temps.
        */
        static void testRegression();
};

#endif