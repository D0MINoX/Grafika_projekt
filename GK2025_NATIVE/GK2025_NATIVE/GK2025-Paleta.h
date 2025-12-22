// funkcje do redukcji kolorów i tworzenia palet
#ifndef GK2025_PALETA_H_INCLUDED
#define GK2025_PALETA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "SDL.h"
#include <iostream>
#include <cmath>
using namespace std;

void narzuconaV1();
void narzuconaV2();
void narzuconaV3();
void paletaNarzucona();
void paletaNarzuconaSzary();
void narysujPalete(int px,int py,SDL_Color pal5[]);
void dithering_bayer();
void dithering_bayer_color();
void czyscPalete();
Uint8 znajdzNajblizszyKolor(SDL_Color kolor, SDL_Color paleta[32]);
int dodajKolor(SDL_Color kolor);
void paletaWykryta();
Uint8 szary5bit(SDL_Color kolor);
SDL_Color z5bitSzary(Uint8 kolor5bit);
Uint8 z24Kdo5K(SDL_Color kolor);
SDL_Color z5Kdo24K(Uint8 kolor5bit);
#endif // GK2025_PALETA_H_INCLUDED
