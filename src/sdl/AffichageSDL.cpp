/**
* @brief Contient l'implémentation de l'affichege graphique
*/

#include "AffichageSDL.h"

int getIndiceCase(const Jeu &jeu, int posx, int posy, const int tab[][2], float zoom) {
    float rayon = 20 * zoom;
    //cout << posx << " " << posy << " " << tab[0][0] * zoom << " " << tab[0][1] * zoom << " ";
    for (int i = 0; i < 16 * jeu.getNbJoueurs(); i++) {
        if (abs(posx - tab[i][0] * zoom) < rayon && abs(posy - tab[i][1] * zoom) < rayon) {
            return i;
        }
    }
    return -1;
}

ImageViewer::ImageViewer(const Jeu &jeu) {
    zoom = 0.5;
    nbJ = jeu.getNbJoueurs();
    phase = 0;
    cout << "SDL: init" << endl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    cout << "SDL_image: init" << endl;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        cout << "SDL_m_image could not initialize! SDL_m_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    if (nbJ == 6) {
        dimx = (int) 1666;
        dimy = (int) 1000;
    } else {
        dimx = (int) 1000;
        dimy = (int) 1000;
    }

    window = SDL_CreateWindow("Tac-Tik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (dimx + 200) * zoom,
                              dimy * zoom,
                              SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    texturePlateau = nbJ == 4 ? IMG_LoadTexture(renderer, "./data/plateau/plateau4.png") : IMG_LoadTexture(renderer, "./data/plateau/plateau6.png");
    textureTas = IMG_LoadTexture(renderer, "./data/cartes/0.png");
    textureCartes[0] = IMG_LoadTexture(renderer, "./data/cartes/0.png");
    textureCartes[1] = IMG_LoadTexture(renderer, "./data/cartes/0.png");
    textureCartes[2] = IMG_LoadTexture(renderer, "./data/cartes/0.png");
    textureCartes[3] = IMG_LoadTexture(renderer, "./data/cartes/0.png");
    if (texturePlateau == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureTas == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureCartes[0] == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureCartes[1] == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureCartes[2] == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureCartes[3] == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }

    if (nbJ == 6) {
        coordonnees = new int[96][2];
        int tmp[96][2] = {
            {355, 725}, {295, 725}, {234, 725}, {234, 788}, {234, 848}, {175, 848}, {112, 832}, {66, 787}, {51, 726},
            {51, 665}, {51, 605}, {51, 543}, {51, 480}, {112, 480}, {172, 480}, {172, 420},
            {172, 358}, {172, 295}, {174, 235}, {111, 235}, {50, 235}, {50, 175}, {67, 112}, {112, 67}, {171, 51},
            {232, 51}, {292, 51}, {354, 51}, {414, 51}, {415, 112}, {415, 174}, {475, 174}, {534, 174}, {596, 172},
            {658, 172}, {658, 111}, {657, 51}, {719, 50}, {779, 50}, {780, 111}, {838, 112}, {898, 112}, {899, 53},
            {961, 53}, {1019, 52}, {1019, 112}, {1021, 174}, {1078, 175}, {1140, 175}, {1200, 175}, {1262, 175},
            {1262, 115}, {1262, 52}, {1323, 52}, {1383, 69}, {1427, 113}, {1443, 175}, {1445, 237}, {1445, 299},
            {1445, 360}, {1443, 420}, {1382, 420}, {1320, 420}, {1321, 482}, {1322, 544}, {1322, 605}, {1322, 666},
            {1385, 666}, {1443, 666}, {1443, 728}, {1429, 788}, {1383, 835}, {1322, 850}, {1262, 850}, {1200, 850},
            {1140, 850}, {1079, 850}, {1079, 790}, {1079, 728}, {1020, 728}, {959, 728}, {900, 727}, {838, 727},
            {838, 790}, {838, 850}, {778, 850}, {718, 850}, {718, 790}, {656, 788}, {595, 788}, {595, 850}, {535, 850},
            {474, 850}, {474, 790}, {475, 727}, {415, 727}
        };
        for (int i = 0; i < 96; i++) {
            coordonnees[i][0] = tmp[i][0];
            coordonnees[i][1] = tmp[i][1];
        }
    } else {
        coordonnees = new int[64][2];
        int tmp[64][2] = {
            {398, 808}, {330, 807}, {263, 807}, {263, 875}, {263, 943}, {195, 943}, {127, 926}, {76, 875}, {59, 808},
            {59, 741}, {59, 672}, {59, 605}, {59, 537}, {127, 537}, {195, 537}, {195, 470}, {194, 402}, {194, 334},
            {194, 266}, {126, 266}, {58, 266}, {59, 198}, {78, 131}, {127, 82}, {194, 63}, {262, 63}, {329, 63},
            {398, 63}, {465, 63}, {464, 131}, {464, 199}, {530, 198}, {597, 198}, {666, 198}, {733, 198}, {733, 130},
            {733, 61}, {801, 62}, {869, 81}, {918, 129}, {936, 197}, {937, 265}, {936, 332}, {936, 400}, {936, 468},
            {868, 469}, {801, 469}, {801, 537}, {800, 604},/**/ {800, 671}, {800, 739}, {869, 739}, {936, 739},
            {936, 807},
            {920, 875}, {869, 925}, {800, 940}, {734, 942}, {666, 942}, {597, 942}, {530, 942}, {530, 873}, {531, 807},
            {466, 808}
        };
        for (int i = 0; i < 64; i++) {
            coordonnees[i][0] = tmp[i][0];
            coordonnees[i][1] = tmp[i][1];
        }
    }
}

ImageViewer::~ImageViewer() {
    SDL_DestroyTexture(texturePlateau);
    SDL_DestroyTexture(textureTas);
    SDL_DestroyTexture(textureCartes[0]);
    SDL_DestroyTexture(textureCartes[1]);
    SDL_DestroyTexture(textureCartes[2]);
    SDL_DestroyTexture(textureCartes[3]);
    delete [] coordonnees;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void ImageViewer::dessineCercle(int couleur, int x, int y) const {
    filledCircleRGBA(renderer, x, y, 22 * zoom, 0, 0, 0, 255);
    filledCircleRGBA(renderer, x, y, 19 * zoom, 255, 255, 255, 255);
    float rayon = 15 * zoom;
    switch (couleur) {
        case 1:
            filledCircleRGBA(renderer, x, y, rayon, 0, 255, 0, 255);
            break;
        case 2:
            filledCircleRGBA(renderer, x, y, rayon, 255, 0, 0, 255);
            break;
        case 3:
            filledCircleRGBA(renderer, x, y, rayon, 0, 0, 255, 255);
            break;
        case 4:
            filledCircleRGBA(renderer, x, y, rayon, 255, 255, 0, 255);
            break;
        case 5:
            filledCircleRGBA(renderer, x, y, rayon, 0, 0, 0, 255);
            break;
        case 6:
            filledCircleRGBA(renderer, x, y, rayon, 255, 255, 255, 255);
            break;
        default:
            break;
    }
}

void ImageViewer::dessineTriangle(int couleur, int x, int y) const {
    float grandRayon = 20 * zoom;
    float moyenRayon = 15 * zoom;
    float petitRayon = 10 * zoom;
    filledTrigonRGBA(renderer, x, y - grandRayon, x + grandRayon, y + grandRayon, x - grandRayon, y + grandRayon, 0, 0,
                     0, 255);
    filledTrigonRGBA(renderer, x, y - moyenRayon, x + moyenRayon, y + moyenRayon, x - moyenRayon, y + moyenRayon, 255,
                     255, 255, 255);
    switch (couleur) {
        case 1:
            filledTrigonRGBA(renderer, x, y - petitRayon, x + petitRayon, y + petitRayon, x - petitRayon,
                             y + petitRayon, 0, 255, 0, 255);
            break;
        case 2:
            filledTrigonRGBA(renderer, x, y - petitRayon, x + petitRayon, y + petitRayon, x - petitRayon,
                             y + petitRayon, 255, 0, 0, 255);
            break;
        case 3:
            filledTrigonRGBA(renderer, x, y - petitRayon, x + petitRayon, y + petitRayon, x - petitRayon,
                             y + petitRayon, 0, 0, 255, 255);
            break;
        case 4:
            filledTrigonRGBA(renderer, x, y - petitRayon, x + petitRayon, y + petitRayon, x - petitRayon,
                             y + petitRayon, 255, 255, 0, 255);
            break;
        case 5:
            filledTrigonRGBA(renderer, x, y - petitRayon, x + petitRayon, y + petitRayon, x - petitRayon,
                             y + petitRayon, 0, 0, 0, 255);
            break;
        case 6:
            filledTrigonRGBA(renderer, x, y - petitRayon, x + petitRayon, y + petitRayon, x - petitRayon,
                             y + petitRayon, 255, 255, 255, 255);
            break;
        default:
            break;
    }
}

void ImageViewer::debugCoordonnees() const {
    for (int i = 0; i < 16 * nbJ; i++) {
        dessineCercle(1, coordonnees[i][0] * zoom, coordonnees[i][1] * zoom);
    }
}

void ImageViewer::afficherPions(const Jeu &jeu) const {
    for (int i = 1; i < 4 * nbJ + 1; i++) {
        Pion pion = jeu.getPion(i);
        int indice = pion.getPos();
        if (indice >= 0) {
            if (pion.estPieu()) {
                dessineTriangle((i - 1) / 4 + 1, coordonnees[indice][0] * zoom, coordonnees[indice][1] * zoom);
            } else {
                dessineCercle((i - 1) / 4 + 1, coordonnees[indice][0] * zoom, coordonnees[indice][1] * zoom);
            }
        }
    }
}

void ImageViewer::setTextureCartes(const Jeu &jeu, int joueur) {
    if (renderer == nullptr) {
        std::cerr << "Erreur : le renderer est invalide." << std::endl;
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (textureCartes[i] != nullptr) {
            SDL_DestroyTexture(textureCartes[i]);
        }
        Carte *carte = jeu.getJoueur(joueur).getCarte(i);
        if (carte == nullptr) {
            textureCartes[i] = IMG_LoadTexture(renderer, "./data/cartes/0.png");
            if (textureCartes[i] == nullptr) {
                std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                return;
            }
        } else {
            int valeur = carte->getValeur();
            if (valeur != -1) {
                char chemin[30];
                sprintf(chemin, "./data/cartes/%d.png", abs(valeur));
                textureCartes[i] = IMG_LoadTexture(renderer, chemin);
                if (textureCartes[i] == nullptr) {
                    std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                    return;
                }
            } else {
                textureCartes[i] = IMG_LoadTexture(renderer, "./data/cartes/joker.png");
                if (textureCartes[i] == nullptr) {
                    std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                    return;
                }
            }
        }
        cout << "Chargement texture carte " << i << " pour joueur " << joueur << endl;
    }
}

void ImageViewer::gestionEvent(SDL_Event event, bool &running, int &imgWidth, int &imgHeight, SDL_Rect &RectMain1,SDL_Rect &RectMain2, SDL_Rect &RectMain3, SDL_Rect &RectMain4, SDL_Rect &RectTas,Jeu &jeu) {
    if (event.type == SDL_QUIT) {
        running = false;
    }
    if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_ESCAPE) {
            running = false;
        }
        if (event.key.keysym.sym == SDLK_t) {
            zoom = zoom + 0.05;
            imgWidth = dimx * zoom;
            imgHeight = dimy * zoom;
            SDL_SetWindowSize(window, imgWidth + 200 * zoom, imgHeight);
            RectMain1 = {imgWidth, 0, (int) (200 * zoom), (int) (250 * zoom)};
            RectMain2 = {imgWidth, (int) (250 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
            RectMain3 = {imgWidth, (int) (500 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
            RectMain4 = {imgWidth, (int) (750 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
            RectTas = {
                (int) (imgWidth / 2 - 100 * zoom), (int) (imgHeight / 2 - 150 * zoom), (int) (200 * zoom),
                (int) (300 * zoom)
            };
        }
        if (event.key.keysym.sym == SDLK_q) {
            zoom = zoom - 0.05;
            imgWidth = dimx * zoom;
            imgHeight = dimy * zoom;
            SDL_SetWindowSize(window, imgWidth + 200 * zoom, imgHeight);
            RectMain1 = {imgWidth, 0, (int) (200 * zoom), (int) (250 * zoom)};
            RectMain2 = {imgWidth, (int) (250 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
            RectMain3 = {imgWidth, (int) (500 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
            RectMain4 = {imgWidth, (int) (750 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
            RectTas = {
                (int) (imgWidth / 2 - 100 * zoom), (int) (imgHeight / 2 - 150 * zoom), (int) (200 * zoom),
                (int) (300 * zoom)
            };
        }
        /*if (event.key.keysym.sym == SDLK_SPACE) {
            if (jeu.getPioche().getTas() != nullptr) {
                int tas = jeu.getPioche().getTas()->getValeur();
                cout << tas << "\n";
                SDL_Surface *newSurfaceTas = IMG_Load("./data/cartes/1.png");
                SDL_Texture *newTextureTas = SDL_CreateTextureFromSurface(renderer, newSurfaceTas);
                SDL_FreeSurface(newSurfaceTas);
                if (newTextureTas != nullptr) {
                    SDL_DestroyTexture(textureTas);
                    textureTas = newTextureTas;
                }
            }
        }*/
        if (event.key.keysym.sym == SDLK_u) {
            setTextureCartes(jeu, 1);
            //phase = 1 - phase;
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            //cout << "{" << event.button.x << "," << event.button.y << "}, ";
            //cout << getIndiceCase(jeu, event.button.x, event.button.y, coordonnees, zoom) << endl;
            if (event.button.x > imgWidth) {
                int indiceCase = event.button.y / (250 * zoom);
                cout << indiceCase << endl;
                int valeur = jeu.getJoueur(1).getCarte(indiceCase)->getValeur();
                cout << "La valeur de la carte : " << valeur << endl;
                if (jeu.carteJouable(1, valeur)) {
                    cout << "La carte est jouable" << endl;
                }
            }
        }
    }
}

void ImageViewer::afficher(Jeu &jeu) {
    int imgWidth = (int) (dimx * zoom);
    int imgHeight = (int) (dimy * zoom);

    SDL_Rect RectMain1 = {imgWidth, 0, (int) (200 * zoom), (int) (250 * zoom)};
    SDL_Rect RectMain2 = {imgWidth, (int) (250 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
    SDL_Rect RectMain3 = {imgWidth, (int) (500 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
    SDL_Rect RectMain4 = {imgWidth, (int) (750 * zoom), (int) (200 * zoom), (int) (250 * zoom)};
    SDL_Rect RectTas = {
        (int) (imgWidth / 2 - 100 * zoom), (int) (imgHeight / 2 - 150 * zoom), (int) (200 * zoom),
        (int) (300 * zoom)
    };

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            gestionEvent(event, running, imgWidth, imgHeight, RectMain1, RectMain2, RectMain3, RectMain4,
                         RectTas, jeu);
        }
        for (int i = 0; i<3; i++) {
            if (textureCartes[i] == nullptr) {
                std::cerr << "Texture 0 est NULL!" << std::endl;
            }
        }
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect = {0, 0, imgWidth, imgHeight};
        SDL_RenderCopy(renderer, texturePlateau, NULL, &Rect);
        if (texturePlateau == nullptr) {
            std::cerr << "texturePlateau est NULL !" << std::endl;
        } else {
            std::cout << "texturePlateau OK" << std::endl;
        }
        //afficherPions(jeu);
        //setTextureCartes(jeu, 1);
        SDL_RenderCopy(renderer, textureTas, NULL, &RectTas);
        SDL_RenderCopy(renderer, textureCartes[0], NULL, &RectMain1);
        SDL_RenderCopy(renderer, textureCartes[1], NULL, &RectMain2);
        SDL_RenderCopy(renderer, textureCartes[2], NULL, &RectMain3);
        SDL_RenderCopy(renderer, textureCartes[3], NULL, &RectMain4);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        //cout << "Fin de boucle \n";
        //cout << imgHeight << " " << imgWidth << endl;
    }
}
