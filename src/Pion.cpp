#include "Pion.h"
#include <iostream>

using namespace std;


Pion::Pion(int identifiant){
    pieu = true;
    image = "data/pion.png";
    id = identifiant;
    couleur = (id/4) +1 ;
}