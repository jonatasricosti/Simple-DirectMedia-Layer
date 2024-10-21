#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

/*
O framerate serve para o jogo ter o mesmo tempo de execução em qualquer computador
Se você não programar o framerate, o jogo vai ser executado na maior velocidade
possível em outros computadores. Isso deixa o jogo injogável.
*/

// variáveis para o framerate
Uint32 start = 0;
const int fps = 30; // fps = frames per second/frames por segundo
const int framerate = 1000/fps;

int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
tela = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);


bool executando = true;
// nosso game loop
while(executando)
{
    start = SDL_GetTicks();
    while(SDL_PollEvent(&evento))
    {
        // clicou no x da janela
        if(evento.type == SDL_QUIT)
        {
            // sai do game loop
            executando = false;
        }
    }

    // atualiza a tela
	SDL_Flip(tela);

    //(SDL_GetTicks() - start) <  framerate = 1000/fps
	if(framerate > (SDL_GetTicks()-start))
    {
        SDL_Delay(framerate-(SDL_GetTicks()-start));
    }
}

SDL_Quit();
return 0;
}
