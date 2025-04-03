CXXFLAGS = -Wall -g -c
CORE = src/core
TXT = src/txt
SDL = src/sdl
INCLUDE_DIR = -I/usr/include/SDL2
LIB_SDL = -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx

# Pour installer SDL2 sous linux
# sudo apt-get update
# sudo apt-get install libsdl2-dev
# sudo apt-get install libsdl2-image-dev libsdl2-ttf-dev


all: clean test bin/mainTXT bin/mainSDL bin/mainTXT.exe

test: memcheck_test

main: bin/mainDEV
	./bin/mainDEV

txt: bin/mainTXT
	./bin/mainTXT

sdl: bin/mainSDL
	./bin/mainSDL

doc: doc/doxyfile doc/html
	doxygen doc/doxyfile

doc/html:
	doxygen doc/doxyfile

bin/test:obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/IA.o obj/Plateau.o obj/Jeu.o obj/AffichageConsole.o obj/mainTEST.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/IA.o obj/Plateau.o obj/Jeu.o obj/AffichageConsole.o obj/mainTEST.o -o bin/test

bin/mainTXT: obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/IA.o obj/Plateau.o obj/Jeu.o obj/AffichageConsole.o obj/mainTXT.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/IA.o obj/Plateau.o obj/Jeu.o obj/AffichageConsole.o obj/mainTXT.o -o bin/mainTXT

bin/mainSDL: obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/IA.o obj/Plateau.o obj/Jeu.o obj/AffichageSDL.o obj/mainSDL.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/IA.o obj/Plateau.o obj/Jeu.o obj/AffichageSDL.o obj/mainSDL.o -o bin/mainSDL $(LIB_SDL)

bin/mainDEV: obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/IA.o obj/Plateau.o obj/Jeu.o obj/AffichageConsole.o obj/AffichageSDL.o obj/mainDEV.o
	g++ obj/Carte.o obj/Pioche.o obj/Pion.o obj/Joueur.o obj/IA.o obj/Plateau.o obj/Jeu.o obj/AffichageConsole.o obj/AffichageSDL.o obj/mainDEV.o -o bin/mainDEV $(LIB_SDL)

obj/mainTEST.o: src/mainTEST.cpp $(CORE)/Jeu.h
	g++ $(CXXFLAGS) src/mainTEST.cpp -o obj/mainTEST.o

obj/mainTXT.o: src/mainTXT.cpp $(TXT)/AffichageConsole.h
	g++ $(CXXFLAGS) src/mainTXT.cpp -o obj/mainTXT.o

obj/mainSDL.o: src/mainSDL.cpp $(SDL)/AffichageSDL.h
	g++ $(CXXFLAGS) $(INCLUDE_DIR) src/mainSDL.cpp -o obj/mainSDL.o

obj/mainDEV.o: src/mainDEV.cpp $(TXT)/AffichageConsole.h $(SDL)/AffichageSDL.h
	g++ $(CXXFLAGS) $(INCLUDE_DIR) src/mainDEV.cpp -o obj/mainDEV.o

obj/AffichageConsole.o: $(TXT)/AffichageConsole.cpp $(TXT)/AffichageConsole.h $(CORE)/Jeu.h
	g++ $(CXXFLAGS) $(TXT)/AffichageConsole.cpp -o obj/AffichageConsole.o

obj/AffichageSDL.o: $(SDL)/AffichageSDL.cpp $(SDL)/AffichageSDL.h
	g++ $(CXXFLAGS) $(INCLUDE_DIR) $(SDL)/AffichageSDL.cpp -o obj/AffichageSDL.o

obj/Jeu.o: $(CORE)/Jeu.cpp $(CORE)/Jeu.h $(CORE)/Joueur.h $(CORE)/IA.h $(CORE)/Pioche.h $(CORE)/Plateau.h
	g++ $(CXXFLAGS) $(CORE)/Jeu.cpp -o obj/Jeu.o

obj/Carte.o: $(CORE)/Carte.cpp $(CORE)/Carte.h
	g++ $(CXXFLAGS) $(CORE)/Carte.cpp -o obj/Carte.o

obj/Pioche.o: $(CORE)/Pioche.cpp $(CORE)/Pioche.h $(CORE)/Carte.h
	g++ $(CXXFLAGS) $(CORE)/Pioche.cpp -o obj/Pioche.o

obj/Pion.o: $(CORE)/Pion.cpp $(CORE)/Pion.h
	g++ $(CXXFLAGS) $(CORE)/Pion.cpp -o obj/Pion.o

obj/Joueur.o: $(CORE)/Joueur.cpp $(CORE)/Joueur.h $(CORE)/Carte.h
	g++ $(CXXFLAGS) $(CORE)/Joueur.cpp -o obj/Joueur.o

obj/IA.o: $(CORE)/IA.cpp $(CORE)/IA.h
	g++ $(CXXFLAGS) $(CORE)/IA.cpp -o obj/IA.o

obj/Plateau.o: $(CORE)/Plateau.cpp $(CORE)/Plateau.h $(CORE)/Pion.h
	g++ $(CXXFLAGS) $(CORE)/Plateau.cpp -o obj/Plateau.o

memcheck_test: bin/test
	valgrind --leak-check=full --track-origins=yes ./bin/test

clean:
	rm -rf obj/*.o bin/* obj_win

veryclean:
	rm -rf doc/html


# ---------------------------------------------------------------------------
# Ajout de la cible mainWindows pour générer mainTXT.exe pour Windows
# On utilise le compilateur croisé MinGW-w64 (x86_64-w64-mingw32-g++)
# Les objets Windows seront placés dans le dossier obj_win

CROSS = x86_64-w64-mingw32-g++
CROSS_CXXFLAGS = -Wall -g -c -municode -DUNICODE -D_UNICODE
WIN_OBJ_DIR = obj_win

# Règle pour créer le dossier d'objets Windows s'il n'existe pas
$(WIN_OBJ_DIR):
	mkdir -p $(WIN_OBJ_DIR)

# Règles pour compiler les sources du répertoire CORE avec le compilateur Windows
$(WIN_OBJ_DIR)/Carte.o: $(CORE)/Carte.cpp $(CORE)/Carte.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) $(CORE)/Carte.cpp -o $(WIN_OBJ_DIR)/Carte.o

$(WIN_OBJ_DIR)/Pioche.o: $(CORE)/Pioche.cpp $(CORE)/Pioche.h $(CORE)/Carte.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) $(CORE)/Pioche.cpp -o $(WIN_OBJ_DIR)/Pioche.o

$(WIN_OBJ_DIR)/Pion.o: $(CORE)/Pion.cpp $(CORE)/Pion.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) $(CORE)/Pion.cpp -o $(WIN_OBJ_DIR)/Pion.o

$(WIN_OBJ_DIR)/Joueur.o: $(CORE)/Joueur.cpp $(CORE)/Joueur.h $(CORE)/Carte.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) $(CORE)/Joueur.cpp -o $(WIN_OBJ_DIR)/Joueur.o

$(WIN_OBJ_DIR)/IA.o: $(CORE)/IA.cpp $(CORE)/IA.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) $(CORE)/IA.cpp -o $(WIN_OBJ_DIR)/IA.o

$(WIN_OBJ_DIR)/Plateau.o: $(CORE)/Plateau.cpp $(CORE)/Plateau.h $(CORE)/Pion.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) $(CORE)/Plateau.cpp -o $(WIN_OBJ_DIR)/Plateau.o

$(WIN_OBJ_DIR)/Jeu.o: $(CORE)/Jeu.cpp $(CORE)/Jeu.h $(CORE)/Joueur.h $(CORE)/IA.h $(CORE)/Pioche.h $(CORE)/Plateau.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) $(CORE)/Jeu.cpp -o $(WIN_OBJ_DIR)/Jeu.o

# Règles pour compiler les sources TXT spécifiques
$(WIN_OBJ_DIR)/AffichageConsole.o: $(TXT)/AffichageConsole.cpp $(TXT)/AffichageConsole.h $(CORE)/Jeu.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) $(TXT)/AffichageConsole.cpp -o $(WIN_OBJ_DIR)/AffichageConsole.o

$(WIN_OBJ_DIR)/mainTXT.o: src/mainTXT.cpp $(TXT)/AffichageConsole.h | $(WIN_OBJ_DIR)
	$(CROSS) $(CROSS_CXXFLAGS) src/mainTXT.cpp -o $(WIN_OBJ_DIR)/mainTXT.o

# Règle de linkage pour générer l'exécutable Windows mainTXT.exe
bin/mainTXT.exe: $(WIN_OBJ_DIR)/Carte.o $(WIN_OBJ_DIR)/Pioche.o $(WIN_OBJ_DIR)/Pion.o $(WIN_OBJ_DIR)/Joueur.o $(WIN_OBJ_DIR)/IA.o $(WIN_OBJ_DIR)/Plateau.o $(WIN_OBJ_DIR)/Jeu.o $(WIN_OBJ_DIR)/AffichageConsole.o $(WIN_OBJ_DIR)/mainTXT.o | bin
	$(CROSS) $^ -static -static-libgcc -static-libstdc++ -lmingw32 -o bin/mainTXT.exe

# Assure que le dossier bin existe
bin:
	mkdir -p bin

# Cible mainWindows qui génère l'exécutable Windows
mainWindows: clean bin/mainTXT.exe
	@echo "Windows executable generated: bin/mainTXT.exe"