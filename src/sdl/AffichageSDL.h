
#ifndef AFFICHERSDL_H
#define AFFICHERSDL_H

#include "../core/Jeu.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL2_gfxPrimitives.h>

using namespace std;
/**
* @brief Contient la déclaration de la classe Image.
*/
class ImageViewer{
    private :
        SDL_Window * window; ///<La fenetre
        SDL_Renderer * renderer;///<Le renderer
        SDL_Texture * texturePlateau;///<La surface de l'image du plateau
		SDL_Texture * textureTas;  ///<La surface de l'image de la carte sur le tas
		SDL_Texture * textureCartes[4]; ///<Les surfaces des quatres cartes
        int dimx, dimy; ///<Les dimensions de la fenetre
		int phase; ///<L'indicateur de la phase dans laquelle on est
        float zoom; ///<Le zoom de l'image
        int nbJ; ///<Le nombre de joueurs
		int (* coordonnees)[2]; ///< Le tableau des coordonnées des points
        int (* coordonneesMaison)[2]; ///< Le tableau des coordonnées des maisons
        int (* coordonneesReserve)[2]; ///< Le tableau des coordonnées des reserves


    public :
        /**
        * @brief Constructeur qui initialise tout SDL2 et crée la fenêtre et le renderer
        * @param jeu Le jeu que l'on veut afficher.
        */
        ImageViewer(const Jeu & jeu);

        /**
        * @brief Detruit et ferme SDL2
        */
        ~ImageViewer();

        /**
        * @brief Affiche des carrés sur les cases du plateau
        */
        void debugCoordonnees() const;

		/**
		* @brief renvoie l'indice du pion sur lequel on a cliqué
		* @param jeu Le jeu courant
		* @param posx Les coordonnées x du clic
		* @param posy Les coordonnées y du clic
		*/
		int getIndicePion(const Jeu &jeu, int posx, int posy);

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
        * @param jeu Le jeu dont on veut afficher les pions
        */
        void afficherPions(const Jeu & jeu) const;

		/**
		* @brief Affiche les reverves du jeu passé en parametre
		* @param jeu Le jeu dont on veut afficher les reserves
		*/
		void afficherReserve(const Jeu & jeu) const;

		/**
		* @brief Affiche les maisons du jeu passé en parametre
		* @param jeu Le jeu dont on veut afficher les maisons
		*/
		void afficherMaison(const Jeu & jeu) const;

		/**
		* @brief Affiche les cartes du jeu passé en parametre
		* @param jeu Le jeu dont on veut afficher les pions
		* @param id_joueur L'identifiant du joueur dont on affiche les cartes
		*/
		void setTextureCartes(const Jeu & jeu, int id_joueur);


		/**
		* @brief Gère les évenenements
		* @param event L'évenement à gérer
		* @param running Booléen qui definit si le jeu continue de tourner
		* @param imgWidth Largeur de l'image
		* @param imgHeight Hauteur de l'image
		* @param RectMain1 Rectangle de la premiere carte de la main
		* @param RectMain2 Rectangle de la deuxieme carte de la main
		* @param RectMain3 Rectangle de la troisieme carte de la main
		* @param RectMain4 Rectangle de la quatrieme carte de la main
		* @param RectTas Rectanlge du tas
		* @param jeu Le jeu en cours
		*/
		void gestionEvent(SDL_Event event, bool &running, int &imgWidth, int &imgHeight, SDL_Rect &RectMain1,SDL_Rect &RectMain2, SDL_Rect &RectMain3, SDL_Rect &RectMain4, SDL_Rect &RectTas, Jeu & jeu);

        /**
        * @brief Affiche le jeu passé en parametre
        * @param jeu Le jeu que l'on veut afficher
        */
        void afficher(Jeu & jeu);

};


#endif
