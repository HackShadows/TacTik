
#ifndef AFFICHERSDL_H
#define AFFICHERSDL_H

#include "../core/Jeu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>

using namespace std;

/**
* @brief Contient la déclaration de la classe ImageViewer.
*/
class ImageViewer{
    private :
		Jeu * jeu; ///<Jeu à afficher
        SDL_Window * window; ///<La fenetre
        SDL_Renderer * renderer;///<Le renderer
        SDL_Texture * texturePlateau;///<La surface de l'image du plateau
		SDL_Texture * textureTas;  ///<La surface de l'image de la carte sur le tas
		SDL_Texture * textureCartes[4]; ///<Les surfaces des quatres cartes
		SDL_Texture * listTexture[15];
		SDL_Rect RectMain[4]; ///<Rectangles des cartes de la main
		SDL_Rect RectTas; ///<Rectanlge du tas
		TTF_Font* m_font; /// Police de la fenetre
		SDL_Surface* textSurface; ///Surface du texte a afficher
        int dimx, dimy; ///<Les dimensions de la fenetre
		int imgWidth, imgHeight; ///<Largeur et hauteur de l'image
		int phase; ///<L'indicateur de la phase dans laquelle on est
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
        ImageViewer();

        /**
        * @brief Detruit et ferme SDL2
        */
        ~ImageViewer();

		/**
        * @brief Constructeur qui initialise le jeu et crée la fenêtre et le renderer
        * 
		* @param nbJoueurs Nombre de joueurs
		* @param nbIA Nombre d'IA
        */
	   void initJeu(int nbJoueurs = 4, int nbIA = 0);

        /**
        * @brief Affiche des carrés sur les cases du plateau
        */
        void debugCoordonnees() const;

		/**
		* @brief Renvoie le jeu en cours.
		*
		* @return Le jeu en cours.
		*/
		Jeu& getJeu();

		/**
		* @brief Renvoie le zoom.
		*
		* @return Le zoom.
		*/
		float getZoom();

		/**
		* @brief Renvoie la largeur de l'image.
		*
		* @return La largeur de l'image.
		*/
		int getImgWidth();

		/**
		* @brief renvoie l'indice du pion sur lequel on a cliqué
		* @param posx Les coordonnées x du clic
		* @param posy Les coordonnées y du clic
		*/
		int getIndicePion(int posx, int posy);

		/**
		* @brief renvoie l'indice du pion sans clic
		* @param plateau Le plateau courant
		* @param s La string à afficher
		*/
		int getIndicePionEvent(string s="");

		/**
		* @brief renvoie le chiffre saisi par l'utilisateur
		* @param s La string à afficher
		*/
		int getEventNumber( string s="");

		/**
		* @brief renvoie le caractère saisi par l'utilisateur
		* @param joueurActif Le joueur qui joue
		* @param choix La valeur des boutons
		* @param message Le message a afficher
		*/
		char getEventChar(int joueurActif, int choix, string message);

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
        * @brief Affiche les pions du jeu passé en parametre
        */
        void afficherPions() const;

		/**
		* @brief Affiche les reverves du jeu passé en parametre
		*/
		void afficherReserve() const;

		/**
		* @brief Affiche les maisons du jeu passé en parametre
		*/
		void afficherMaison() const;

		/**
		* @brief Affiche les cartes du jeu passé en parametre
		* @param id_joueur L'identifiant du joueur dont on affiche les cartes
		*/
		void setTextureCartes(int id_joueur);

		void grossissement(bool positif);

		/**
        * @brief Met à jour la valeur de textSurface
		* @param message Le message à afficher
		* @param couleur La couleur du joueur actif
        */
	   void setTextSurface(string message, int couleur);

		/**
        * @brief Met à jour la couleur du fond
        */
	   void setCouleur(int couleur);

	   /**
        * @brief Affiche deux boutons
		* @param choix Les différentes possibilités pour le choix
        */
	   void afficherBoutons(int choix);

	   /**
        * @brief Affiche toutes les cartes pour le choix du joker
		* @param tab Le tableu des coordonnées des cartes
        */
	   void afficherJoker(SDL_Rect tab[13]);

	   /**
        * @brief Affiche les cartes pour le choix de la carte du joker
		* @param joueurActif L'identifiant du joueur actif.
		* @param message Le message à afficher
        */
	   int selectionnerValJoker(int joueurActif, string message);


        /**
        * @brief Affiche le jeu passé en parametre
		* @param joueurActif L'identifiant du joueur actif.
		* @param message Le message à afficher
        */
        void afficher(int joueurActif, string message);

};


#endif
