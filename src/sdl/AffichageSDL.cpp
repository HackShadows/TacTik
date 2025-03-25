
#include "AffichageSDL.h"


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
    if (jeu.getNbJoueurs() == 6){
        surface = IMG_Load("./data/plateau6.png");
    }
    else{
        surface = IMG_Load("./data/plateau4.png");
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



