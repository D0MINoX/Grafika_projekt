#include "GK2025-WrapperAPI.h"
#include "GK2025-Funkcje.h"   // jeœli potrzebujesz swoich funkcji
#include <SDL.h>
#include "GK2025-Zmienne.h"
#include <cstdlib>
#include "GK2025-Paleta.h"




void RunSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    window = SDL_CreateWindow(
        tytul,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        szerokosc * 2,
        wysokosc * 2,
        SDL_WINDOW_SHOWN
    );

    if (window == NULL) {
        printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
        return;
    }

    screen = SDL_GetWindowSurface(window);
    if (screen == NULL) {
        fprintf(stderr, "SDL_GetWindowSurface Error: %s\n", SDL_GetError());
        return;
    }

    SDL_UpdateWindowSurface(window);

    bool done = false;
    SDL_Event event;

    // Minimalna pêtla zdarzeñ – tylko zamykanie okna
    while (!done)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                done = true;
        }

        // GUI bêdzie wywo³ywaæ funkcje rysuj¹ce, wiêc tu nic nie robimy
        SDL_UpdateWindowSurface(window);
    }

    if (screen)
        SDL_FreeSurface(screen);

    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();

}
void laduj_BMP(const char* nazwa,int x,int y) {
	ladujBMP(nazwa, x, y);
}

void paletanarzuconaAPI()
{
	paletaNarzucona();
}

void paletaNarzuconaSzaraAPI()
{
    paletaNarzuconaSzary();
}

void bayerDitheringAPI()
{
	dithering_bayer_color();
}

void bayerDitheringSzaryAPI()
{
    dithering_bayer();
}
