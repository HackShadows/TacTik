all: bin/executable

doc: doc/doxyfile doc/html
	doxygen doc/doxyfile

doc/html:
	doxygen doc/doxyfile

bin/executable: obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/main.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/main.o -o bin/executable

obj/main.o: src/main.cpp src/Carte.h src/Joueur.h src/Pion.h src/Pioche.h src/Plateau.h
	g++ -Wall -c src/main.cpp -o obj/main.o

obj/Carte.o: src/Carte.cpp src/Carte.h 
	g++ -Wall -c src/Carte.cpp -o obj/Carte.o

obj/Pioche.o: src/Pioche.cpp src/Pioche.h 
	g++ -Wall -c src/Pioche.cpp -o obj/Pioche.o

obj/Pion.o: src/Pion.cpp src/Pion.h src/Carte.h
	g++ -Wall -c src/Pion.cpp -o obj/Pion.o

obj/Joueur.o: src/Joueur.cpp src/Joueur.h src/Carte.h
	g++ -Wall -c src/Joueur.cpp -o obj/Joueur.o

obj/Plateau.o: src/Plateau.cpp src/Plateau.h src/Joueur.h src/Pion.h src/Pioche.h
	g++ -Wall -c src/Plateau.cpp -o obj/Plateau.o

clean:
	rm -rf obj/*.o bin/executable doc/html