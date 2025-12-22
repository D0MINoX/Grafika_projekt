// funkcje do redukcji kolorów i tworzenia palet
#include <algorithm>
#include <cmath>
#include "GK2025-Paleta.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Funkcje.h"

/*
    funkcja zmieniająca paletę obrazu na zredukowaną paletę 5 bitową(2,2,1)
    przy użyciu przesunięcia bitowego oraz wyświetlenie obrazu ze zredukowanej palety za pomocą uzupełnienia bitów

*/

void narzuconaV1(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y = 0; y < wysokosc/2; y++){
        for(int x = 0; x < szerokosc/2; x++){
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>6;   // przesunięcie bitowe kolorów odpowiednio o 6,6 i 7 bitów do palety (2,2,1)
            nowyG = G>>6;
            nowyB = B>>7;

            R = nowyR <<6;  //uzupełnienie bitów do 8 w celu poprawnego działania wyświetlania
            G = nowyG <<6;
            B = nowyB <<7;

            setPixel(x+szerokosc/2, y, R, G, B);
        }
    }
}

/*
 funkcja zmieniająca paletę obrazu na zredukowaną paletę 5 bitową(2,2,1)
    przy użyciu przesunięcia bitowego oraz wyświetlenie obrazu ze zredukowanej palety za pomocą aproksymowanej wartości
*/

void narzuconaV2(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y = 0; y < wysokosc/2; y++){
        for(int x = 0; x < szerokosc/2; x++){
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = R>>6; //2 bity dla koloru czerwonego
            nowyG = G>>6; // 2 bity dla koloru zielonego
            nowyB = B>>7; //1 bit dla koloru niebieskiego

            R = nowyR * 255.0/3.0; // 4 dostępne kolory
            G = nowyG * 255.0/3.0; // 4 kolory
            B = nowyB * 255.0/1.0; // to możemy mieć max 2 kolory (0-1)

            setPixel(x, y+wysokosc/2, R, G, B);
        }
    }
}

/*
 funkcja zmieniająca paletę obrazu na zredukowaną paletę 5 bitową(2,2,1)
    przy użyciu aproksymacji wartości  oraz wyświetlenie obrazu ze zredukowanej palety za pomocą aproksymowanej wartości
*/

void narzuconaV3(){
    SDL_Color kolor;
    int R, G, B;
    int kolor8bit;
    int nowyR, nowyG, nowyB;

    for(int y = 0; y < wysokosc/2; y++){
        for(int x = 0; x < szerokosc/2; x++){
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            nowyR = round(R*3.0/255.0); //przybliżenie wartości koloru (0-3)
            nowyG = round(G*3.0/255.0); //przybliżenie wartości koloru (0-3)
            nowyB = round(B*1.0/255.0); //przybliżenie wartości koloru (0-1)

            R = nowyR*255.0/3.0;
            G = nowyG*255.0/3.0;    // przybliżenie obliczonego koloru
            B = nowyB*255.0/1.0;

            setPixel(x+szerokosc/2, y+wysokosc/2, R, G, B);
        }
    }
}
/*
funkcja obliczająca kolor do zredukowanej barwy dla palety(2,2,1)

*/
Uint8 z24Kdo5K(SDL_Color kolor){
    Uint8 kolor5bit;
    int R, G, B;
    int nowyR, nowyG, nowyB;

    R = kolor.r;
    G = kolor.g;
    B = kolor.b;

    nowyR = round(R*3.0/255.0); //(0 - 3)
    nowyG = round(G*3.0/255.0); //(0 - 3)
    nowyB = round(B/255.0); //(0 - 1)

    kolor5bit = (nowyR<<3) | (nowyG<<1) | nowyB;

    return kolor5bit;
}
/*
funkcja obliczająca kolor ze zredukowanej barwy dla palety(2,2,1) do postaci 24 bitowej
*/
SDL_Color z5Kdo24K(Uint8 kolor5bit){
    SDL_Color kolor;
    int R, G, B;
    int nowyR, nowyG, nowyB;

   nowyR = (kolor5bit >> 3) & 0x03; // 2 bity
    nowyG = (kolor5bit >> 1) & 0x03; // 2 bity
    nowyB = kolor5bit & 0x01;        // 1 bit

    R = nowyR*255.0/3.0;
    G = nowyG*255.0/3.0;
    B = nowyB*255.0;



    kolor.b=B;
    kolor.r = R;
    kolor.g = G;

    return kolor;
}
/*
funkcja obliczająca zredukowane odcienie szarości do 5 bitów z pełnej palety 24 bitowej oraz zwracająca wartość zredukowanej palety
*/

Uint8 szary5bit(SDL_Color kolor){
    Uint8 szary5b;
    int R,G,B,szary;
    R=kolor.r;
    G=kolor.g;
    B=kolor.b;

    szary=0.299*R+0.587*G+0.114*B;

    szary5b=round(szary*31.0/255);
    return szary5b;

}
/*
funkcja obliczająca odcień szarości ze zredukowanych odcieni do 5 bitów oraz zwracająca kolor
*/

SDL_Color z5bitSzary(Uint8 kolor5bit){
    SDL_Color kolor;
    int szary;

    szary=kolor5bit*255/31;     //32 dostepne kolory (0-31)

    kolor.b=szary;
    kolor.r = szary;
    kolor.g = szary;

    return kolor;
}
/*
funkcja rysująca obraz przy pomocy palety narzuconej wykorzystuje kodowanie
 z palety 24-bitowej do palety 5-bitowej oraz dekodowanie z palety 5 bitowej do 24-bitowej
*/
void paletaNarzucona(){
    Uint8 kolor5bit;
    SDL_Color kolor, nowykolor;

    for (int y=0;y<wysokosc/2;y++){
        for(int x=0;x<szerokosc/2 ;x++){
            kolor=getPixel(x,y);
            kolor5bit=z24Kdo5K(kolor);
            nowykolor=z5Kdo24K(kolor5bit);
            setPixel(x+szerokosc/2,y,nowykolor.r,nowykolor.g,nowykolor.b);

        }
    }
     SDL_UpdateWindowSurface(window);
}
/*

funkcja rysująca obraz przy pomocy palety narzuconej wykorzystuje kodowanie z palety 24-bitowej na odcień 5-bitowej szarości oraz dekodowanie z 5 bitowej palety szarości do 24-bitowej
*/

void paletaNarzuconaSzary(){
    Uint8 kolor5bit;
    SDL_Color kolor, nowykolor;

    for (int y=0;y<wysokosc/2;y++){
        for(int x=0;x<szerokosc/2 ;x++){
            kolor=getPixel(x,y);
            kolor5bit=szary5bit(kolor);
            nowykolor=z5bitSzary(kolor5bit);
            setPixel(x+szerokosc/2,y,nowykolor.r,nowykolor.g,nowykolor.b);

        }
    }
     SDL_UpdateWindowSurface(window);
}
/*
funkcja rysująca paletę przy użyciu zredukowanej palety
*/
void narysujPalete(int px, int py, SDL_Color pal8[]){
    int x, y;
    for (int k=0; k<32; k++){
        y = k / 8;
        x = k % 8;

        for (int xx=0; xx<40; xx++){
            for (int yy=0; yy<40; yy++){
                setPixel(x*40+xx+px, y*40+yy+py, pal8[k].r, pal8[k].g, pal8[k].b);
            }
        }
    }
}


/*
Funkcja wykonująca dithering Bayer’ a, metoda konwersji kolorowego obrazu do czarno-białego
*/

void dithering_bayer() {
    //macierz progowa Bayera 4x4
    double bayer_table[4][4] = {
        {6, 14, 8, 16},
        {10, 2, 12, 4},
        {7, 15, 5, 13},
        {11, 3, 9, 1}
    };

    int r = 4;
    int levels = 5; //liczba odcieni szarości
    int palette[5] = {0, 64, 128, 192, 255};

    SDL_Color kolor;
    int R, G, B;
    double gray, norm, p;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {
            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            //Skala szarości
            gray = 0.299 * R + 0.587 * G + 0.114 * B;
            norm = gray / 255.0;  // normalizacja 0–1

            //Pozycja w tablicy Bayera
            int i = x % r;
            int j = y % r;

            //Próg Bayera (0–1)
            p = (bayer_table[j][i] - 1.0) / (r * r);

            int level = (int)(norm * levels + p);
            if (level < 0) level = 0;
            if (level >= levels) level = levels - 1;

            int intensity = palette[level];

            setPixel(x + szerokosc / 2, y, intensity, intensity, intensity);
        }
    }
}
bool porownajKolory(SDL_Color kolor1, SDL_Color kolor2){
    if(kolor1.r != kolor2.r){
        return false;
    }
    if(kolor1.g != kolor2.g){
        return false;
    }
    if(kolor1.b != kolor2.b){
        return false;
    }
    return true;
}
int sprawdzKolor(SDL_Color kolor){
    if(ileKolorow > 0){
        for(int i = 0; i < ileKolorow; i++){
            if(porownajKolory(kolor, paleta8[i]))
                return i; // jesli kolor znajduje sie juz w palecie to go zwracamy
        }
    }
    return dodajKolor(kolor); //jesli sie nie znajduje, to dodajemy go do palety
}

void paletaWykryta(){
    czyscPalete();
    int indexKoloru;
    SDL_Color kolor;
    for(int y = 0; y < wysokosc/2; y++){
        for(int x = 0; x<szerokosc/2; x++){
            kolor = getPixel(x, y);
            indexKoloru = sprawdzKolor(kolor);
        }
    }

    cout << endl << "liczba kolorow: " << ileKolorow << endl;

    if(ileKolorow <= 32){
        cout << endl << "Paleta spelnia ograniczenie 8bit / piksel" << endl;
       narysujPalete(0,210,paleta8);
    } else{
        cout << endl << "Paleta nie spełnia ograniczenia 8bit / piksel" << endl;
    }
}
int dodajKolor(SDL_Color kolor){
    int aktualnyKolor = ileKolorow;
    paleta8[aktualnyKolor] = kolor;
    if(ileKolorow < 32){
        cout << aktualnyKolor << ": [";
        cout << (int) kolor.r << ", " << (int) kolor.g << ", " << (int) kolor.b;
        cout << "]" << endl;
    }
    ileKolorow++;
    return aktualnyKolor;
}


void czyscPalete(){
for (int k = 0; k< ileKolorow; k++)
paleta8[k] = {0,0,0};
ileKolorow=0;
for (int k=0; k<256; k++){
    paleta8s[k] = {0,0,0};
    paleta8k[k] = {0,0,0};
}

}

void dithering_bayer_color() {
    //macierz progowa Bayera 4x4
    double bayer_table[4][4] = {
        {6, 14, 8, 16},
        {10, 2, 12, 4},
        {7, 15, 5, 13},
        {11, 3, 9, 1}
    };

    int r = 4;
    SDL_Color kolor;
    int R, G, B;
    double p;

    for (int y = 0; y < wysokosc / 2; y++) {
        for (int x = 0; x < szerokosc / 2; x++) {

            kolor = getPixel(x, y);
            R = kolor.r;
            G = kolor.g;
            B = kolor.b;

            int i = x % r;
            int j = y % r;

            p = (bayer_table[j][i] - 1.0) / (r * r);

            //normalizacja 0–1
            double nr = R / 255.0;
            double ng = G / 255.0;
            double nb = B / 255.0;

            //liczba poziomów na kanał
            int levelsR = 4;  // 2 bity
            int levelsG = 4;  // 2 bity
            int levelsB = 2;  // 1 bit

            //kwantyzacja z ditheringiem
            int rq = (int)(nr * levelsR + p);
            int gq = (int)(ng * levelsG + p);
            int bq = (int)(nb * levelsB + p);

            //ograniczenia zakresu
            if (rq < 0) rq = 0;
            if (gq < 0) gq = 0;
            if (bq < 0) bq = 0;

            if (rq >= levelsR) rq = levelsR - 0.1;
            if (gq >= levelsG) gq = levelsG - 0.1;
            if (bq >= levelsB) bq = levelsB - 0.1;

            //skala z powrotem do 0–255
            int R5 = (int)(rq * 255.0 / (levelsR - 0.1));
            int G5 = (int)(gq * 255.0 / (levelsG -0.1));
            int B5 = (int)(bq * 255.0 / (levelsB - 0.1));

            //zapis piksela
            setPixel(x + szerokosc / 2, y, R5, G5, B5);
        }
    }
}
Uint8 znajdzNajblizszyKolor(SDL_Color kolor, SDL_Color paleta[32]) {
    Uint8 najlepszyIndeks = 0;
    int najmniejszaOdleglosc = INT_MAX;

    for (int i = 0; i < 32; i++) {
        int dr = kolor.r - paleta[i].r;
        int dg = kolor.g - paleta[i].g;
        int db = kolor.b - paleta[i].b;
        int odleglosc = dr * dr + dg * dg + db * db;

        if (odleglosc < najmniejszaOdleglosc) {
            najmniejszaOdleglosc = odleglosc;
            najlepszyIndeks = i;
        }
    }
    return najlepszyIndeks;
}




