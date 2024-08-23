#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

// use essa função pra carregar uma imagem bmp e deixa o fundo transparente
SDL_Surface *fundo_transparente(const char*filename, const Uint8 red, const Uint8 green, const Uint8 blue)
{
    SDL_Surface *load = NULL;
    SDL_Surface *otimizado = NULL;

    load = SDL_LoadBMP(filename);

    if(load != NULL)
    {
        otimizado = SDL_DisplayFormat(load);
        SDL_FreeSurface(load);

        if(otimizado != NULL)
        {
            SDL_SetColorKey(otimizado,SDL_SRCCOLORKEY,SDL_MapRGB(otimizado->format,red,green,blue));
        }
    }

    return otimizado;
}


// use essa função pra desenhar uma imagem na tela
void DrawImage(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    // posição x,y da imagem
    SDL_Rect mover;
    mover.x = x;
    mover.y = y;

    SDL_BlitSurface(source,NULL,destination,&mover);
}


SDL_Surface *StarImage = NULL;

// carrega arquivos
void LoadFiles()
{
    StarImage = fundo_transparente("star.bmp",0,255,255);
}

// fecha arquivos
void CloseFiles()
{
    SDL_FreeSurface(StarImage);
}

int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);

tela = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);

LoadFiles();

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


    DrawImage(0,0,StarImage,tela);
    SDL_Flip(tela);
}


CloseFiles();
SDL_Quit();
return 0;
}
