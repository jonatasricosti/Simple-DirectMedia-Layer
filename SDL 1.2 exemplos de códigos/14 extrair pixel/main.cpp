#include <SDL.h>
#include <fstream>
using namespace std; // pra não escrever std::

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


// use essa função pra extrair um pixel da tela
// essa função pega a posição x,y do pixel e returna o número da cor
Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

switch (bpp)
{
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;
            break;

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;       /* shouldn't happen, but avoids warnings */
      }
}


// use essa função pra extrair um pixel da tela
// essa função pega a posição x,y do pixel e returna o número da cor
Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Converta os pixels para 32 bits
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //pegue o pixel solicitado
    return pixels[ ( y * surface->w ) + x ];
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

    DrawPixel(tela, 100,120,0xffff00);   // desenha um pixel amarelo
    DrawPixel(tela,200,300,255,255,255); // desenha um pixel branco

    SDL_Flip(tela); // atualiza a tela
}

ofstream escreva;
escreva.open("pixel.txt");


escreva << "0x" << hex << getpixel(tela, 100,120)  << endl;
escreva << "0x" << hex << get_pixel32(tela, 200,300) << endl;


escreva.close();

/*
nota: abra o arquivo pixel.txt
pra ver o código hexadecimal da cor
pega pela função getpixel
*/

SDL_Quit();
return 0;
}

