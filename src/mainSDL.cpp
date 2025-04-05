
#include "./sdl/AffichageSDL.h"

using namespace std;

int main(){
    Jeu jeu(6);
    /*jeu.demarrer(1);
    jeu.demarrer(2);
    jeu.demarrer(3);
    jeu.demarrer(4);
    jeu.demarrer(5);
    jeu.demarrer(6);*/
    jeu.distribuer();
    //jeu.avancerPion(2, 1);
    ImageViewer image(jeu);
    image.afficher(jeu);
    return 0;
}
