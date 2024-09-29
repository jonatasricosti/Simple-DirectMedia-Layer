#include <SDL.h>
#include <SDL_ttf.h>


const int screen_width = 640;
const int screen_height = 480;
const int screen_bpp = 32;
SDL_Surface *tela = NULL;
SDL_Event evento;

// use essa função pra desenhar uma imagem na tela
void DrawImage(int x, int y, SDL_Surface *source, SDL_Surface *destination)
{
    SDL_Rect mover;
    mover.x = x;
    mover.y = y;

    SDL_BlitSurface(source,NULL,destination,&mover);
}


TTF_Font *times = NULL;
SDL_Surface *FontImage = NULL;


// carrega arquivos
void LoadFiles()
{
    times = TTF_OpenFont("times.ttf",40); // abri o arquivo de fonte
}

// fecha arquivos
void CloseFiles()
{
    TTF_CloseFont(times); // fecha o arquivo de fonte
    SDL_FreeSurface(FontImage);
}

// use essa função pra desenhar texto na tela usando fonte ttf
void DrawText(int x, int y, char *text, Uint8 red, Uint8 green, Uint8 blue, TTF_Font *font)
{
    SDL_Surface *buffer = NULL;
    SDL_Color color = {red, green, blue};

    buffer = TTF_RenderText_Solid(font, text, color);

    SDL_Rect mover;
    mover.x = x;
    mover.y = y;

    SDL_BlitSurface(buffer, NULL, tela, &mover);
    SDL_FreeSurface(buffer);
}

// use essa função pra desenhar um texto no centro da tela usando fonte ttf
void DrawTextCenter(int x, int y, char *text, Uint8 red, Uint8 green, Uint8 blue, TTF_Font *font)
{
    SDL_Surface *buffer = NULL;
    SDL_Color color = {red, green, blue};

    buffer = TTF_RenderText_Solid(font, text, color);

    SDL_Rect mover;
    mover.x = x+(screen_width - buffer->w)/2;
    mover.y = y+(screen_height - buffer->h)/2;

    SDL_BlitSurface(buffer, NULL, tela, &mover);
    SDL_FreeSurface(buffer);
}


int main(int argc, char*args[])
{
SDL_Init(SDL_INIT_EVERYTHING);
SDL_putenv("SDL_VIDEO_WINDOW_POS=center"); // centraliza a janela ao abrir o programa
tela = SDL_SetVideoMode(screen_width,screen_height,screen_bpp,SDL_SWSURFACE);

TTF_Init(); // inicia o ttf

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

    DrawText(0,0,"Sou um texto na posição x = 0 y  = 0", 255,255,255, times);
    DrawTextCenter(0,0,"Sou um texto no centro da tela", 0,255,0,times);

    SDL_Flip(tela);
}


CloseFiles();
TTF_Quit(); // encerra o ttf
SDL_Quit();
return 0;
}

