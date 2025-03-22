
#include "Affichage.h"
#include <iostream>

using namespace std;

void affichage_textuel_id(int id){
    if (id/10 == 0) {
        cout << id << "  ";
    }
    else {
        cout << id << " ";
    }
}


void affichage_textuel_maison() {

}


void affichage_textuel_4p(const Jeu & jeu) {
    for (int i = 0; i<16; i++){
        affichage_textuel_id(jeu.getPlateau().getIdPion(i));  //i;
    }
    cout << endl;
    for (int i = 0; i<16; i++) {
        affichage_textuel_id(jeu.getPlateau().getIdPion(63-i));  // 63-i
        for (int j = 0; j<14; j++) {
            cout << "   ";
        }
        affichage_textuel_id(jeu.getPlateau().getIdPion(16+i)); // 16+i
        cout << endl;
    }
    for (int i = 0; i<16; i++){
        affichage_textuel_id(jeu.getPlateau().getIdPion(47+i));  //47+i
    }
    cout << endl;
}


void affichage_textuel_6p(const Jeu & jeu) {
    for (int i = 0; i<32; i++){
        affichage_textuel_id(jeu.getPlateau().getIdPion(i));  //i;
    }
    cout << endl;
    for (int i = 0; i<16; i++) {
        affichage_textuel_id(jeu.getPlateau().getIdPion(95-i));  // 95-i
        for (int j = 0; j<30; j++) {
            cout << "   ";
        }
        affichage_textuel_id(jeu.getPlateau().getIdPion(32+i)); // 32+i
        cout << endl;
    }
    for (int i = 0; i<32; i++){
        affichage_textuel_id(jeu.getPlateau().getIdPion(79-i));  //79+i
    }
    cout << endl;
}



void affichage_textuel(const Jeu & jeu){
    if (jeu.getNbJoueurs() == 4) {
        affichage_textuel_4p(jeu);
    }
     else{
        affichage_textuel_6p(jeu);
    }
}


