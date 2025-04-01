
#include "./sdl/AffichageSDL.h"

using namespace std;

int main(){
    Jeu jeu(4);
    jeu.demarrer(1);
    jeu.demarrer(2);
    jeu.demarrer(3);
    jeu.demarrer(4);
    jeu.avancerPion(2, 1);
    cout << jeu.getPlateau().getIdPion(0) << "\n";
    ImageViewer image(jeu);
    image.afficher(jeu);
    return 0;
}
