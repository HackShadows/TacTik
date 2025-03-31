
#ifndef AFFICHERSDL_H
#define AFFICHERSDL_H

#include "../core/Jeu.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

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
        * @brief Affiche le jeu passé en parametre
        * @param jeu Le jeu que l'on veut afficher
        */
        void afficher(const Jeu & jeu);
};


#endif
