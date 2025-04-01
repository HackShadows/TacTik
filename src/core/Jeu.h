#ifndef _Jeu_H
#define _Jeu_H

/**
* @brief Contient la déclaration de la classe Jeu.
*/
#include "Joueur.h"
#include "IA.h"
#include "Pioche.h"
#include "Plateau.h"
#include <iostream>
#include <limits>
using namespace std;


/**
* @brief Permet de saisir un entier en gérant les erreurs de saisi.
*
* @param cout_message Message à afficher avant le cin (non obligatoire).
* @param val_defaut Valeur par défaut de l'entier (non obligatoire).
*
* @return Entier saisi par l'utilisateur.
*/
int cinProtectionInt(string cout_message = "", int val_defaut = 0);

/**
* @brief Permet de saisir un caractère en gérant les erreurs de saisi.
*
* @param cout_message Message à afficher avant le cin (non obligatoire).
* @param val_defaut Valeur par défaut du caractère (non obligatoire).
*
* @return Caractère saisi par l'utilisateur.
*/
char cinProtectionChar(string cout_message = "", char val_defaut = '0');

/**
* @class Jeu
*
* @brief Représente l'ensemble des règles du jeu.
*/

class Jeu {

	private:
        int nbJoueurs; ///<Nombre de joueurs.
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
        * @brief Renvoie la pioche.
		*
		* @return La pioche.
        */
	   	const Pioche& getPioche() const;

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
		* @brief Défausse la carte passée en paramètre.
		*
		* @param val_carte Valeur de la carte défaussée par le joueur.
		* @param couleur Couleur du joueur qui défausse la carte.
		*
		* @return True si la carte a pu être défaussée, False sinon.
		*/
		bool defausserCarte(int val_carte, int couleur);

		/**
		* @brief Défausse la main du joueur passé en paramètre.
		*
		* @param couleur Couleur du joueur.
		*/
		void defausserJoueur(int couleur);

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
		* @param test True pour ne pas effectuer l'action, False sinon (géré automatiquement).
		*
		* @return True si un pion a pu démarrer, False sinon.
		*/
		bool demarrer(int couleur, bool test = false);

		/**
		* @brief Avance le pion du nombre passé en paramètre.
		*
		* @param val_carte Valeur de la carte jouée par le joueur.
		* @param id_pion Id du pion à déplacer.
		* @param test True pour ne pas effectuer l'action, False sinon (géré automatiquement).
		* @param septx1 True si on avance le pion pour un 7x1, False sinon (géré automatiquement).
		*
		* @return True si le pion a pu avancer, False sinon.
		*/
		bool avancerPion(int val_carte, int id_pion, bool test = false, bool septx1 = false);

		/**
		* @brief Avance le pion dans la maison du nombre passé en paramètre.
		*
		* @param val_carte Valeur de la carte jouée par le joueur.
		* @param id_pion Id du pion à déplacer.
		* @param test True pour ne pas effectuer l'action, False sinon (géré automatiquement).
		*
		* @return True si le pion a pu avancer, False sinon.
		*/
		bool avancerMaison(int val_carte, int id_pion, bool test = false);

		/**
		* @brief Permutte le pion du joueur avec un autre pion.
		*
		* @param id_pion1 Id du pion du joueur.
		* @param id_pion2 Id du pion avec lequel permutter.
		* @param test True pour ne pas effectuer l'action, False sinon (géré automatiquement).
		*
		* @return True si le pion a pu être permutté, False sinon.
		*/
		bool permutter(int id_pion1, int id_pion2, bool test = false);

		/**
        * @brief Renvoie True si la partie a été gagnée par une équipe, False sinon.
		*
		* @return Le booléen correspondant.
        */
	   	bool partieGagnee();

		/**
		* @brief Détermine si la carte passée en paramètre peut être jouée.
		*
		* @param couleur Couleur du joueur.
		* @param val_carte Valeur de la carte jouée par le joueur.
		* @param coequipier True si le joueur joue pour son coéquipier, false sinon (géré automatiquement).
		* @param joker True si la carte passée en paramètre est la valeur choisie pour un joker, false sinon (géré automatiquement).
		*
		* @return True si la carte peut être jouée, False sinon.
		*/
		bool carteJouable(int couleur, int val_carte, bool coequipier = false, bool joker = false);

		/**
		* @brief Détermine si le joueur peut jouer.
		*
		* @param couleur Couleur du joueur.
		* @param coequipier True si le joueur joue pour son coéquipier, false sinon (géré automatiquement).
		*
		* @return True si le joueur peut jouer, False sinon.
		*/
		bool peutJouer(int couleur, bool coequipier = false);

		/**
		* @brief Joue la carte passée en paramètre.
		*
		* @param val_carte Valeur de la carte jouée par le joueur.
		* @param couleur Couleur du joueur.
		* @param coequipier True si le joueur joue pour son coéquipier, false sinon (géré automatiquement).
		* @param affichage_graphique True pour un affichage graphique, false pour un affichage console (géré automatiquement).
		* @param joker True si la carte passée en paramètre est un joker, false sinon (géré automatiquement).
		*
		* @return True si la carte a pu être jouée, False sinon.
		*/
		bool jouerCarte(int val_carte, int couleur, bool coequipier = false, bool affichage_graphique = false, bool joker = false);

        /**
        * @brief Test les fonctionnalités de la classe.
        *
        * Effectue une série de tests pour vérifier que toutes les fonctions produisent uniquement le résultat attendu,
        * et que les données membres de l'objet sont conformes en tout temps.
        */
        static void testRegression();
};

#endif