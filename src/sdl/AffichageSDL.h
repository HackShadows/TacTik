
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
        SDL_Window * window; /// La fenetre
        SDL_Renderer * renderer;/// Le renderer
        SDL_Surface * surfacePlateau;///La surface de l'image du plateau
		SDL_Surface * surfaceTas;  ///La surface de l'image de la carte sur le tas
		SDL_Surface * surfaceCarte1; ///La surface de l'image de la première carte
		SDL_Surface * surfaceCarte2;  ///La surface de l'image de la deuxième carte
		SDL_Surface * surfaceCarte3;  ///La surface de l'image de la troisième carte
		SDL_Surface * surfaceCarte4;  ///La surface de l'image de la quatrième carte
        int dimx, dimy; /// Les dimensions de la fenetre
        float zoom; /// Le zoom de l'image
        int nbJ; /// Le nombre de joueurs


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
        * @param tab Le tableau de coordonnées des cases que l'on veut afficher
        */
        void debugCoordonnees(const int tab[][2]);

        /**
        * @brief Affiche la carte du tas du jeu passé en parametre
        * @param jeu Le jeu dont on veut afficher le tas
        */
        void afficherTas(const Jeu & jeu);


        /**
        * @brief dessine le pion de couleur "couleur" aux coordonnées (x,y)
        * @param couleur L'indice de la couleur qu'on veut afficher
        * @param x L'abscisse du point qu'on veut afficher
        * @param y L'ordonnée du point qu'on veut afficher
        */
        void dessineCercle(int couleur, int x, int y);

        /**
        * @brief dessine le pieu de couleur "couleur" aux coordonnées (x,y)
        * @param couleur L'indice de la couleur qu'on veut afficher
        * @param x L'abscisse du pieu qu'on veut afficher
        * @param y L'ordonnée du pieu qu'on veut afficher
        */
        void dessineTriangle(int couleur, int x, int y);

        /**
        * @brief Affiche les pions du jeu passé en parametre
        * @param jeu Le jeu dont on veut afficher les pions
        * @param tab Le tableau des coordonnées des cases sur le plateau
        */
        void afficherPions(const Jeu & jeu, const int tab[][2]);

		/**
		* @brief Affiche les cartes du jeu passé en parametre
		* @param jeu Le jeu dont on veut afficher les pions
		*/
		void afficherCartes(const Jeu & jeu);

        /**
        * @brief Affiche le jeu passé en parametre
        * @param jeu Le jeu que l'on veut afficher
        */
        void afficher(const Jeu & jeu);

};


#endif
