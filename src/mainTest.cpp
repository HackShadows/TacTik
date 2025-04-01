/**
* @brief Contient les tests des différentes classes.
*/
#include "./core/Jeu.h"
#include <iostream>

using namespace std;

int main(){
    cout << "testRegression Carte : " << endl;
    Carte::testRegression();
    cout << "\ntestRegression Pion : " << endl;
    Pion::testRegression();
    cout << "\ntestRegression Pioche : " << endl;
    Pioche::testRegression();
    cout << "\ntestRegression Plateau : " << endl;
    Plateau::testRegression();
    cout << "\ntestRegression Joueur : " << endl;
    Joueur::testRegression();
    cout << "\ntestRegression Jeu : " << endl;
    Jeu::testRegression();
    cout << "\ntestRegression IA : " << endl;
    IA::testRegression();
}
