/**
* @brief Contient l'implémentation de la classe Pioche.
*/
#include "Pioche.h"

Pioche::Pioche() {
	pile = new Carte[54];
	tas = Carte();
}

void Pioche::setTas(const Carte & carte){
    tas = carte;
}

Carte Pioche::getTas() const{
    return tas;
}

