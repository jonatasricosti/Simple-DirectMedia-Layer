#include <SDL.h>
#include <sstream>
#include <fstream>
using namespace std; // pra não escrever std::

const int screen_width = 640;
const int screen_height = 480;
const int screen_bpp = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;


// use essa função pra remover comentários de uma imagem ppm p3
void Remove_PPM_P3_Comments(string filename, string newfilename)
{
    ifstream arquivoEntrada(filename.c_str());
    ofstream arquivoSaida(newfilename.c_str());

    string linha;

    while (getline(arquivoEntrada, linha))
    {
        if (linha[0] != '#')
        {
            arquivoSaida << linha << endl;
        }
    }

    arquivoEntrada.close();
    arquivoSaida.close();
}


// use essa função pra pegar três canais de cores red green blue e transformar em uma cor
int RGB24(int red, int green, int blue)
{
    return ((red & 255) << 16) + ((green & 255) << 8) + (blue & 255);
}


// use essa função pra mudar um pixel de uma SDL_Surface
void change_pixel(SDL_Surface *surface, int x, int y, Uint32 color)
{
    SDL_Rect quadro;
    quadro.x = x;
    quadro.y = y;
    quadro.w = 1; // tamanho de um pixel
    quadro.h = 1; // tamanho de um pixel

    SDL_FillRect(surface, &quadro, color);
}

/*
use essa função pra carregar uma imagem ppm p3
nota: se tiver comentários no arquivo essa função não vai funcionar direito
por isso use a função Remove_PPM_P3_Comments antes
pra remover todos os comentário do arquivo
*/
SDL_Surface* LoadPPM_P3(string filename)
{
    string type;
	int image_width;
	int image_height;
	int magic_number;
	int red;
	int green;
	int blue;


	ifstream file;
	file.open(filename.c_str());

	file >> type;
	file >> image_width;
	file >> image_height;
	file >> magic_number;


	Uint32 *vram = (Uint32 *) malloc(image_width*image_height * sizeof(Uint32));


	SDL_Surface *NewImage = NULL;

	Uint32 Rmask = 0x00FF0000;  // Red mask
    Uint32 Gmask = 0x0000FF00;  // Green mask
    Uint32 Bmask = 0x000000FF;  // Blue mask
    Uint32 Amask = 0;           // Alpha mask
	NewImage = SDL_CreateRGBSurface(SDL_SWSURFACE, image_width, image_height, 32, Rmask, Gmask, Bmask, Amask);


	// pegue todas as cores em rgb e transforme em cores decimais
	for(int i = 0; i < image_width*image_height; i++)
	{
		file >> red;
		file >> green;
		file >> blue;

		vram[i] = RGB24(red,green,blue);
	}

	// coloca todos os pixels na surface NewImage
	for(int y = 0; y < image_height; y++)
    {
        for(int x = 0; x < image_width; x++)
        {
            // ao invés de desenhar pixel na tela
            // vamos colocar pixel na nossa surface
            change_pixel(NewImage, x,y, vram[x+y*image_width]);
        }
    }


    file.close();
    free(vram);
    return NewImage;
}



// objeto ponteiro da struct SDL_Surface
SDL_Surface *mxImage = NULL;

// carrega arquivos
void LoadFiles()
{
    Remove_PPM_P3_Comments("mx.ppm", "megamanx.ppm");
    mxImage = LoadPPM_P3("megamanx.ppm");
}

// fecha arquivos
void CloseFiles()
{
    SDL_FreeSurface(mxImage);
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
    
    DrawImage(0,0,mxImage,tela);
    
    SDL_Flip(tela); // atualiza a tela
}


CloseFiles();
SDL_Quit();
return 0;
}

