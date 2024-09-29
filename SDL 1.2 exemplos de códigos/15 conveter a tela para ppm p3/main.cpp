#include <SDL.h>
#include <fstream>
#include <sstream>
using namespace std; // pra não escrever std::

/*
nesse programa, vamos extrair todos os pixels da tela
e salvar em uma imagem ppm p3
*/

const int screen_width = 640;
const int screen_height = 480;
const int screen_bpp = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

// use essa função pra conveter uma cor em rgb24 de hexadecimal pra decimal
string rgb24Todecimal(int color)
{
	int red = color >> 16 & 255;
	int green = color >> 8 & 255;
	int blue = color & 255;

	stringstream escreva;
	escreva << red << " " << green << " " << blue << endl;
	string texto = escreva.str();

	return texto;
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

// objeto ponteiro da struct SDL_Surface
SDL_Surface *StarImage = NULL;

// carrega arquivos
void LoadFiles()
{
   StarImage = SDL_LoadBMP("star.bmp");
}

// fecha arquivos
void CloseFiles()
{
    SDL_FreeSurface(StarImage);
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


int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
tela = SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);

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
    SDL_Flip(tela); // atualiza a tela
}

ofstream escreva;
escreva.open("imagem.ppm");


escreva << "P3" << endl;
escreva << screen_width << endl;
escreva << screen_height << endl;
escreva << 255 << endl;


const int n_elementos = screen_width*screen_height;

int *image = (int *)  malloc(n_elementos * sizeof(int));


// salve todas as cores no array image
for(int y = 0; y < screen_height; y++)
{
    for(int x = 0; x < screen_width; x++)
    {
        image[x+y*screen_width] = get_pixel32(tela,x,y);
    }
}


// converte todas as cores em decimal que está no array image
for(int i = 0; i < screen_width*screen_height; i++)
{
    escreva << rgb24Todecimal(image[i]);
}

escreva.close();

/*
esse programa vai gerar um arquivo chamado imagem.ppm
nota: você pode abrir o arquivo imagem.ppm com o Gimp ou Irfanview
*/


free(image);
CloseFiles();
SDL_Quit();
return 0;
}

