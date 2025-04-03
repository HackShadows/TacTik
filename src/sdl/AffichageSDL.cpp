/**
* @brief Contient l'implémentation de l'affichege graphique
*/

#include "AffichageSDL.h"

int getIndiceCase(const Jeu &jeu, int posx, int posy, const int tab[][2], float zoom) {
    float rayon = 20 * zoom;
    //cout << posx << " " << posy << " " << tab[0][0] * zoom << " " << tab[0][1] * zoom << " ";
    for (int i = 0; i < 16*jeu.getNbJoueurs(); i++) {
        if (abs(posx - tab[i][0] * zoom) < rayon && abs(posy - tab[i][1] * zoom) < rayon) {
            return i;
        }
    }
    return -1;
}

void ImageViewer::dessineCercle(int couleur, int x, int y) {
    filledCircleRGBA(renderer, x, y, 20 * zoom, 0, 0, 0, 255);
    filledCircleRGBA(renderer, x, y, 17 * zoom, 255, 255, 255, 255);
    float rayon = 13 * zoom;
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

void ImageViewer::dessineTriangle(int couleur, int x, int y) {
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

void ImageViewer::debugCoordonnees(const int tab[][2]) {
    for (int i = 0; i < 16 * nbJ; i++) {
        dessineCercle(1, tab[i][0] * zoom, tab[i][1]*zoom);
        //filledCircleRGBA(renderer, tab[i][0]*zoom, tab[i][1], 20 * zoom, 0, 0, 0, 255);
        /*SDL_Rect rect = {(int) (tab[i][0] * zoom), (int) (tab[i][1] * zoom), (int) (20 * zoom), (int) (20 * zoom)};
        SDL_RenderFillRect(renderer, &rect);*/
    }
}

void ImageViewer::afficherPions(const Jeu &jeu, const int tab[][2]) {
    for (int i = 1; i < 4 * nbJ + 1; i++) {
        Pion pion = jeu.getPion(i);
        int indice = pion.getPos();
        if (indice >= 0) {
            if (pion.estPieu()) {
                dessineTriangle((i - 1) / 4 + 1, tab[indice][0] * zoom, tab[indice][1] * zoom);
            } else {
                dessineCercle((i - 1) / 4 + 1, tab[indice][0] * zoom, tab[indice][1] * zoom);
            }
        }
    }
}

void ImageViewer::setTextureCartes(const Jeu &jeu, int joueur) {

    for (int i = 0; i<4; i++) {
        Carte * carte = jeu.getJoueur(joueur).getCarte(i);
        if (carte == nullptr) {
            surfaceCartes[i] = IMG_Load("./data/cartes/0.png");
            if (surfaceCartes[i] == nullptr) {
                std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                return;
            }
        }
        else {
            int valeur = carte->getValeur();
            if (valeur > 0) {
                char chemin [30];
                sprintf(chemin, "./data/cartes/%d.png", valeur);
                surfaceCartes[i] = IMG_Load(chemin);
                if (surfaceCartes[i] == nullptr) {
                    std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                    return;
                }
            }
            else {
                surfaceCartes[i] = IMG_Load("./data/cartes/joker.png");
                if (surfaceCartes[i] == nullptr) {
                    std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                    return;
                }
            }
        }
    }
}



void ImageViewer::afficherTas(const Jeu &jeu) {
    surfaceTas = IMG_Load("./data/cartes/0.png");
    if (surfaceTas == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture *textureTas = SDL_CreateTextureFromSurface(renderer, surfaceTas);
    SDL_FreeSurface(surfaceTas);
    SDL_Rect RectTas = {0, 0, 100, 50};
    SDL_RenderCopy(renderer, textureTas, NULL, &RectTas);
}

ImageViewer::ImageViewer(const Jeu &jeu) {
    zoom = 0.75;
    nbJ = jeu.getNbJoueurs();
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
        dimx = (int) 1500;
        dimy = (int) 900;
    } else {
        dimx = (int) 1000;
        dimy = (int) 1000;
    }

    window = SDL_CreateWindow("Tac-Tik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx * zoom, dimy * zoom,
                              SDL_WINDOW_RESIZABLE);
    if (window == NULL) {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    surfacePlateau = nbJ == 4 ? IMG_Load("./data/plateau/plateau4.png") : IMG_Load("./data/plateau/plateau6.png");
    surfaceTas = IMG_Load("./data/cartes/0.png");
    surfaceCartes[0] = IMG_Load("./data/cartes/0.png");
    surfaceCartes[1] = IMG_Load("./data/cartes/0.png");
    surfaceCartes[2] = IMG_Load("./data/cartes/0.png");
    surfaceCartes[3] = IMG_Load("./data/cartes/0.png");
    if (surfacePlateau == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (surfaceTas == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (surfaceCartes[0] == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (surfaceCartes[1] == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (surfaceCartes[2] == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (surfaceCartes[3] == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
}


ImageViewer::~ImageViewer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void ImageViewer::afficher(const Jeu &jeu) {
    int imgWidth = (int) dimx * zoom;
    int imgHeight = (int) dimy * zoom;
    int (*tab)[2] = nullptr;

    if (nbJ == 6) {
        tab = new int[96][2];
        int tmp[96][2] = {
            {355, 725}, {295, 725}, {234, 725}, {234, 788}, {234, 848}, {175, 848}, {112, 832}, {66, 787}, {51, 726},
            {51, 665}, {51, 605}, {51, 543}, {51, 480}, {112, 480}, {172, 480}, {172, 420},
            {172, 358}, {172, 295}, {174, 235}, {111, 235}, {50, 235}, {50, 175}, {67, 112}, {112, 67}, {171, 51},
            {232, 51}, {292, 51}, {354, 51}, {414, 51}, {415, 112}, {415, 174}, {475, 174}, {534, 174}, {596, 172},
            {658, 172}, {658, 111}, {657, 51}, {719, 50}, {779, 50}, {780, 111}, {838, 112}, {898, 112}, {899, 53},
            {961, 53}, {1019, 52}, {1019, 112}, {1021, 174}, {1078, 175}, {1140, 175}, {1199, 174}, {1262, 175},
            {1262, 115}, {1260, 51}, {1322, 52}, {1384, 68}, {1427, 113}, {1443, 172}, {1445, 233}, {1445, 295},
            {1444, 355}, {1444, 417}, {1384, 415}, {1323, 415}, {1323, 477}, {1321, 535}, {1322, 597}, {1324, 660},
            {1384, 658}, {1442, 658}, {1443, 719}, {1428, 780}, {1383, 824}, {1321, 838}, {1260, 840}, {1200, 841},
            {1140, 840}, {1078, 840}, {1081, 778}, {1080, 719}, {1021, 719}, {957, 718}, {899, 720}, {841, 718},
            {840, 778}, {839, 840}, {777, 839}, {719, 839}, {716, 777}, {656, 779}, {595, 775}, {597, 839}, {533, 838},
            {472, 841}, {474, 778}, {475, 717}, {415, 717}
        };
        for (int i = 0; i < 96; i++) {
            tab[i][0] = tmp[i][0];
            tab[i][1] = tmp[i][1];
        }
    }
    else {
        tab = new int[64][2];
        int tmp[64][2] = {
            {396, 810}, {330, 814}, {266, 810}, {264, 880}, {264, 946}, {196, 946}, {128, 928}, {76, 878}, {60, 812},
            {62, 744}, {56, 678}, {62, 608}, {60, 540}, {128, 542}, {194, 540}, {198, 476}, {196, 404}, {200, 338},
            {198, 272}, {128, 270}, {58, 272}, {58, 198}, {82, 134}, {130, 82}, {192, 64}, {262, 66}, {328, 68},
            {400, 66}, {466, 66}, {464, 134}, {468, 202}, {532, 202}, {600, 200}, {666, 198}, {736, 200}, {736, 134},
            {732, 64}, {802, 66}, {872, 84}, {922, 132}, {936, 198}, {938, 262}, {936, 332}, {938, 404}, {934, 468},
            {868, 472}, {802, 470}, {802, 538}, {800, 606}, {802, 672}, {804, 742}, {870, 744}, {938, 738}, {938, 808},
            {920, 878}, {872, 926}, {802, 944}, {738, 944}, {666, 942}, {596, 942}, {532, 944}, {530, 876}, {530, 810},
            {468, 810}
        };
        for (int i = 0; i < 64; i++) {
            tab[i][0] = tmp[i][0];
            tab[i][1] = tmp[i][1];
        }
    }
    SDL_Texture *texturePlateau = SDL_CreateTextureFromSurface(renderer, surfacePlateau);
    SDL_FreeSurface(surfacePlateau);
    if (texturePlateau == nullptr) {
        std::cerr << "Erreur de création de la texture : " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surfacePlateau);
        return;
    }

    SDL_Texture *textureTas = SDL_CreateTextureFromSurface(renderer, surfaceTas);
    SDL_FreeSurface(surfaceTas);

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
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
                    SDL_SetWindowSize(window, imgWidth, imgHeight);
                }
                if (event.key.keysym.sym == SDLK_q) {
                    zoom = zoom - 0.05;
                    imgWidth = dimx * zoom;
                    imgHeight = dimy * zoom;
                    SDL_SetWindowSize(window, imgWidth, imgHeight);
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
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
                }
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        //cout << "{" << event.button.x << "," << event.button.y << "}, ";
                        cout << getIndiceCase(jeu, event.button.x, event.button.y, tab, zoom) << endl;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect = {0, 0, imgWidth, imgHeight};
        SDL_RenderCopy(renderer, texturePlateau, NULL, &Rect);
        SDL_Rect RectTas = {
            (int) (imgWidth / 2 - 100 * zoom), (int) (imgHeight / 2 - 150 * zoom), (int) (200 * zoom),
            (int) (300 * zoom)
        };
        SDL_RenderCopy(renderer, textureTas, NULL, &RectTas);
        debugCoordonnees(tab);
        /*setTextureCartes(jeu, 1);
        SDL_Texture *textureMain1 = SDL_CreateTextureFromSurface(renderer, surfaceCartes[0]);
        SDL_FreeSurface(surfaceCartes[0]);
        SDL_Rect RectMain1 = {0, 0, 200, 100};
        SDL_RenderCopy(renderer, textureMain1, NULL, &RectMain1);

        SDL_Texture *textureMain2 = SDL_CreateTextureFromSurface(renderer, surfaceCartes[1]);
        SDL_FreeSurface(surfaceCartes[1]);
        SDL_Rect RectMain2 = {200, 0, 200, 100};
        SDL_RenderCopy(renderer, textureMain2, NULL, &RectMain2);

        SDL_Texture *textureMain3 = SDL_CreateTextureFromSurface(renderer, surfaceCartes[2]);
        SDL_FreeSurface(surfaceCartes[2]);
        SDL_Rect RectMain3 = {400, 0, 200, 100};
        SDL_RenderCopy(renderer, textureMain3, NULL, &RectMain3);

        SDL_Texture *textureMain4 = SDL_CreateTextureFromSurface(renderer, surfaceCartes[3]);
        SDL_FreeSurface(surfaceCartes[3]);
        SDL_Rect RectMain4 = {600, 0, 200, 100};
        SDL_RenderCopy(renderer, textureMain4, NULL, &RectMain4);
*/
        //afficherPions(jeu, tab);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        /*SDL_DestroyTexture(textureMain1);
        SDL_DestroyTexture(textureMain2);
        SDL_DestroyTexture(textureMain3);
        SDL_DestroyTexture(textureMain4);*/
    }
    SDL_DestroyTexture(texturePlateau);
    SDL_DestroyTexture(textureTas);
    delete [] tab;
}
