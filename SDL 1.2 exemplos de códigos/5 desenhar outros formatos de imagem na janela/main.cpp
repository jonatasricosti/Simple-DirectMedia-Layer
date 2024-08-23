#include <SDL.h>
#include <SDL_image.h>

/*
por padrão o SDL só carrega imagens bmp,
mas com o SDL_image.h podemos carregar outros formatos de imagens
*/

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

SDL_Surface *Image = NULL;

// carrega arquivos
void LoadFiles()
{
    Image = IMG_Load("wallpaper.jpg");
}

// fecha arquivos
void CloseFiles()
{
    SDL_FreeSurface(Image);
}

int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);

tela = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,SCREEN_BPP,SDL_SWSURFACE);
SDL_WM_SetCaption("Minha janela",NULL);

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

    // desenha a imagem na tela na posição x = 0, y = 0
    // pois o último parâmetro é NULL
	SDL_BlitSurface(Image,NULL,tela,NULL);
    SDL_Flip(tela);
}


CloseFiles();
SDL_Quit();
return 0;
}
