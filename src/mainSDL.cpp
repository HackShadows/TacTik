
#include "./sdl/AffichageSDL.h"

using namespace std;

int main(){
    Jeu jeu(4);
    ImageViewer image(jeu);
    image.afficher(jeu);
    return 0;
}
