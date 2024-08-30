#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

// use essa função pra carregar uma imagem bmp e deixa o fundo transparente
SDL_Surface *fundo_transparente(const char*filename, const Uint8 red, const Uint8 green, const Uint8 blue)
{
    SDL_Surface *load = NULL;
    SDL_Surface *otimizado = NULL;

    load = SDL_LoadBMP(filename);

    if(load != NULL)
    {
        otimizado = SDL_DisplayFormat(load);
        SDL_FreeSurface(load);

        if(otimizado != NULL)
        {
            SDL_SetColorKey(otimizado,SDL_SRCCOLORKEY,SDL_MapRGB(otimizado->format,red,green,blue));
        }
    }

    return otimizado;
}


SDL_Surface *whitefontImage = NULL;
SDL_Surface *yellowfontImage = NULL;
SDL_Surface *bluefontImage = NULL;

// carrega arquivos
void LoadFiles()
{
    whitefontImage = fundo_transparente("fontes/whitefont.bmp", 255,0,255);
    yellowfontImage = fundo_transparente("fontes/yellowfont.bmp", 255,0,255);
    bluefontImage = fundo_transparente("fontes/bluefont.bmp", 255,0,255);
}

// fecha arquivos
void CloseFiles()
{
    SDL_FreeSurface(whitefontImage);
    SDL_FreeSurface(yellowfontImage);
    SDL_FreeSurface(bluefontImage);
}

// use essa função pra desenhar uma imagem cortada na tela
void DrawImageFrame(int x, int y, SDL_Surface *source, SDL_Surface *destination, int width, int height, int frame)
{
    SDL_Rect mover;
    mover.x = x;
    mover.y = y;

    int coluna = source->w / width;

    SDL_Rect corte;
    corte.x = (frame % coluna)*width;
    corte.y = (frame / coluna)*height;
    corte.w = width;
    corte.h = height;


    SDL_BlitSurface(source, &corte, destination, &mover);
}

// use essa função pra desenhar texto na tela
void DrawText(int x, int y, SDL_Surface *source, SDL_Surface *destination, char texto[], int charSize, int start)
{
	for(unsigned int i = 0; i < strlen(texto); i++)
    {
        DrawImageFrame(x+i*charSize, y, source, destination, charSize, charSize, texto[i]-start);
    }
}


// use essa função pra desenhar texto na tela com quebra de linnha
// essa função pula linha se usar o caractere /n
void DrawText2(int x, int y, SDL_Surface *source, SDL_Surface *destination, char texto[], int charSize, int start)
{
    int coluna = 0;
    int linha = 0;

	for(unsigned int i = 0; i < strlen(texto); i++)
    {
        if(texto[i] == '\n')
        {
            linha = linha + charSize; // mova pra baixo cada nova linha
            coluna = 0; // coluna volta para o começo
            continue; //Pule o resto do loop para a nova linha
        }

        DrawImageFrame(x+coluna*charSize, y+linha, source, destination, charSize, charSize, texto[i]-start);

         // Move para a próxima coluna
        coluna++;
    }
}

int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
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
    SDL_FillRect(tela,NULL,0); // limpa a tela na cor preta

    char texto[] = "gosto de programar\ngosto de programar\ngosto de programar\ngosto de programar\n";


    DrawText2(60,80,whitefontImage,tela,texto,16,32);
    SDL_Flip(tela);
}


CloseFiles();
SDL_Quit();
return 0;
}
