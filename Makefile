all: bin/executable

test: bin/test

doc: doc/doxyfile doc/html
	doxygen doc/doxyfile

doc/html:
	doxygen doc/doxyfile

bin/executable: obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/Affichage.o obj/main.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/Affichage.o obj/main.o -o bin/executable

bin/test:obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/Affichage.o obj/mainTest.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/Affichage.o obj/mainTest.o -o bin/test

obj/mainTest.o: src/mainTest.cpp src/Jeu.h
	g++ -Wall -c src/mainTest.cpp -o obj/mainTest.o

obj/main.o: src/main.cpp src/Affichage.h
	g++ -Wall -c src/main.cpp -o obj/main.o

obj/Affichage.o: src/Affichage.cpp src/Affichage.h src/Jeu.h
	g++ -Wall -c src/Affichage.cpp -o obj/Affichage.o

obj/Jeu.o: src/Jeu.cpp src/Jeu.h src/Joueur.h src/Pioche.h src/Plateau.h
	g++ -Wall -c src/Jeu.cpp -o obj/Jeu.o

obj/Carte.o: src/Carte.cpp src/Carte.h 
	g++ -Wall -c src/Carte.cpp -o obj/Carte.o

obj/Pioche.o: src/Pioche.cpp src/Pioche.h src/Carte.h
	g++ -Wall -c src/Pioche.cpp -o obj/Pioche.o

obj/Pion.o: src/Pion.cpp src/Pion.h
	g++ -Wall -c src/Pion.cpp -o obj/Pion.o

obj/Joueur.o: src/Joueur.cpp src/Joueur.h src/Carte.h
	g++ -Wall -c src/Joueur.cpp -o obj/Joueur.o

obj/Plateau.o: src/Plateau.cpp src/Plateau.h src/Pion.h
	g++ -Wall -c src/Plateau.cpp -o obj/Plateau.o

clean:
	rm -rf obj/*.o bin/executable doc/html