//
// Created by Utilisateur on 18/03/2025.
//

Jeu::Jeu(){
    assert(nbJ == 4 || nbJ == 6);
    nbJoueurs = nbJ;
    joueurs = new Joueur[nbJoueurs];
    pioche = Pioche();
  }
