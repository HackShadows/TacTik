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
set(TXT_DIR ${CMAKE_SOURCE_DIR}/src/txt)
set(SDL_DIR ${CMAKE_SOURCE_DIR}/src/sdl)

# SDL2 settings (adjust include path if necessary)
set(SDL_INCLUDE_DIR /usr/include/SDL2)
set(LIB_SDL "-lSDL2;-lSDL2_ttf;-lSDL2_image;-lSDL2_gfx")

include_directories(
        ${CORE_DIR}
        ${TXT_DIR}
        ${SDL_DIR}
        ${SDL_INCLUDE_DIR}
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

# Test executable
add_executable(test
        src/mainTEST.cpp
        ${COMMON_SOURCES}
)
target_link_libraries(test PRIVATE ${LIB_SDL})

# Text-mode executable
add_executable(mainTXT
        src/mainTXT.cpp
        ${COMMON_SOURCES}
        src/controleur.cpp
        ${TXT_DIR}/AffichageConsole.cpp
        ${SDL_DIR}/AffichageGraphique.cpp
)
target_link_libraries(mainTXT PRIVATE ${LIB_SDL})

# SDL-mode executable
add_executable(mainSDL
        src/mainSDL.cpp
        ${COMMON_SOURCES}
        src/controleur.cpp
        ${TXT_DIR}/AffichageConsole.cpp
        ${SDL_DIR}/AffichageGraphique.cpp
)
target_link_libraries(mainSDL PRIVATE ${LIB_SDL})

# Development-mode executable
add_executable(mainDEV
        src/mainDEV.cpp
        ${COMMON_SOURCES}
        src/controleur.cpp
        ${TXT_DIR}/AffichageConsole.cpp
        ${SDL_DIR}/AffichageGraphique.cpp
)
target_link_libraries(mainDEV PRIVATE ${LIB_SDL})

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
