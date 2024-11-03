/*
Nesse tutorial, vamos aprender a como rotacionar uma imagem
o SDL 1.2 não tem uma função pra rotacionar uma imagem por isso temos que criar uma do zero.
ou você pode usar a lib SDL_gfx.h pra isso e é isso que vamos fazer
já o SDL 2 tem
*/

#include <SDL.h>
#include "SDL_gfx-2.0.23/SDL_rotozoom.c"

SDL_Surface *tela = NULL;
SDL_Event evento;

// para o framerate
Uint32 start = 0;
const int fps = 60;
const int framerate = 1000/fps;

// tamanho da janela
const int screen_width = 640;
const int screen_height = 480;
const int screen_bpp = 32; // bits por pixel

bool executando = true; // true tela aberta , false tela fechada

// use essa função pra carregar imagem bmp e deixa o fundo transparente
SDL_Surface *fundo_transparente(const char*filename, Uint32 red, Uint32 green, Uint32 blue)
{
    SDL_Surface *otimizado = NULL;
    SDL_Surface *load = NULL;

    load = SDL_LoadBMP(filename);

    if(load != NULL)
    {
        otimizado = SDL_DisplayFormat(load);
        SDL_FreeSurface(load);

        if(otimizado != NULL)
        {
            SDL_SetColorKey(otimizado, SDL_SRCCOLORKEY, SDL_MapRGB(otimizado->format, red, green, blue));
        }
    }

    return otimizado;
}


SDL_Surface *setaImage = NULL;

// use essa função pra carregar arquivos
void LoadFiles()
{
    setaImage = fundo_transparente("seta.bmp",0,255,255);
}


// use essa função pra fechar arquivo
void CloseFiles()
{
    SDL_FreeSurface(setaImage);
}

// use essa função pra desenhar uma imagem inteira na tela
void DrawImage(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect mover;
    mover.x = x;
    mover.y = y;

    SDL_BlitSurface(source,NULL,tela, &mover);
}


int main(int argc, char*args[])
{

SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
tela = SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);
LoadFiles();

int angle = 0;

SDL_Surface *rotateImage = rotozoomSurface(setaImage, angle, 1.0, 0);

while(executando)
{
    start = SDL_GetTicks();
    while(SDL_PollEvent(&evento))
    {
        if(evento.type == SDL_QUIT)
        {
            executando = false;
        }
    }

    SDL_FillRect(tela,0,0xffffff);

    angle--;

    if(angle <= 0)
    {
        angle = 360;
    }

    SDL_Surface *rotateImage = rotozoomSurface(setaImage, angle, 1.0, 0);

    DrawImage((screen_width - rotateImage->w)/2,(screen_height - rotateImage->h)/2,rotateImage,tela);

    SDL_Flip(tela); // atualiza a tela

    // calculo de framerate
    if(framerate > (SDL_GetTicks()-start))
    {
        SDL_Delay(framerate-(SDL_GetTicks()-start));
    }
}


CloseFiles();
SDL_Quit();
return 0;
}
