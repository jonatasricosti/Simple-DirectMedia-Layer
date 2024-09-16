#include <SDL.h>
#include <SDL_ttf.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

// use essa função pra desenhar uma imagem na tela
void DrawImage(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect mover;
    mover.x = x;
    mover.y = y;

    SDL_BlitSurface(source,NULL,destination,&mover);
}


TTF_Font *times = NULL;
SDL_Surface *FontImage = NULL;


// carrega arquivos
void LoadFiles()
{
    times = TTF_OpenFont("times.ttf",50); // abri o arquivo de fonte
}

// fecha arquivos
void CloseFiles()
{
    TTF_CloseFont(times); // fecha o arquivo de fonte
    SDL_FreeSurface(FontImage);
}


int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
tela = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

TTF_Init(); // inicia o ttf

LoadFiles();

SDL_Color whitecolor = {255,255,255};
SDL_Color yellowcolor = {255,255,0};
SDL_Color greencolor = {0,255,0};

bool executando = true;
// nosso game loop
while(executando)
{
    while(SDL_PollEvent(&evento))
    {
        // clicou no x da janela
        if(evento.type == SDL_QUIT)
        {
            // sai do game loop
            executando = false;
        }
    }


    FontImage = TTF_RenderText_Solid(times,"Texto com font ttf.",whitecolor);
    DrawImage(50,70,FontImage,tela);

    FontImage = TTF_RenderText_Solid(times,"É muito legal escrever.",yellowcolor);
    DrawImage(50,140,FontImage,tela);

    FontImage = TTF_RenderText_Solid(times,"Código feito em c++.",greencolor);
    DrawImage(50,210,FontImage,tela);

    SDL_Flip(tela);
}


CloseFiles();
TTF_Quit(); // encerra o ttf
SDL_Quit();
return 0;
}
