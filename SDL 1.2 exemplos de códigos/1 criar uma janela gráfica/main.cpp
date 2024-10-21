#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);

tela = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
SDL_WM_SetCaption("Minha janela",NULL);

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
    
    // atualiza a tela
	SDL_Flip(tela);
}

SDL_Quit();
return 0;
}

