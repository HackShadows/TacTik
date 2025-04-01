/**
* @brief Contient l'implémentation de la classe IA.
*/
#include "IA.h"

#include <iostream>
#include <cassert>

using namespace std;

IA::IA(): couleur(0) {}

IA::IA(int id_couleur): couleur(id_couleur) {
    assert(1 <= id_couleur && id_couleur <= 6);
}

IA::~IA() {}

void IA::testRegression() {}