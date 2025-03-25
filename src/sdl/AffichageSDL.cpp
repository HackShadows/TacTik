
#include "AffichageSDL.h"

int getIndiceCase(const Jeu & jeu, int posx, int posy, int tab[][2]){
    if (jeu.getNbJoueurs() == 6){
        //rayon : 20
        for (int i = 0; i<96; i++){
            if (abs(posx-tab[i][0]) < 20 && abs(posy - tab[i][1]) < 20){
                cout << i;
                return i;
            }
        }
    }
    return 0;
}



ImageViewer::ImageViewer(const Jeu & jeu){
    cout << "SDL: init" << endl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    cout << "SDL_image: init" << endl;
    if (!(IMG_Init(imgFlags) & imgFlags))
    {
        cout << "SDL_m_image could not initialize! SDL_m_image Error: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
    if (jeu.getNbJoueurs() == 6){
        dimx = 1500;
        dimy = 890;
        
    }
    else{
        dimx = 1000;
        dimy = 997;
    }

    // Creation de la fenetre
    window = SDL_CreateWindow("Tac-Tik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx, dimy, 0);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}


ImageViewer::~ImageViewer(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void ImageViewer::afficher(const Jeu & jeu){
    int (*tab)[2] = nullptr;

    if (jeu.getNbJoueurs() == 6) {
        surface = IMG_Load("./data/plateau6.png");
        int tmp[96][2] = {{355,715}, {300,715}, {230,720}, {235,780}, {235,840}, {170,840}, {115,825}, {70,780}, {50,715}, {50,660}, {50,600}, {50,530}, {50,475}, {110,480}, {170,475}, {175,415},
        {172,354}, {171,292}, {174,235}, {112,231}, {51,232}, {50,175}, {66,110}, {110,67}, {170,49}, {231,50}, {292,51}, {354,50}, {412,49}, {416,111}, {415,170}, {476,170}, {534,171}, {596,172}, 
        {658,172}, {657,108}, {654,52}, {719,48}, {778,49}, {782,110}, {836,112}, {898,111}, {899,53}, {960,50}, {1019,50}, {1019,112}, {1021,174}, {1077,173}, {1140,171}, {1199,174}, {1262,175}, 
        {1262,115}, {1260,51}, {1322,52}, {1384,68}, {1427,113}, {1443,172}, {1445,233}, {1445,295}, {1444,355}, {1444,417}, {1384,415}, {1323,415}, {1323,477}, {1321,535}, {1322,597}, {1324,660}, 
        {1384,658}, {1442,658}, {1443,719}, {1428,780}, {1383,824}, {1321,838}, {1260,840}, {1200,841}, {1140,840}, {1078,840}, {1081,778}, {1080,719}, {1021,719}, {957,718}, {899,720}, {841,718}, 
        {840,778}, {839,840}, {777,839}, {719,839}, {716,777}, {656,779}, {595,775}, {597,839}, {533,838}, {472,841}, {474,778}, {475,717}, {415,717}};
        tab = tmp;
    } 
    else {
        surface = IMG_Load("./data/plateau4.png");
        int tmp[16][2] = {{355,715}, {300,715}, {230,720}, {235,780}, {235,840}, {170,840}, {115,825}, {70,780}, {50,715}, {50,660}, {50,600}, {50,530}, {50,475}, {110,480}, {170,475}, {175,415}};
        tab = tmp;
    }
    if (surface == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        std::cerr << "Erreur de création de la texture : " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return;
    }

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                if(event.button.button==SDL_BUTTON_LEFT){
                    //cout << "{" << event.button.x << "," << event.button.y << "}, ";
                    getIndiceCase(jeu, event.button.x, event.button.y, tab);
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect = { 0, 0, dimx, dimy};
        SDL_RenderCopy(renderer, texture, NULL, &Rect);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
    SDL_DestroyTexture(texture);
}



