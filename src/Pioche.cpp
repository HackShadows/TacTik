/**
* @brief Contient l'implémentation de la classe Pioche.
*/
#include "Pioche.h"

Pioche::Pioche() {
	pile = new Carte[54];
	tas = Carte();
}

Pioche::~Pioche() {
    delete [] pile;
    pile = nullptr;
}

void Pioche::setTas(const Carte & carte){
    tas = carte;
}

Carte Pioche::getTas() const{
    return tas;
}

Carte* Pioche::getPile() const{
    return pile;
}

void Pioche::testRegression(){
    
}

void Pioche::afficher() const {
    cout << "Tas : ";
    tas.afficher();
    for (int i = 0 ; i < 54 ; i++) pile[i].afficher();
}
