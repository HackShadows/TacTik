
#ifndef AFFICHERSDL_H
#define AFFICHERSDL_H

#include "../core/Jeu.h"
#include <SDL.h>
#include <SDL_image.h>

using namespace std;
/**
* @brief Contient la déclaration de la classe Image.
*/
class ImageViewer{
    private :
        SDL_Window * window; /// La fenetre
        SDL_Renderer * renderer;/// Le renderer
        SDL_Surface * surface;///La surface
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
        * @brief met la couleur du renderer selon la couleur passé en paramètre
        * @param couleur L'indice de la couleur qu'on veut afficher
        */
        void setRGB(int couleur);

        /**
        * @brief Affiche les pions du jeu passé en parametre
        * @param jeu Le jeu dont on veut afficher les pions
        * @param tab Le tableau des coordonnées des cases sur le plateau
        */
        void afficherPions(const Jeu & jeu, const int tab[][2]);

        /**
        * @brief Affiche le jeu passé en parametre
        * @param jeu Le jeu que l'on veut afficher
        */
        void afficher(const Jeu & jeu);

};


#endif
