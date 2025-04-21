# LIFAPCD_Tac-Tik



***


## Description
Ce projet est une réécriture en C++ du jeu de société TacTik, un jeu de stratégie combinant hasard et tactique. 
Il propose deux modes de jeu : une version console accessible via le terminal, et une version graphique utilisant la bibliothèque SDL2.
L’objectif est de fournir une expérience fidèle au jeu de plateau original, tout en mettant en œuvre des concepts 
de programmation orientée objet et de gestion d’affichage en C++. 

## Architecture
    .
    ├── bin                          # Fichiers compilés
    ├── obj                          # Fichiers binaires
    ├── data                         # Images et Police
    │   ├── cartes                   # Images des cartes
    │   └── plateau                  # Images du plateau
    ├── doc                          # Documentation
    │   ├── html                     # Documentaion HTML
    │   └── doxyfile                 # Fichier de configuration Doxygen
    ├── src                          # Fichiers sources
    │   ├── core                     # Code du jeu
    │   ├── txt                      # Code de l'affichage console
    │   └── sdl                      # Code de l'affichage graphique
    ├── Makefile                     
    └── README.md

## Installation et execution
### Linux
#### Prerequis
 - Compilateur C++ (ex g++)
 - Make
 - Les bibliothèques SDL2 :
````
sudo apt-get update
sudo apt-get install libsdl2-dev
sudo apt-get install libsdl2-image-dev libsdl2-ttf-dev
sudo apt-get install libsdl2-gfx-dev

````

#### Compilation
Clonez le projet puis compilez les différents modules
````
make txt       # Compile et lance la version console
make sdl       # Compile et lance la version graphique SDL2
make dev      # Compile la version "développeur"
make doc       # Génère la documentation Doxygen
make mainTXTWindows   # Génère la version texte pour Windows (nécessite MinGW installé)
make mainSDLWindows   # Génère la version grapghique pour Windows (nécessite MinGW installé)
make mainDEVWindows   # Génère la version déveleoppeur pour Windows (nécessite MinGW installé)
````

#### Execution
Une fois compilé, vous pouvez lancer les exécutables depuis le dossier `` bin/`` :
````
./bin/mainTXT       # Version console
./bin/mainSDL       # Version graphique SDL2
````

#### Tests mémoire
Une cible de test avec ``valgrind`` est également disponible :
````
make test    # Vérifie les fuites mémoires
````

#### Nettoyage
Pour supprimer les fichiers objets et executables
````
make clean        # Supprime les .o et les exécutables
make veryclean    # Supprime aussi la documentation
````

## Contributeurs

 Ce projet à été réalisé dans le cadre d'un travail en binôme par :
 - Marius CISERANE p2303380
 - Valentin LAPORTE p2302750
 
 Le projet est hébergé sur le GitLab de Lyon1 avec comme ID 38209

