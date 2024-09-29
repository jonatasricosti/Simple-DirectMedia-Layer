#include <SDL.h>

const int screen_width = 640;
const int screen_height = 480;
const int screen_bpp = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

// use essa função pra desenhar um pixel na tela
void DrawPixel( SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	// Converta os pixels para 32 bits
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Defina o pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}


// use essa função pra desenhar pixel na tela
void DrawPixel(SDL_Surface *surface, int x, int y, Uint8 r, Uint8 g, Uint8 b)
{
    if(SDL_MUSTLOCK(surface))
    {
        if(SDL_LockSurface(surface) < 0)
            return;
    }

    // se passou do lado direito, esquerdo, de cima, de baixo
    if(x >= surface->w || x < 0 || y >= surface->h || y < 0)
        return;

    Uint32 *buffer = NULL;
    Uint32 color = SDL_MapRGB(surface->format,r,g,b);


    buffer = (Uint32*)surface->pixels + y*surface->pitch /4 + x;
    (*buffer) = color;

    if(SDL_MUSTLOCK(surface))
        SDL_UnlockSurface(surface);
}


int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
tela = SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);


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


     // desenhe pixels
     for(int i = 0; i < 100; i++)
    {
        DrawPixel(tela, rand()%800, rand()%600, rand()%256, rand()%256, rand()%256);
    }


    SDL_Flip(tela); // atualiza a tela
}


SDL_Quit();
return 0;
}

