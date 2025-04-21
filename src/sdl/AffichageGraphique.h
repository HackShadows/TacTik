
#ifndef AFFICHERSDL_H
#define AFFICHERSDL_H

#include "../core/Jeu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

using namespace std;

/**
* @brief Contient la déclaration de la classe Image.
*/
class Image{
    private :
		Jeu * jeu; ///<Jeu à afficher
        SDL_Window * window; ///<La fenetre
        SDL_Renderer * renderer;///<Le renderer
        SDL_Texture * texturePlateau;///<La surface de l'image du plateau
		SDL_Texture * textureTas;  ///<La surface de l'image de la carte sur le tas
		SDL_Texture * textureCartes[4]; ///<Les surfaces des quatres cartes
		SDL_Texture * listTexture[15]; ///<Les textures préchargées
		SDL_Rect RectMain[4]; ///<Rectangles des cartes de la main
		SDL_Rect RectTas; ///<Rectanlge du tas
		TTF_Font* m_font; /// Police de la fenetre
		SDL_Surface* textSurface; ///Surface du texte a afficher
        int dimx, dimy; ///<Les dimensions de la fenetre
		int imgWidth, imgHeight; ///<Largeur et hauteur de l'image du plateau
        float zoom; ///<Le zoom de l'image
        int nbJ; ///<Le nombre de joueurs
		int (* coordonnees)[2]; ///< Le tableau des coordonnées des points
        int (* coordonneesMaison)[2]; ///< Le tableau des coordonnées des maisons
        int (* coordonneesReserve)[2]; ///< Le tableau des coordonnées des reserves


    public :
        /**
        * @brief Constructeur qui initialise tout SDL2 et crée la fenêtre et le renderer
        * 
        */
        Image();

        /**
        * @brief Detruit et ferme SDL2
        */
        ~Image();

		/**
        * @brief Initialise le jeu et crée la fenêtre et le renderer
        * 
		* @param nbJoueurs Nombre de joueurs
		* @param IA Liste correspondant aux couleurs des joueurs (true si le joueur est joué par une ia, false sinon)
        */
	   void initJeu(int nbJoueurs, array<bool, 6> IA);

        /**
        * @brief Affiche des carrés sur les cases du plateau
        */
        void debugCoordonnees() const;

		/**
		* @brief Renvoie le jeu en cours.
		*
		* @return Le jeu en cours.
		*/
		Jeu& getJeu() const;

		/**
		* @brief Renvoie le zoom.
		*
		* @return Le zoom.
		*/
		float getZoom() const;

		/**
		* @brief Renvoie la largeur de l'image.
		*
		* @return La largeur de l'image.
		*/
		int getImgWidth() const;

		/**
		* @brief renvoie l'indice du pion sur lequel on a cliqué
		* @param posx Les coordonnées x du clic
		* @param posy Les coordonnées y du clic
		*/
		int getIndicePion(int posx, int posy) const;

		/**
		* @brief renvoie l'indice de la case sur lequel on a cliqué
		* @param posx Les coordonnées x du clic
		* @param posy Les coordonnées y du clic
		*/
		int getIndiceCase(int posx, int posy, int joueurActif = -1) const;

		/**
		* @brief renvoie le numéro du bouton cliqué
		* @param posx Les coordonnées x du clic
		* @param posy Les coordonnées y du clic
		*/
		int getBouton(int posx, int posy) const;

        /**
        * @brief dessine le pion de couleur "couleur" aux coordonnées (x,y)
        * @param couleur L'indice de la couleur qu'on veut afficher
        * @param x L'abscisse du point qu'on veut afficher
        * @param y L'ordonnée du point qu'on veut afficher
        */
        void dessineCercle(int couleur, int x, int y) const;

        /**
        * @brief dessine le pieu de couleur "couleur" aux coordonnées (x,y)
        * @param couleur L'indice de la couleur qu'on veut afficher
        * @param x L'abscisse du pieu qu'on veut afficher
        * @param y L'ordonnée du pieu qu'on veut afficher
        */
        void dessineTriangle(int couleur, int x, int y) const;

        /**
        * @brief Affiche les pions sur le plateau
        */
        void afficherPions() const;

		/**
		* @brief Affiche les pions dans les réserves
		*/
		void afficherReserve() const;

		/**
		* @brief Affiche les pions dans les maisons
		*/
		void afficherMaison() const;

		/**
		* @brief Met à jour les textures des cartes du joueur
		* @param idJoueur L'identifiant du joueur dont on affiche les cartes
		*/
		void setTextureCartes(int idJoueur);

		/**
		* @brief Effectue un zoom avant ou arrière
		* @param positif Indique si le zoom est positif ou négatif
		*/
		void grossissement(bool positif);

		/**
        * @brief Met à jour la valeur de textSurface
		* @param message Le message à afficher
		* @param couleur La couleur du joueur actif
        */
	   void setTextSurface(string message, int couleur);

		/**
        * @brief Met à jour la couleur du fond
        * @param couleur La couleur du joueur actif
        */
	   void setCouleur(int couleur) const;

	   /**
        * @brief Affiche deux boutons
		* @param choix Les différentes possibilités pour les boutons
        */
	   void afficherBoutons(int choix) const;

	   /**
        * @brief Affiche toutes les cartes pour le choix du joker
		* @param tab Le tableau des coordonnées des cartes
        */
	   void afficherJoker(SDL_Rect tab[13]) const;

	   /**
        * @brief Affiche les cartes et récupere la carte séléctionnée
		* @param joueurActif L'identifiant du joueur actif.
		* @param message Le message à afficher
        */
	   int selectionnerValJoker(int joueurActif, string message);

	    /**
        * @brief Affiche le menu pour sélectionner le nombre de joueurs
		* @param message Le message à afficher
        */
	   	int afficherMenu(string message);

		/**
        * @brief Permet de faire les choix pour l'attribution des IA.
		* @param message Le message à afficher
        */
	   char choixIA(string message);

        /**
        * @brief Affiche le jeu à un instant donné
		* @param joueurActif L'identifiant du joueur actif.
		* @param message Le message à afficher
        */
        void afficher(int joueurActif, string message);

};


#endif
