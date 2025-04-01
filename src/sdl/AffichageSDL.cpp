
#include "AffichageSDL.h"

int getIndiceCase(const Jeu & jeu, int posx, int posy, const int tab[][2], float zoom){
  float rayon = 20 * zoom;
    if (jeu.getNbJoueurs() == 6){
        cout << posx << " " << posy << " " << tab[0][0]*zoom << " " << tab[0][1]*zoom << " ";
        for (int i = 0; i<96; i++){
            if (abs(posx-tab[i][0]*zoom) < rayon && abs(posy - tab[i][1]*zoom) < rayon ){
                //cout << i;
                return i;
            }
        }
    }
    else{
          cout << posx << " " << posy << " " << tab[0][0]*zoom << " " << tab[0][1]*zoom << " ";
    	  for (int i = 0; i<64; i++){
            if (abs(posx-tab[i][0]*zoom) < rayon && abs(posy - tab[i][1]*zoom) < rayon){
                //cout << i;
                return i;
            }
        }
    }
    return -1;
}

void ImageViewer::setRGB(int couleur){
      switch couleur{
              case 1:
              case 2:
              case 3:
              case 4:
              case 5:
              case 6:
              default:
                  break;
          }
}


void ImageViewer::debugCoordonnees(const int tab[][2]){
    for (int i = 0; i<16*nbJ; i++){
        SDL_Rect rect = { tab[i][0]*zoom, tab[i][1]*zoom, 20*zoom, 20*zoom };
        SDL_RenderFillRect(renderer, &rect);
    }
}

void ImageViewer::afficherPions(const Jeu & jeu, const int tab[][2]){
    for (int i = 0; i<4*nbJ; i++){
        Pion pion = jeu.getPion(i);
        int indice = pion.getPos();
        if (indice >=0){
            if (pion.estPieu()){
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_Rect rect = { tab[indice][0]*zoom, tab[indice][1]*zoom, 20*zoom, 20*zoom };
                SDL_RenderFillRect(renderer, &rect);
            }
            else{
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Blanc
                SDL_Rect rect = { tab[i][0]*zoom, tab[i][1]*zoom, 20*zoom, 20*zoom };
                SDL_RenderFillRect(renderer, &rect);
            }

        }

    	}
    }
}


void ImageViewer::afficherTas(const Jeu & jeu){
    SDL_Surface * surfaceTas = IMG_Load("./data/cartes/dos.png");
    if (surfaceTas == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    SDL_Texture *textureTas = SDL_CreateTextureFromSurface(renderer, surfaceTas);
    SDL_FreeSurface(surfaceTas);
    SDL_Rect RectTas = { 0, 0, 100, 50};
    SDL_RenderCopy(renderer, textureTas, NULL, &RectTas);
}

ImageViewer::ImageViewer(const Jeu & jeu){
  	zoom = 0.75;
    nbJ = jeu.getNbJoueurs();
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
    if (nbJ == 6){
        dimx = (int) 1500;
        dimy = (int) 900;
        
    }
    else{
        dimx = (int) 1000;
        dimy = (int) 1000;
    }

    // Creation de la fenetre
    window = SDL_CreateWindow("Tac-Tik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimx * zoom, dimy * zoom, SDL_WINDOW_RESIZABLE);
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
    int imgWidth = (int) dimx * zoom;
    int imgHeight = (int) dimy * zoom;

    int (*tab)[2] = nullptr;
	cout << "Nouvel appel de fct \n";
    if (nbJ == 6) {
        surface = IMG_Load("./data/plateau/plateau6.png");
        tab = new int[96][2];
        int tmp[96][2] = {{355,715}, {300,715}, {230,720}, {235,780}, {235,840}, {170,840}, {115,825}, {70,780}, {50,715}, {50,660}, {50,600}, {50,530}, {50,475}, {110,480}, {170,475}, {175,415},
        {172,354}, {171,292}, {174,235}, {112,231}, {51,232}, {50,175}, {66,110}, {110,67}, {170,49}, {231,50}, {292,51}, {354,50}, {412,49}, {416,111}, {415,170}, {476,170}, {534,171}, {596,172}, 
        {658,172}, {657,108}, {654,52}, {719,48}, {778,49}, {782,110}, {836,112}, {898,111}, {899,53}, {960,50}, {1019,50}, {1019,112}, {1021,174}, {1077,173}, {1140,171}, {1199,174}, {1262,175}, 
        {1262,115}, {1260,51}, {1322,52}, {1384,68}, {1427,113}, {1443,172}, {1445,233}, {1445,295}, {1444,355}, {1444,417}, {1384,415}, {1323,415}, {1323,477}, {1321,535}, {1322,597}, {1324,660}, 
        {1384,658}, {1442,658}, {1443,719}, {1428,780}, {1383,824}, {1321,838}, {1260,840}, {1200,841}, {1140,840}, {1078,840}, {1081,778}, {1080,719}, {1021,719}, {957,718}, {899,720}, {841,718}, 
        {840,778}, {839,840}, {777,839}, {719,839}, {716,777}, {656,779}, {595,775}, {597,839}, {533,838}, {472,841}, {474,778}, {475,717}, {415,717}};
        for (int i = 0; i<96; i++){
          	tab[i][0] = tmp[i][0];
            tab[i][1] = tmp[i][1];
        }
        cout << "passage creation tab \n";
    } 
    else {
        surface = IMG_Load("./data/plateau/plateau4.png");
        tab = new int[64][2];
        int tmp[64][2] = {{396,810}, {330,814}, {266,810}, {264,880}, {264,946}, {196,946}, {128,928}, {76,878}, {60,812},
                           {62,744}, {56,678}, {62,608}, {60,540}, {128,542}, {194,540}, {198,476}, {196,404}, {200,338},
                           {198,272}, {128,270}, {58,272}, {58,198}, {82,134}, {130,82}, {192,64}, {262,66}, {328,68},
                           {400,66}, {466,66}, {464,134}, {468,202}, {532,202}, {600,200}, {666,198}, {736,200}, {736,134},
                           {732,64}, {802,66}, {872,84}, {922,132}, {936,198}, {938,262}, {936,332}, {938,404}, {934,468},
                           {868,472}, {802,470}, {802,538}, {800,606}, {802,672}, {804,742}, {870,744}, {938,738}, {938,808},
                           {920,878}, {872,926}, {802,944}, {738,944}, {666,942}, {596,942}, {532,944}, {530,876}, {530,810},
                           {468,810}};
		for (int i = 0; i<64; i++){
          	tab[i][0] = tmp[i][0];
            tab[i][1] = tmp[i][1];
        }
        cout << "passage creation tab \n";    }
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

    SDL_Surface * surfaceTas = IMG_Load("./data/cartes/dos.png");
    if (surfaceTas == nullptr) {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
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
				if (event.key.keysym.sym == SDLK_t){
                    zoom = zoom + 0.05;
                    imgWidth = dimx * zoom;
                    imgHeight = dimy * zoom;
                    SDL_SetWindowSize(window, imgWidth, imgHeight);
                }
                if (event.key.keysym.sym == SDLK_q){
                    zoom = zoom - 0.05;
                    imgWidth = dimx * zoom;
                    imgHeight = dimy * zoom;
                    SDL_SetWindowSize(window, imgWidth, imgHeight);
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                	if (jeu.getPioche().getTas() != nullptr){
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
                if (event.type == SDL_MOUSEBUTTONDOWN){
                    if(event.button.button==SDL_BUTTON_LEFT){
                        //cout << "{" << event.button.x << "," << event.button.y << "}, ";
                        cout << getIndiceCase(jeu, event.button.x, event.button.y, tab, zoom) << endl;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
        SDL_RenderClear(renderer);
        SDL_Rect Rect = { 0, 0, imgWidth, imgHeight};
        SDL_RenderCopy(renderer, texture, NULL, &Rect);
        SDL_Rect RectTas = { imgWidth/2 - 100*zoom, imgHeight/2 - 150*zoom, 200*zoom, 300*zoom};
        SDL_RenderCopy(renderer, textureTas, NULL, &RectTas);
        //debugCoordonnees(tab);
        afficherPions(jeu, tab);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        //cout << "Fin de boucle \n";
    }
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(textureTas);
}



