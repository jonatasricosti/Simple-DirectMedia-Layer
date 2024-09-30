#include <SDL.h>

const int screen_width = 640;
const int screen_height = 480;
const int screen_bpp = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;


int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
tela = SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);


SDL_Rect quadro; // objeto da struct SDL_Rect
quadro.x = 200;
quadro.y = 100;
quadro.w = 50;
quadro.h = 80;


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

    SDL_FillRect(tela, NULL, 0xffffff); // desenha um retângulo branco do tamanho da tela
    SDL_FillRect(tela, &quadro, 0xff); // desenha um retângulo azul

    SDL_Flip(tela); // atualiza a tela
}


SDL_SaveBMP(tela, "foto.bmp"); // tira fota da tela

SDL_Quit();
return 0;
}

