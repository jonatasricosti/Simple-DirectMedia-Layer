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


/*
explicando a função SDL_BlitSurface
o primeiro parâmetro é a imagem carregada com o objeto da struct SDL_Surface
o segundo parâmetro é um objeto da struct SDL_Rect define a posição x,y da imagem
o terceito parâmetro é onde a imagem vai ser desenhada no caso tela
o quarto parâmetro é um objeto da struct SDL_Rect que é um retângulo de corte,
tem a posição x, y, largura e altura
*/


// use essa função pra desenhar uma imagem cortada na tela
void DrawCutImage(int x, int y, int cx, int cy, int width, int height, SDL_Surface *source, SDL_Surface *destination)
{
    // posição x,y da imagem
    SDL_Rect mover;
    mover.x = x;
    mover.y = y;

    SDL_Rect corte;
    corte.x = cx;
    corte.y = cy;
    corte.w = width;
    corte.h = height;

    SDL_BlitSurface(source,&corte,destination,&mover);
}


SDL_Surface *SpritesImage = NULL;

// carrega arquivos
void LoadFiles()
{
    SpritesImage = fundo_transparente("sprites.bmp",255,0,255);
}

// fecha arquivos
void CloseFiles()
{
    SDL_FreeSurface(SpritesImage);
}

int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
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


    DrawCutImage(64,80,0,0,32,32,SpritesImage,tela);
    DrawCutImage(200,300,32,0,32,32,SpritesImage,tela);
    SDL_Flip(tela);
}


CloseFiles();
SDL_Quit();
return 0;
}
