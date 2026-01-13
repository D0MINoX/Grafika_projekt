// funkcje do operacji na plikach
#ifndef GK2025_PLIKI_H_INCLUDED
#define GK2025_PLIKI_H_INCLUDED

#include <stdio.h>
#include <math.h>
#include <fstream>
#include "SDL.h"

void zapiszPlik5(char identyfikator,const char* path);
void odczytajPlik5(char const* path);
void odczytajPlik(char const* path);
void opt_zapiszPlik5(const char* path);
void opt_odczytajPlik5(char const* path);
#endif // GK2025_PLIKI_H_INCLUDED
