CXXFLAGS = -Wall -g -c
CORE = src/core
TXT = src/txt
SDL = src/sdl
INCLUDE_DIR = -I/usr/include/SDL2
LIB_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image

all: test main

test: memcheck_test

main: bin/mainTXT
	./bin/mainTXT

sdl: bin/mainSDL
	./bin/mainSDL

doc: doc/doxyfile doc/html
	doxygen doc/doxyfile

doc/html:
	doxygen doc/doxyfile

bin/mainTXT: obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/AffichageTXT.o obj/mainTXT.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/AffichageTXT.o obj/mainTXT.o -o bin/mainTXT

bin/test:obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/AffichageTXT.o obj/mainTest.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/AffichageTXT.o obj/mainTest.o -o bin/test

bin/mainSDL: obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/AffichageSDL.o obj/mainSDL.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/Plateau.o obj/Jeu.o obj/AffichageSDL.o obj/mainSDL.o -o bin/mainSDL $(LIB_SDL)

obj/mainTest.o: src/mainTest.cpp $(CORE)/Jeu.h
	g++ $(CXXFLAGS) src/mainTest.cpp -o obj/mainTest.o

obj/mainSDL.o: src/mainSDL.cpp $(SDL)/AffichageSDL.h
	g++ $(CXXFLAGS) $(INCLUDE_DIR) src/mainSDL.cpp -o obj/mainSDL.o

obj/AffichageSDL.o: $(SDL)/AffichageSDL.cpp $(SDL)/AffichageSDL.h
	g++ $(CXXFLAGS) $(INCLUDE_DIR) $(SDL)/AffichageSDL.cpp -o obj/AffichageSDL.o

obj/mainTXT.o: src/mainTXT.cpp $(TXT)/Affichage.h
	g++ $(CXXFLAGS) src/mainTXT.cpp -o obj/mainTXT.o

obj/AffichageTXT.o: $(TXT)/Affichage.cpp $(TXT)/Affichage.h $(CORE)/Jeu.h
	g++ $(CXXFLAGS) $(TXT)/Affichage.cpp -o obj/AffichageTXT.o

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

memcheck_mainTXT: bin/mainTXT
	valgrind --leak-check=full --track-origins=yes ./bin/mainTXT

memcheck_test: bin/test
	valgrind --leak-check=full --track-origins=yes ./bin/test

clean:
	rm -rf obj/*.o bin/* doc/html