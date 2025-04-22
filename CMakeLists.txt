cmake_minimum_required(VERSION 3.10)
project(GameProject VERSION 1.0 LANGUAGES CXX)

# Compiler settings
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")

# Output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Source directories
set(CORE_DIR ${CMAKE_SOURCE_DIR}/src/core)
set(TXT_DIR ${CMAKE_SOURCE_DIR}/src/affichage/txt)
set(SDL_DIR ${CMAKE_SOURCE_DIR}/src/affichage/sdl)

# SDL2 settings
set(SDL2_DIR "C:/libs/SDL2/SDL2-2.32.4/x86_64-w64-mingw32")  # Remplacer par le chemin de ton dossier SDL2
set(SDL_INCLUDE_DIR "${SDL2_DIR}/include")
set(SDL_LIB_DIR "${SDL2_DIR}/lib")

# SDL2_image
set(SDL2_IMAGE_INCLUDE_DIR "C:/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/include")
set(SDL2_IMAGE_LIB_DIR "C:/libs/SDL2_image-2.6.3/x86_64-w64-mingw32/lib")

# SDL2_ttf
set(SDL2_TTF_INCLUDE_DIR "C:/libs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/include")
set(SDL2_TTF_LIB_DIR "C:/libs/SDL2_ttf-2.24.0/x86_64-w64-mingw32/lib")

# SDL2_gfx
set(SDL2_GFX_INCLUDE_DIR "C:/libs/SDL2_gfx/include")
set(SDL2_GFX_SOURCE_DIR "C:/libs/SDL2_gfx/src")

# Ajout des répertoires d'inclusion
include_directories(
		${CORE_DIR}
		${TXT_DIR}
		${SDL_DIR}
		${SDL_INCLUDE_DIR}
		${SDL_INCLUDE_DIR}/SDL2
		${SDL2_IMAGE_INCLUDE_DIR}
		${SDL2_TTF_INCLUDE_DIR}
		${SDL2_GFX_INCLUDE_DIR}
)

# Ajout du répertoire des bibliothèques
link_directories(
		${SDL_LIB_DIR}
		${SDL2_IMAGE_LIB_DIR}
		${SDL2_TTF_LIB_DIR}
)

# Common core sources
set(COMMON_SOURCES
		${CORE_DIR}/Carte.cpp
		${CORE_DIR}/Pioche.cpp
		${CORE_DIR}/Pion.cpp
		${CORE_DIR}/Joueur.cpp
		${CORE_DIR}/IA.cpp
		${CORE_DIR}/Plateau.cpp
		${CORE_DIR}/Jeu.cpp
)

# gfx sources
set(GFX_PRIMITIVES_SOURCES
		${SDL2_GFX_SOURCE_DIR}/SDL2_gfxPrimitives.c
		${SDL2_GFX_SOURCE_DIR}/SDL2_rotozoom.c
)

# SDL2 libraries
set(LIB_SDL "SDL2main" "SDL2" "SDL2_ttf" "SDL2_image" "m")  # Ajouter les autres bibliothèques SDL2 nécessaires

enable_language(C)  # pour forcer le support du C si jamais

# Test executable
add_executable(test
		src/mainTEST.cpp
		${COMMON_SOURCES}
		${GFX_PRIMITIVES_SOURCES}
)
target_link_libraries(test PRIVATE ${LIB_SDL})

# Text-mode executable
add_executable(mainTXT
		src/mainTXT.cpp
		${COMMON_SOURCES}
		src/affichage/controleur.cpp
		${TXT_DIR}/AffichageConsole.cpp
		${SDL_DIR}/AffichageGraphique.cpp
)
target_link_libraries(mainTXT PRIVATE ${LIB_SDL})

# SDL-mode executable
add_executable(mainSDL
		src/mainSDL.cpp
		${COMMON_SOURCES}
		src/affichage/controleur.cpp
		${TXT_DIR}/AffichageConsole.cpp
		${SDL_DIR}/AffichageGraphique.cpp
		${GFX_PRIMITIVES_SOURCES}
)
target_link_libraries(mainSDL PRIVATE ${LIB_SDL})
target_compile_definitions(mainSDL PRIVATE SDL_MAIN_HANDLED)


# Development-mode executable
add_executable(mainDEV
		src/mainDEV.cpp
		${COMMON_SOURCES}
		src/affichage/controleur.cpp
		${TXT_DIR}/AffichageConsole.cpp
		${SDL_DIR}/AffichageGraphique.cpp
		${GFX_PRIMITIVES_SOURCES}
)
target_link_libraries(mainDEV PRIVATE ${LIB_SDL})
target_compile_definitions(mainDEV PRIVATE SDL_MAIN_HANDLED)


# Custom memcheck target using Valgrind
add_custom_target(memcheck
		COMMAND valgrind --leak-check=full --track-origins=yes $<TARGET_FILE:test>
		DEPENDS test
		WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

# Documentation via Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
	add_custom_target(doc
			COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_SOURCE_DIR}/doc/doxyfile
			WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
	)
endif()

# Veryclean: remove generated documentation
add_custom_target(veryclean
		COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_SOURCE_DIR}/doc/html
)
