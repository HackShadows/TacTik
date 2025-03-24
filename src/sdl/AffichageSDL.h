
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

    public :
        /**
        * @brief Constructeur qui initialise tout SDL2 et crée la fenêtre et le renderer
        */
        ImageViewer();

        /**
        * @brief Detruit et ferme SDL2
        */
        ~ImageViewer();

        /**
        * @brief Affiche l'image passé en parametre
        * @param im est l'Image que l'on veut afficher
        */
        void afficher();
};


#endif
