/*
Nesse tutorial, vou ensinar a como inverter uma imagem
na horizontal e na vertical com código
o SDL 1.2 não tem uma função pra inverter imagem por isso temos que criar uma do zero
já o SDL 2 tem
*/

#include <SDL.h>

SDL_Surface *tela = NULL;
SDL_Event evento;

// para o framerate
Uint32 start = 0;
const int fps = 30;
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


// use essa função pra extrair um pixel da surface
// essa função pega a posição x,y do pixel e returna o número da cor
Uint32 get_pixel32( SDL_Surface *surface, int x, int y )
{
    //Converta os pixels para 32 bits
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //pegue o pixel solicitado
    return pixels[ ( y * surface->w ) + x ];
}


// use essa função pra desenhar um pixel na surface
void DrawPixel( SDL_Surface *surface, int x, int y, Uint32 pixel)
{
	// Converta os pixels para 32 bits
    Uint32 *pixels = (Uint32 *)surface->pixels;

    //Defina o pixel
    pixels[ ( y * surface->w ) + x ] = pixel;
}

// flags
const int FLIP_VERTICAL = 1;
const int FLIP_HORIZONTAL = 2;

// use essa função pra inverter uma surface na horizontal ou na vertical
SDL_Surface *flip_surface( SDL_Surface *surface, int flags )
{
    // Ponteiro para a surface que será invertida em breve
    SDL_Surface *flipped = NULL;

    // Se a imagem tiver código de cores transparentes
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, 0 );
    }
    // caso contrário
    else
    {
        flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surface->w, surface->h, surface->format->BitsPerPixel, surface->format->Rmask, surface->format->Gmask, surface->format->Bmask, surface->format->Amask );
    }

    // Se a surface precisar ser travada
    if( SDL_MUSTLOCK( surface ) )
    {
        // trave a surface
        SDL_LockSurface( surface );
    }

    // Percorra as colunas
    for( int x = 0, rx = flipped->w - 1; x < flipped->w; x++, rx-- )
    {
        // Percorra as linhas
        for( int y = 0, ry = flipped->h - 1; y < flipped->h; y++, ry-- )
        {
            //pegue os pixels
            Uint32 pixel = get_pixel32( surface, x, y );

            // copie os pixels
            if( ( flags & FLIP_VERTICAL ) && ( flags & FLIP_HORIZONTAL ) )
            {
                DrawPixel( flipped, rx, ry, pixel );
            }
            else if( flags & FLIP_HORIZONTAL )
            {
                DrawPixel( flipped, rx, y, pixel );
            }
            else if( flags & FLIP_VERTICAL )
            {
                DrawPixel( flipped, x, ry, pixel );
            }
        }
    }

    //destrave a surface
    if( SDL_MUSTLOCK( surface ) )
    {
        SDL_UnlockSurface( surface );
    }

    // Copiar a cor transparente
    if( surface->flags & SDL_SRCCOLORKEY )
    {
        SDL_SetColorKey( flipped, SDL_RLEACCEL | SDL_SRCCOLORKEY, surface->format->colorkey );
    }

    // retorna a surface invertida
    return flipped;
}


SDL_Surface *topLeft = NULL;
SDL_Surface *topRight = NULL;
SDL_Surface *bottomLeft = NULL;
SDL_Surface *bottomRight = NULL;


// use essa função pra carregar arquivos
void LoadFiles()
{
    topLeft = fundo_transparente("corner.bmp",255,255,255);

    // vire as surfaces
    topRight = flip_surface( topLeft, FLIP_HORIZONTAL );
    bottomLeft = flip_surface( topLeft, FLIP_VERTICAL );
    bottomRight = flip_surface( topLeft, FLIP_HORIZONTAL | FLIP_VERTICAL );
}


// use essa função pra fechar arquivo
void CloseFiles()
{
    SDL_FreeSurface(topLeft);
    SDL_FreeSurface(topRight);
    SDL_FreeSurface(bottomLeft);
    SDL_FreeSurface(bottomRight);
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

    DrawImage( 20, 0, topLeft, tela ); // desenha a imagem pra esquerda
    DrawImage( 150, 0, topRight, tela ); // desenha a imagem pra direita
    DrawImage( 20, 240, bottomLeft, tela ); // desenha a imagem pra baixo e esquerda
    DrawImage( 150, 240, bottomRight, tela ); // desenha a imagem pra baixo e direita

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
