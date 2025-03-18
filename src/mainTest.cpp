/**
* @brief Contient les tests des différentes classes.
*/
#include "Jeu.h"
#include <iostream>

using namespace std;

int main(){
    cout << "testRegression Carte : " << endl;
    Carte::testRegression();
    cout << "\ntestRegression Pion : " << endl;
    Pion::testRegression();
    cout << "\ntestRegression Pile : " << endl;
    Pioche::testRegression();
    cout << "\ntestRegression Plateau : " << endl;
    Plateau::testRegression();
}
