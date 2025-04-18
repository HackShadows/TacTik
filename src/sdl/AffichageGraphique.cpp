#include "AffichageGraphique.h"

#include <iostream>
#include <cassert>
#include <unordered_map>

using namespace std;

int getIndiceCase(Jeu * jeu, int posx, int posy, const int tab[][2], float zoom)
{
    float rayon = 20 * zoom;
    for (int i = 0; i < 16 * jeu->getNbJoueurs(); i++)
    {
        if (abs(posx - tab[i][0] * zoom) < rayon && abs(posy - tab[i][1] * zoom) < rayon)
        {
            return i;
        }
    }
    return -1;
}

ImageViewer::ImageViewer() 
{
    jeu = nullptr;
    zoom = 0.5;
    phase = 0;
    cout << "SDL: init" << endl;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    cout << "TTF: init" << endl;
    if (TTF_Init() != 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
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
    string ttffile = string("data/DejaVuSansCondensed.ttf");
    int n = 0;
    do
    {
        m_font = TTF_OpenFont(ttffile.c_str(), 50);
        n++;
        ttffile = "../" + ttffile;
    } while (m_font == nullptr && n < 3);

    if (m_font == nullptr)
    {
        cout << "Failed to load DejaVuSansCondensed.ttf! SDL_TTF Error: " << TTF_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    dimx = (int)1500;
    dimy = (int)900;
    
    window = SDL_CreateWindow("Tac-Tik", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (dimx + 200) * zoom,
                              (dimy + 100) * zoom,
                              SDL_WINDOW_RESIZABLE);
    if (window == NULL)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        exit(1);
    }

    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    for (int i = 0; i < 14; i++)
    {
        char chemin[100];
        sprintf(chemin, "./data/cartes/%d.png", i);
        listTexture[i] = IMG_LoadTexture(renderer, chemin);
    }
    listTexture[14] = IMG_LoadTexture(renderer, "./data/cartes/joker.png");
    textureTas = listTexture[0];
    textureCartes[0] = listTexture[0];
    textureCartes[1] = listTexture[0];
    textureCartes[2] = listTexture[0];
    textureCartes[3] = listTexture[0];

    
    if (textureTas == nullptr)
    {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureCartes[0] == nullptr)
    {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureCartes[1] == nullptr)
    {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureCartes[2] == nullptr)
    {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }
    if (textureCartes[3] == nullptr)
    {
        std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
        return;
    }

    imgWidth = (int)dimx * zoom;
    imgHeight = (int)dimy * zoom;

    for (int i = 0; i < 4; i++)
    {
        RectMain[i] = {imgWidth, (int)(i * imgHeight / 4), (int)(200 * zoom), (int)(imgHeight / 4)};
    }

    RectTas = {
        (int)(imgWidth / 2 - 100 * zoom), (int)(imgHeight / 2 - 150 * zoom), (int)(200 * zoom),
        (int)(300 * zoom)};
}

ImageViewer::~ImageViewer()
{
    delete[] coordonnees;
    delete[] coordonneesMaison;
    delete[] coordonneesReserve;
    for (int i = 0; i < 15; i++)
    {
        SDL_DestroyTexture(listTexture[i]);
    }
    SDL_DestroyTexture(texturePlateau);
    SDL_DestroyTexture(textureTas);
    SDL_DestroyTexture(textureCartes[0]);
    SDL_DestroyTexture(textureCartes[1]);
    SDL_DestroyTexture(textureCartes[2]);
    SDL_DestroyTexture(textureCartes[3]);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(m_font);
    TTF_Quit();
    SDL_Quit();
}

void ImageViewer::initJeu(int nbJoueurs, int nbIA){
    assert(nbIA >= 0 && nbJoueurs >= nbIA && (nbJoueurs == 4 || nbJoueurs == 6));
    jeu = new Jeu(nbJoueurs, nbIA);
    nbJ = jeu->getNbJoueurs();
    cout << nbJ << endl;
    if (nbJ == 6)
    {
        dimx = (int)1500;
        dimy = (int)900;
    }
    else
    {
        dimx = (int)1000;
        dimy = (int)1000;
    }
    imgWidth = (int)dimx * zoom;
    imgHeight = (int)dimy * zoom;

    for (int i = 0; i < 4; i++)
    {
        RectMain[i] = {imgWidth, (int)(i * imgHeight / 4), (int)(200 * zoom), (int)(imgHeight / 4)};
    }

    RectTas = {
        (int)(imgWidth / 2 - 100 * zoom), (int)(imgHeight / 2 - 150 * zoom), (int)(200 * zoom),
        (int)(300 * zoom)};
    SDL_SetWindowSize(window, imgWidth + 200 * zoom, imgHeight + 100 * zoom);
    if (nbJ == 6)
    {
        coordonnees = new int[96][2];
        coordonneesMaison = new int[24][2];
        coordonneesReserve = new int[24][2];
        int tmp[96][2] = {
            {355, 725}, {295, 725}, {234, 725}, {234, 788}, {234, 848}, {175, 848}, {112, 832}, {66, 787}, {51, 726}, {51, 665}, {51, 605}, {51, 543}, {51, 480}, {112, 480}, {172, 480}, {172, 420}, {172, 358}, {172, 295}, {174, 235}, {111, 235}, {50, 235}, {50, 175}, {67, 112}, {112, 67}, {171, 51}, {232, 51}, {292, 51}, {354, 51}, {414, 51}, {415, 112}, {415, 174}, {475, 174}, {534, 174}, {596, 172}, {658, 172}, {658, 111}, {657, 51}, {719, 50}, {779, 50}, {780, 111}, {838, 112}, {898, 112}, {899, 53}, {961, 53}, {1019, 52}, {1019, 112}, {1021, 174}, {1078, 175}, {1140, 175}, {1200, 175}, {1262, 175}, {1262, 115}, {1262, 52}, {1323, 52}, {1383, 69}, {1427, 113}, {1443, 175}, {1445, 237}, {1445, 299}, {1445, 360}, {1443, 420}, {1382, 420}, {1320, 420}, {1321, 482}, {1322, 544}, {1322, 605}, {1322, 666}, {1385, 666}, {1443, 666}, {1443, 728}, {1429, 788}, {1383, 835}, {1322, 850}, {1262, 850}, {1200, 850}, {1140, 850}, {1079, 850}, {1079, 790}, {1079, 728}, {1020, 728}, {959, 728}, {900, 727}, {838, 727}, {838, 790}, {838, 850}, {778, 850}, {718, 850}, {718, 790}, {656, 788}, {595, 788}, {595, 850}, {535, 850}, {474, 850}, {474, 790}, {475, 727}, {415, 727}};
        int tmpMaison[24][2] = {
            {266, 493}, {219, 492}, {175, 494}, {129, 492}, {179, 267}, {179, 221}, {178, 176}, {179, 130}, {854, 182}, {900, 183}, {946, 182}, {992, 183}, {940, 406}, {940, 451}, {940, 498}, {940, 542}, {401, 182}, {447, 180}, {492, 181}, {537, 181}, {718, 492}, {673, 493}, {628, 491}, {583, 493}};
        int tmpReserve[24][2] = {
            {399, 831}, {366, 803}, {335, 831}, {314, 803}, {62, 405}, {104, 372}, {58, 335}, {95, 308}, {1091, 73}, {1119, 99}, {1150, 65}, {1192, 96}, {1426, 488}, {1389, 529}, {1435, 561}, {1400, 584}, {485, 64}, {511, 96}, {548, 66}, {578, 91}, {1005, 830}, {986, 800}, {951, 827}, {914, 810}};
        for (int i = 0; i < 96; i++)
        {
            coordonnees[i][0] = tmp[i][0];
            coordonnees[i][1] = tmp[i][1];
        }
        for (int i = 0; i < 24; i++)
        {
            coordonneesMaison[i][0] = tmpMaison[i][0] * 1.33;
            coordonneesMaison[i][1] = tmpMaison[i][1] * 1.33;
        }
        for (int i = 0; i < 24; i++)
        {
            coordonneesReserve[i][0] = tmpReserve[i][0];
            coordonneesReserve[i][1] = tmpReserve[i][1];
        }
    }
    else
    {
        coordonnees = new int[64][2];
        coordonneesMaison = new int[16][2];
        coordonneesReserve = new int[16][2];
        int tmp[64][2] = {
            {398, 808}, {330, 807}, {263, 807}, {263, 875}, {263, 943}, {195, 943}, {127, 926}, {76, 875}, {59, 808}, {59, 741}, {59, 672}, {59, 605}, {59, 537}, {127, 537}, {195, 537}, {195, 470}, {194, 402}, {194, 334}, {194, 266}, {126, 266}, {58, 266}, {59, 198}, {78, 131}, {127, 82}, {194, 63}, {262, 63}, {329, 63}, {398, 63}, {465, 63}, {464, 131}, {464, 199}, {530, 198}, {597, 198}, {666, 198}, {733, 198}, {733, 130}, {733, 61}, {801, 62}, {869, 81}, {918, 129}, {936, 197}, {937, 265}, {936, 332}, {936, 400}, {936, 468}, {868, 469}, {801, 469}, {801, 537}, {800, 604}, /**/ {800, 671}, {800, 739}, {869, 739}, {936, 739}, {936, 807}, {920, 875}, {869, 925}, {800, 940}, {734, 942}, {666, 942}, {597, 942}, {530, 942}, {530, 873}, {531, 807}, {466, 808}};
        for (int i = 0; i < 64; i++)
        {
            coordonnees[i][0] = tmp[i][0];
            coordonnees[i][1] = tmp[i][1];
        }
        int tmpMaison[16][2] = {
            {397, 732}, {329, 732}, {262, 731}, {194, 732}, {268, 403}, {270, 335}, {267, 265}, {268, 198}, {596, 270}, {664, 272}, {731, 269}, {800, 273}, {724, 601}, {724, 671}, {723, 735}, {724, 803}};
        for (int i = 0; i < 16; i++)
        {
            coordonneesMaison[i][0] = tmpMaison[i][0];
            coordonneesMaison[i][1] = tmpMaison[i][1];
        }
        int tmpReserve[16][2] = {
            {346, 915}, {379, 881}, {419, 920}, {446, 889}, {77, 453}, {113, 414}, {72, 382}, {119, 346}, {548, 80}, {580, 118}, {620, 79}, {644, 112}, {883, 550}, {916, 578}, {884, 611}, {911, 650}};
        for (int i = 0; i < 16; i++)
        {
            coordonneesReserve[i][0] = tmpReserve[i][0];
            coordonneesReserve[i][1] = tmpReserve[i][1];
        }
    }
    texturePlateau = nbJ == 4
                         ? IMG_LoadTexture(renderer, "./data/plateau/plateau4.png")
                         : IMG_LoadTexture(renderer, "./data/plateau/plateau6.png");
}

Jeu &ImageViewer::getJeu()
{
    return *jeu;
}

float ImageViewer::getZoom()
{
    return zoom;
}

int ImageViewer::getImgWidth()
{
    return imgWidth;
}

int ImageViewer::getIndicePion(int posx, int posy)
{
    float rayon = 20 * zoom;
    for (int i = 0; i < 16 * jeu->getNbJoueurs(); i++)
    {
        if (abs(posx - coordonnees[i][0] * zoom) < rayon && abs(posy - coordonnees[i][1] * zoom) < rayon)
        {
            return jeu->getPlateau().getIdPion(i);
            // return i;
        }
    }
    return -1;
}

int ImageViewer::getIndicePionEvent(string s)
{
    cout << s;
    cout << "entrée \n";
    SDL_Event event;
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                float rayon = 20 * zoom;
                for (int i = 0; i < 16 * nbJ; i++)
                {
                    if (abs(event.button.x - coordonnees[i][0] * zoom) < rayon && abs(
                                                                                      event.button.y - coordonnees[i][1] * zoom) < rayon)
                    {
                        cout << "sortie \n";
                        return jeu->getPlateau().getIdPion(i);
                        // return getIndicePion(jeu, event.button.x, event.button.y);
                    }
                }
            }
        }
    }
}

int ImageViewer::getEventNumber(string s)
{
    cout << s;
    cout << "entrée \n";
    SDL_Event event;
    while (true)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                cout << "sortie \n";
                return 0;
            }
            if (event.key.keysym.sym == SDLK_0)
            {
                cout << "sortie \n";
                return 0;
            }
            if (event.key.keysym.sym == SDLK_1)
            {
                cout << "sortie \n";
                return 1;
            }
            if (event.key.keysym.sym == SDLK_2)
            {
                cout << "sortie \n";
                return 2;
            }
            if (event.key.keysym.sym == SDLK_3)
            {
                cout << "sortie \n";
                return 3;
            }
            if (event.key.keysym.sym == SDLK_4)
            {
                cout << "sortie \n";
                return 4;
            }
            if (event.key.keysym.sym == SDLK_5)
            {
                cout << "sortie \n";
                return 5;
            }
            if (event.key.keysym.sym == SDLK_6)
            {
                cout << "sortie \n";
                return 6;
            }
            if (event.key.keysym.sym == SDLK_7)
            {
                cout << "sortie \n";
                return 7;
            }
        }
    }
}

int ImageViewer::getBouton(int posx, int posy)
{
    if (posx> imgWidth / 4 && posx < imgWidth / 4 + 100 * zoom && posy > imgHeight / 2 - 50 * zoom && posy < imgHeight / 2 + 50 * zoom)
    {
        return 1;
    }
    if (posx > 2 * imgWidth / 3 && posx < 2 * imgWidth / 3 + 100 * zoom && posy > imgHeight / 2 - 50 * zoom && posy < imgHeight / 2 + 50 * zoom)
    {
        return 2;
    }
    else{
        return 0;
    }
        
    
}

void ImageViewer::dessineCercle(int couleur, int x, int y) const
{
    filledCircleRGBA(renderer, x, y, 22 * zoom, 0, 0, 0, 255);
    filledCircleRGBA(renderer, x, y, 19 * zoom, 255, 255, 255, 255);
    float rayon = 15 * zoom;
    switch (couleur)
    {
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

void ImageViewer::dessineTriangle(int couleur, int x, int y) const
{
    float grandRayon = 20 * zoom;
    float moyenRayon = 15 * zoom;
    float petitRayon = 10 * zoom;
    filledTrigonRGBA(renderer, x, y - grandRayon, x + grandRayon, y + grandRayon, x - grandRayon, y + grandRayon, 0, 0,
                     0, 255);
    filledTrigonRGBA(renderer, x, y - moyenRayon, x + moyenRayon, y + moyenRayon, x - moyenRayon, y + moyenRayon, 255,
                     255, 255, 255);
    switch (couleur)
    {
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

void ImageViewer::debugCoordonnees() const
{
    for (int i = 0; i < 16 * nbJ; i++)
    {
        dessineCercle(1, coordonnees[i][0] * zoom, coordonnees[i][1] * zoom);
    }
    for (int i = 0; i < 4 * nbJ; i++)
    {
        dessineTriangle(i / 4 + 1, coordonneesMaison[i][0] * zoom, coordonneesMaison[i][1] * zoom);
    }
    for (int i = 0; i < 4 * nbJ; i++)
    {
        dessineCercle(i / 4 + 1, coordonneesReserve[i][0] * zoom, coordonneesReserve[i][1] * zoom);
    }
}

void ImageViewer::afficherPions() const
{
    for (int i = 1; i < 4 * nbJ + 1; i++)
    {
        Pion pion = jeu->getPion(i);
        int indice = pion.getPos();
        if (indice >= 0)
        {
            if (pion.estPieu())
            {
                dessineTriangle((i - 1) / 4 + 1, coordonnees[indice][0] * zoom, coordonnees[indice][1] * zoom);
            }
            else
            {
                dessineCercle((i - 1) / 4 + 1, coordonnees[indice][0] * zoom, coordonnees[indice][1] * zoom);
            }
        }
    }
}

void ImageViewer::afficherReserve() const
{
    for (int i = 0; i < nbJ; i++)
    {
        int reserve = jeu->getJoueur(i).getReserve();
        for (int j = 0; j < reserve; j++)
        {
            dessineCercle(i + 1, coordonneesReserve[i * 4 + j][0] * zoom, coordonneesReserve[i * 4 + j][1] * zoom);
        }
    }
}

void ImageViewer::afficherMaison() const
{
    for (int i = 0; i < nbJ; i++)
    {
        const int *maison = jeu->getJoueur(i).getMaison();
        for (int j = 0; j < 4; j++)
        {
            if (maison[j] != 0)
            {
                dessineTriangle(i+1, coordonneesMaison[i][0] * zoom, coordonneesMaison[i][1] * zoom);
            }
        }
    }
}

void ImageViewer::setTextureCartes(int id_joueur)
{
    Carte *carte = nullptr;
    for (int i = 0; i < 4; i++)
    {
        if (id_joueur >= 0)
            carte = jeu->getJoueur(id_joueur).getCarte(i);
        if (carte == nullptr)
        {
            textureCartes[i] = listTexture[0];
            if (textureCartes[i] == nullptr)
            {
                std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                return;
            }
        }
        else
        {
            int valeur = carte->getValeur();
            if (valeur != -1)
            {
                textureCartes[i] = listTexture[abs(valeur)];
                if (textureCartes[i] == nullptr)
                {
                    std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                    return;
                }
            }
            else
            {
                textureCartes[i] = listTexture[14];
                if (textureCartes[i] == nullptr)
                {
                    std::cerr << "Erreur de chargement de l'image : " << IMG_GetError() << std::endl;
                    return;
                }
            }
        }
    }
}

void ImageViewer::grossissement(bool positif)
{
    zoom += (positif) ? 0.05 : -0.05;
    imgWidth = dimx * zoom;
    imgHeight = dimy * zoom;
    SDL_SetWindowSize(window, imgWidth + 200 * zoom, imgHeight + 100 * zoom);
    for (int i = 0; i < 4; i++)
    {
        RectMain[i] = {imgWidth, (int)(i * imgHeight / 4), (int)(200 * zoom), (int)(imgHeight / 4)};
    }
    RectTas = {
        (int)(imgWidth / 2 - 100 * zoom), (int)(imgHeight / 2 - 150 * zoom), (int)(200 * zoom),
        (int)(300 * zoom)};
}

void ImageViewer::setTextSurface(string message, int couleur)
{
    SDL_Color TextColor;
    if (couleur == 5)
    {
        TextColor = {255, 255, 255};
    }
    else
    {
        TextColor = {0, 0, 0};
    }
    const char *msg = message.c_str();
    textSurface = TTF_RenderUTF8_Blended(m_font, msg, TextColor);
    if (textSurface)
    {
        SDL_Rect txtRect = {0, imgHeight, (int)((dimy + 200) * zoom), (int)(100 * zoom)};
        SDL_Texture *TextTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (TextTexture)
        {
            SDL_RenderCopy(renderer, TextTexture, NULL, &txtRect);
            SDL_DestroyTexture(TextTexture);
        }
        SDL_FreeSurface(textSurface);
    }
}

void ImageViewer::setCouleur(int couleur)
{
    switch (couleur)
    {
    case 1:
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        break;
    case 2:
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        break;
    case 3:
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        break;
    case 4:
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        break;
    case 5:
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        break;
    case 6:
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        break;
    }
}

void ImageViewer::afficherBoutons(int choix)
{
    SDL_Rect rect1 = {(int)(imgWidth / 4), (int)(imgHeight / 2 - 50 * zoom), (int)(100 * zoom), (int)(100 * zoom)};
    SDL_Rect rect2 = {(int)(2 * imgWidth / 3),(int)(imgHeight / 2 - 50 * zoom), (int)(100 * zoom), (int)(100 * zoom)};
    roundedBoxRGBA(renderer, imgWidth / 4, imgHeight / 2 - 50 * zoom, imgWidth / 4 + 100 * zoom, imgHeight / 2 + 50 * zoom, 5, 150, 60, 250, 180);
    roundedBoxRGBA(renderer, 2 * imgWidth / 3, imgHeight / 2 - 50 * zoom, 2 * imgWidth / 3 + 100 * zoom, imgHeight / 2 + 50 * zoom, 5, 150, 60, 250, 180);
    SDL_Surface *surface1 = nullptr;
    SDL_Surface *surface2 = nullptr;
    if (choix == 0)
    {
        surface1 = TTF_RenderUTF8_Blended(m_font, "4", {0, 0, 0});
        surface2 = TTF_RenderUTF8_Blended(m_font, "6", {0, 0, 0});
    }
    if (choix == 1)
    {
        surface1 = TTF_RenderUTF8_Blended(m_font, "A", {0, 0, 0});
        surface2 = TTF_RenderUTF8_Blended(m_font, "D", {0, 0, 0});
    }
    if (choix == 2)
    {
        surface1 = TTF_RenderUTF8_Blended(m_font, "O", {0, 0, 0});
        surface2 = TTF_RenderUTF8_Blended(m_font, "N", {0, 0, 0});
    }
    if (surface1 && surface2)
    {
        SDL_Texture *texture1 = SDL_CreateTextureFromSurface(renderer, surface1);
        SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, surface2);

        SDL_RenderCopy(renderer, texture1, NULL, &rect1);
        SDL_RenderCopy(renderer, texture2, NULL, &rect2);

        SDL_RenderPresent(renderer);
        SDL_Delay(100);
        // Libérer les textures
        SDL_DestroyTexture(texture1);
        SDL_DestroyTexture(texture2);
    }

    SDL_FreeSurface(surface1);
    SDL_FreeSurface(surface2);
}

void ImageViewer::afficherJoker(SDL_Rect tab[13])
{
    int cardWidth;
    int cardHeight;
    int paddingX;
    int paddingY;

    if (nbJ==4){
        cardWidth = imgWidth / 6; // Largeur de chaque carte (5 cartes + espacement)
        cardHeight = imgHeight / 4; // Hauteur de chaque carte (3 lignes + espacement)
        paddingX = (imgWidth - 5 * cardWidth) / 6; // Espacement horizontal entre les cartes
        paddingY = (imgHeight - 3 * cardHeight) / 4; // Espacement vertical entre les lignes
    }
    else{
        cardWidth = imgWidth / 9; // Largeur de chaque carte (5 cartes + espacement)
        cardHeight = imgHeight / 4; // Hauteur de chaque carte (3 lignes + espacement)
        paddingX = (imgWidth - 5 * cardWidth) / 6; // Espacement horizontal entre les cartes
        paddingY = (imgHeight - 3 * cardHeight) / 4; // Espacement vertical entre les lignes
    }
    
    for (int i = 0; i < 13; i++) {
        int row = i / 5; // Ligne actuelle
        int col = i % 5; // Colonne actuelle

        // Ajuster pour la troisième ligne qui ne contient que 3 cartes
        if (row == 2) {
            col += 1; // Centrer les 3 cartes
        }

        tab[i] = {paddingX + col * (cardWidth + paddingX), paddingY + row * (cardHeight + paddingY), cardWidth, cardHeight};
        SDL_RenderCopy(renderer, listTexture[i+1], NULL, &tab[i]);
    }
}

int ImageViewer::selectionnerValJoker(int joueurActif, string message){
    SDL_Rect tab[13];

    SDL_Event event;
    while (true)
    {
        afficher(joueurActif, message);
        afficherJoker(tab);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                for (int i = 0; i < 13; i++) {
                    if (event.button.x >= tab[i].x && event.button.x <= tab[i].x + tab[i].w &&
                        event.button.y >= tab[i].y && event.button.y <= tab[i].y + tab[i].h) {
                        return i;
                    }
                }
                return -1; // Retourne -1 si aucune carte n'a été cliquée
            }
        }
    }
}

int ImageViewer::afficherMenu(string message){
    texturePlateau = IMG_LoadTexture(renderer, "./data/plateau/plateau6.png");
    SDL_Rect Rect = {0, 0, imgWidth+200*zoom, imgHeight};
    SDL_Event event;
    while (true){
        SDL_RenderCopy(renderer, texturePlateau, NULL, &Rect);
        afficherBoutons(0);
        setTextSurface(message, 5);
        SDL_RenderPresent(renderer);
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return 0;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.x > imgWidth / 4 && event.button.x < imgWidth / 4 + 100 * zoom && event.button.y > imgHeight / 2 - 50 * zoom && event.button.y < imgHeight / 2 + 50 * zoom)
                {
                    cout << 4 << endl;
                    return 4;
                }
                if (event.button.x > 2 * imgWidth / 3 && event.button.x < 2 * imgWidth / 3 + 100 * zoom && event.button.y > imgHeight / 2 - 50 * zoom && event.button.y < imgHeight / 2 + 50 * zoom)
                {
                    cout << 6 << endl;
                    return 6;
                }
            }
        }
    }
}

void ImageViewer::afficher(int joueurActif, string message)
{
    setCouleur(joueurActif + 1);
    SDL_RenderClear(renderer);
    SDL_Rect Rect = {0, 0, imgWidth, imgHeight};
    SDL_RenderCopy(renderer, texturePlateau, NULL, &Rect);
    afficherPions();
    afficherMaison();
    afficherReserve();
    SDL_RenderCopy(renderer, textureTas, NULL, &RectTas);
    SDL_RenderCopy(renderer, textureCartes[0], NULL, &RectMain[0]);
    SDL_RenderCopy(renderer, textureCartes[1], NULL, &RectMain[1]);
    SDL_RenderCopy(renderer, textureCartes[2], NULL, &RectMain[2]);
    SDL_RenderCopy(renderer, textureCartes[3], NULL, &RectMain[3]);
    setTextSurface(message, joueurActif + 1);
    
    SDL_RenderPresent(renderer);
}
