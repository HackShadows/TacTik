CXXFLAGS = -Wall -g -c
CORE = src/core
TXT = src/txt

all: bin/main bin/test

test: memcheck_test

main: bin/main
	./bin/main

doc: doc/doxyfile doc/html
	doxygen doc/doxyfile

doc/html:
	doxygen doc/doxyfile

bin/main: obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/Affichage.o obj/main.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/Affichage.o obj/main.o -o bin/main

bin/test:obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/Affichage.o obj/mainTest.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/Affichage.o obj/mainTest.o -o bin/test

obj/mainTest.o: src/mainTest.cpp $(CORE)/Jeu.h
	g++ $(CXXFLAGS) src/mainTest.cpp -o obj/mainTest.o

obj/main.o: src/main.cpp $(TXT)/Affichage.h
	g++ $(CXXFLAGS) src/main.cpp -o obj/main.o

obj/Affichage.o: $(TXT)/Affichage.cpp $(TXT)/Affichage.h $(CORE)/Jeu.h
	g++ $(CXXFLAGS) $(TXT)/Affichage.cpp -o obj/Affichage.o

obj/Jeu.o: $(CORE)/Jeu.cpp $(CORE)/Jeu.h $(CORE)/Joueur.h $(CORE)/Pioche.h $(CORE)/Plateau.h
	g++ $(CXXFLAGS) $(CORE)/Jeu.cpp -o obj/Jeu.o

obj/Carte.o: $(CORE)/Carte.cpp $(CORE)/Carte.h
	g++ $(CXXFLAGS) $(CORE)/Carte.cpp -o obj/Carte.o

obj/Pioche.o: $(CORE)/Pioche.cpp $(CORE)/Pioche.h $(CORE)/Carte.h
	g++ $(CXXFLAGS) $(CORE)/Pioche.cpp -o obj/Pioche.o

obj/Pion.o: $(CORE)/Pion.cpp $(CORE)/Pion.h
	g++ $(CXXFLAGS) $(CORE)/Pion.cpp -o obj/Pion.o

obj/Joueur.o: $(CORE)/Joueur.cpp $(CORE)/Joueur.h $(CORE)/Carte.h
	g++ $(CXXFLAGS) $(CORE)/Joueur.cpp -o obj/Joueur.o

obj/Plateau.o: $(CORE)/Plateau.cpp $(CORE)/Plateau.h $(CORE)/Pion.h
	g++ $(CXXFLAGS) $(CORE)/Plateau.cpp -o obj/Plateau.o

memcheck_main: bin/main
	valgrind --leak-check=full --track-origins=yes ./bin/main

memcheck_test: bin/test
	valgrind --leak-check=full --track-origins=yes ./bin/test

clean:
	rm -rf obj/*.o bin/* doc/html