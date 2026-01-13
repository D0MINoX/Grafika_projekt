// funkcje do operacji na plikach
#include "GK2025-Funkcje.h"
#include "GK2025-Zmienne.h"
#include "GK2025-Paleta.h"
#include "GK2025-MedianCut.h"
#include "GK2025-Pliki.h"

/*
Funkcja zapiszPlikv0 zapisuje dane o obrazie do pliku binarnego obraz.bin u¿ywajaæ prze³adowanego oeratora strumienia wyjœcia

*/

void zapiszPlikv0(){
    SDL_Color kolor;
    Uint16 szerokoscObrazka=szerokosc/2;
    Uint16 wysokoscObrazka=wysokosc/2;
    Uint8 ileBitow=24;
    cout<<"zapisujemy plik 'obraz.bin' uzywajac operatora <<"<<endl;
    ofstream wyjscie("obraz.bin");
    wyjscie<<"DG";
    wyjscie<<(Uint8)szerokoscObrazka<<(Uint8)(szerokoscObrazka>>8);
    wyjscie<<(Uint8)wysokoscObrazka<<(Uint8)(wysokoscObrazka>>8);
    wyjscie<<ileBitow;
    for(int y=0;y<wysokoscObrazka;y++){
        for(int x=0;x<szerokoscObrazka;x++){
            kolor=getPixel(x,y);
            wyjscie<<kolor.r<<kolor.g<<kolor.b;
        }
    }
    wyjscie.close();

    SDL_UpdateWindowSurface(window);
}
/*

Funkcja zapiszPlik zapisuje dane o obrazie w pliku binarnym obrazRGB.bin za pomoc¹ wunkcji write

*/

void zapiszPlik(const char* path){
     SDL_Color kolor;
    Uint16 szerokoscObrazka=szerokosc/2;
    Uint16 wysokoscObrazka=wysokosc/2;
    Uint8 ileBitow=24;
    char identyfikator[]="DG";
    cout<<"zapisujemy plik'obrazRGB.bin' uzywajac write()"<<endl;
    ofstream wyjscie(path,ios::binary);
    wyjscie.write((char*)&identyfikator,sizeof(char)*2);
    wyjscie.write((char*)&szerokoscObrazka,sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka,sizeof(Uint16));
    wyjscie.write((char*)&ileBitow,sizeof(Uint8));
     for(int y=0;y<wysokoscObrazka;y++){
        for(int x=0;x<szerokoscObrazka;x++){
            kolor=getPixel(x,y);
            wyjscie.write((char*)&kolor,sizeof(Uint8)*3);
           /* wyjscie.write((char*)&kolor.r,sizeof(Uint8));
            wyjscie.write((char*)&kolor.g,sizeof(Uint8));
            wyjscie.write((char*)&kolor.b,sizeof(Uint8));
            */
        }
    }
    wyjscie.close();
    SDL_UpdateWindowSurface(window);

}
/*
Funkcja odczytajPlik odczytuje dane o obrazie z pliku binarnego obrazRGB.bin za pomoc¹ funkcji read
*/

void odczytajPlik(char const* path){
    SDL_Color kolor;
    Uint16 szerokoscObrazka=szerokosc/2;
    Uint16 wysokoscObrazka=wysokosc/2;
    Uint8 ileBitow=24;
    char identyfikator[]="  ";
    cout<<"odczytujemy plik'obrazRGB.bin' uzywajac read()"<<endl;
    ifstream wejscie(path,ios::binary);
     wejscie.read((char*)&identyfikator,sizeof(char)*2);
    wejscie.read((char*)&szerokoscObrazka,sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka,sizeof(Uint16));
    wejscie.read((char*)&ileBitow,sizeof(Uint8));
    cout<<"id: "<<identyfikator<<endl;
    cout<<"szerokosc: "<<szerokoscObrazka<<endl;
    cout<<"wysokosc: "<<wysokoscObrazka<<endl;
    cout<<"ile bitow: "<<(int)ileBitow<<endl;
      for(int y=0;y<wysokoscObrazka;y++){
        for(int x=0;x<szerokoscObrazka;x++){
            wejscie.read((char*)&kolor,sizeof(Uint8)*3);
            setPixel(x+(szerokosc/2),y,kolor.r,kolor.g,kolor.b);
        }
    }
    SDL_UpdateWindowSurface(window);
}

/*
Funkcja zapiszPlik5 zapisuje dane o obrazie do pliku binarnego obraz5.bin, jednoczeœnie konwertuj¹c dane na palete 5-bitow¹
*/

void zapiszPlik5(char identyfikator,const char* path) {
    SDL_Color kolor;
    Uint8 kolor5bit;
    Uint16 szerokoscObrazka=szerokosc/2;
    Uint16 wysokoscObrazka=wysokosc/2;
    Uint8 ileBitow=5;
    char id = identyfikator;
    cout<<"zapis pliku 'obraz5.bin' metoda write()"<<endl;
    ofstream wyjscie(path,ios::binary);
    wyjscie.write((char*)&id,sizeof(char));
    wyjscie.write((char*)&szerokoscObrazka,sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka,sizeof(Uint16));
    wyjscie.write((char*)&ileBitow,sizeof(Uint8));
    switch(identyfikator){
        case '1':
            for(int y=0;y<wysokoscObrazka;y++){
                for(int x=0;x<szerokoscObrazka;x++){
                    kolor=getPixel(x,y);
                    kolor5bit= z24Kdo5K(kolor);
                    wyjscie.write((char*)&kolor5bit,sizeof(Uint8));
                }
            }
        break;
        case'2':
             for(int y=0;y<wysokoscObrazka;y++){
                for(int x=0;x<szerokoscObrazka;x++){
                    kolor=getPixel(x,y);
                    kolor5bit= szary5bit(kolor);
                    wyjscie.write((char*)&kolor5bit,sizeof(Uint8));
                }
            }
            break;
        case '3':
            paletaWykryta();
            for (int i = 0; i < 32; i++) {
            wyjscie.write((char*)&paleta8[i].r, sizeof(Uint8));
            wyjscie.write((char*)&paleta8[i].g, sizeof(Uint8));
            wyjscie.write((char*)&paleta8[i].b, sizeof(Uint8));
            }

            for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++) {
                kolor = getPixel(x, y);
                Uint8 indeks = znajdzNajblizszyKolor(kolor, paleta8);
                wyjscie.write((char*)&indeks, sizeof(Uint8));
            }
        }

            break;
        case '4':
            paletaMedianCutBW();
             for (int i = 0; i < 32; i++) {
            wyjscie.write((char*)&paleta8s[i].r, sizeof(Uint8));
            wyjscie.write((char*)&paleta8s[i].g, sizeof(Uint8));
            wyjscie.write((char*)&paleta8s[i].b, sizeof(Uint8));
            }

            for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++) {
                kolor = getPixel(x, y);
                Uint8 indeks = znajdzNajblizszyKolor(kolor, paleta8s);
                wyjscie.write((char*)&indeks, sizeof(Uint8));

            }}
            break;
        case '5':
            paletaMedianCut();
             for (int i = 0; i < 32; i++) {
            wyjscie.write((char*)&paleta8k[i].r, sizeof(Uint8));
            wyjscie.write((char*)&paleta8k[i].g, sizeof(Uint8));
            wyjscie.write((char*)&paleta8k[i].b, sizeof(Uint8));
            }

            for(int y = 0; y < wysokoscObrazka; y++) {
            for(int x = 0; x < szerokoscObrazka; x++) {
                kolor = getPixel(x, y);
                Uint8 indeks = znajdzNajblizszyKolor(kolor, paleta8k);
                wyjscie.write((char*)&indeks, sizeof(Uint8));

            }}
            break;
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}
/*
Funkcja odczytajPlik5 odczytuje dane o obrazie z pliku obraz5.bin jednoczeœnie konwertuj¹c obraz z zredukowanej palety 5-bitowej do pe³nej palety 24-bitowej dla poprawnie dzia³aj¹cego wyœwietlania
*/

void odczytajPlik5(char const* path){
    SDL_Color kolor;
    Uint8 kolor5bit;
    Uint16 szerokoscObrazka=szerokosc/2;
    Uint16 wysokoscObrazka=wysokosc/2;
    Uint8 ileBitow=24;
    char identyfikator=' ';
    cout<<"odczytujemy plik'obraz5.bin' uzywajac read()"<<endl;
    ifstream wejscie(path,ios::binary);

     wejscie.read((char*)&identyfikator,sizeof(char));
    wejscie.read((char*)&szerokoscObrazka,sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka,sizeof(Uint16));
    wejscie.read((char*)&ileBitow,sizeof(Uint8));

    cout<<"id: "<<identyfikator<<endl;
    cout<<"szerokosc: "<<szerokoscObrazka<<endl;
    cout<<"wysokosc: "<<wysokoscObrazka<<endl;
    cout<<"ile bitow: "<<(int)ileBitow<<endl;
    switch(identyfikator){
      case '1':
      for(int y=0;y<wysokoscObrazka;y++){
        for(int x=0;x<szerokoscObrazka;x++){
            wejscie.read((char*)&kolor5bit,sizeof(Uint8));
            kolor=z5Kdo24K(kolor5bit);
            setPixel(x+(szerokosc/2),y,kolor.r,kolor.g,kolor.b);
        }
    }
    break;
      case '2':
          for(int y=0;y<wysokoscObrazka;y++){
                for(int x=0;x<szerokoscObrazka;x++){
                wejscie.read((char*)&kolor5bit,sizeof(Uint8));
                kolor=z5bitSzary(kolor5bit);
                setPixel(x+(szerokosc/2),y,kolor.r,kolor.g,kolor.b);
                }
            }
        break;

    case '3':{
    SDL_Color paleta8[32];

    // Odczyt palety (32 kolorów po 3 bajty)
    for (int i = 0; i < 32; i++) {
        wejscie.read((char*)&paleta8[i].r, sizeof(Uint8));
        wejscie.read((char*)&paleta8[i].g, sizeof(Uint8));
        wejscie.read((char*)&paleta8[i].b, sizeof(Uint8));
        cout<<"["<<paleta8[i].r<<","<<paleta8[i].g<<","<<paleta8[i].b<<"]"<<endl;
    }

    // Odczyt pikseli jako indeksów do palety
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            Uint8 indeks;
            wejscie.read((char*)&indeks, sizeof(Uint8));
            kolor = paleta8[indeks];
            setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
        }
    }
    }
    break;
    case '4':{
        SDL_Color paleta[32];

    // Odczyt palety (32 kolorów po 3 bajty)
    for (int i = 0; i < 32; i++) {
        wejscie.read((char*)&paleta[i].r, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].g, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].b, sizeof(Uint8));
        cout<<"["<<paleta[i].r<<","<<paleta[i].g<<","<<paleta[i].b<<"]"<<endl;
    }

    // Odczyt pikseli jako indeksów do palety
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            Uint8 indeks;
            wejscie.read((char*)&indeks, sizeof(Uint8));
            kolor = paleta[indeks];
            setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
        }
    }
    break;
    }
    case '5':{
        SDL_Color paleta[32];

    // Odczyt palety (32 kolorów po 3 bajty)
    for (int i = 0; i < 32; i++) {
        wejscie.read((char*)&paleta[i].r, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].g, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].b, sizeof(Uint8));
        cout<<"["<<paleta[i].r<<","<<paleta[i].g<<","<<paleta[i].b<<"]"<<endl;
    }

    // Odczyt pikseli jako indeksów do palety
    for (int y = 0; y < wysokoscObrazka; y++) {
        for (int x = 0; x < szerokoscObrazka; x++) {
            Uint8 indeks;
            wejscie.read((char*)&indeks, sizeof(Uint8));
            kolor = paleta[indeks];
            setPixel(x + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
        }
    }
    break;
    }
}
    SDL_UpdateWindowSurface(window);
}

/*
Funkcja opt_zapiszPlik5 ma za zadanie zoptymalizować zapis z funkcji zapiszPlik5.
*/
void opt_zapiszPlik5(char identyfikator, const char* path){
    SDL_Color kolor;
    Uint8 kolor5bit;

    Uint16 szerokoscObrazka=szerokosc/2;
    Uint16 wysokoscObrazka=wysokosc/2;
    Uint8 ileBitow=5;
    char id=identyfikator;

    cout<<"zapis pliku 'obraz5_opt.bin' metoda write() - zoptymalizowana"<<endl;
    ofstream wyjscie(path,ios::binary);

    wyjscie.write((char*)&id,sizeof(char));
    wyjscie.write((char*)&szerokoscObrazka,sizeof(Uint16));
    wyjscie.write((char*)&wysokoscObrazka,sizeof(Uint16));
    wyjscie.write((char*)&ileBitow,sizeof(Uint8));

    Uint32 bufor;
    int aktualneBity;

    switch(id){
        case '1':
            bufor = 0;
            aktualneBity = 0;
            for(int x=0;x<szerokoscObrazka;x+=8){
                for(int y=0;y<wysokoscObrazka;y++){
                        for(int i = 0; i < 8; i++){
                            int xx = x + i;
                            if(xx >= szerokoscObrazka) break;

                            kolor = getPixel(xx, y);
                            kolor5bit = z24Kdo5K(kolor);

                            bufor = (bufor << 5) | (kolor5bit&0x1F);
                            aktualneBity+=5;

                            while(aktualneBity>=8){
                                Uint8 bajt = (bufor >> (aktualneBity - 8)) & 0xFF;
                                wyjscie.write((char*)&bajt,sizeof(Uint8));
                                aktualneBity-=8;
                            }

                        }
                }
            }
            if(aktualneBity > 0){
                Uint8 bajt = (bufor << (8 - aktualneBity)) & 0xFF;
                wyjscie.write((char*)&bajt,sizeof(Uint8));
            }
        break;
        case'2':
             bufor = 0;
             aktualneBity = 0;
             for(int x=0;x<szerokoscObrazka;x+=8){
                for(int y=0;y<wysokoscObrazka;y++){
                        for(int i = 0; i < 8; i++){
                            int xx = x+i;
                            if(xx >= szerokoscObrazka) break;

                            kolor=getPixel(xx,y);
                            kolor5bit= szary5bit(kolor);

                            bufor = (bufor << 5 ) | (kolor5bit & 0x1F);
                            aktualneBity += 5;

                            while(aktualneBity >= 8){
                                Uint8 bajt = (bufor >> (aktualneBity - 8)) &0xFF;
                                wyjscie.write((char*)&bajt,sizeof(Uint8));
                                aktualneBity -= 8;
                            }
                        }
                }
            }
            if(aktualneBity > 0){
                Uint8 bajt = (bufor << (8 - aktualneBity)) &0xFF;
                wyjscie.write((char*)&bajt, sizeof(Uint8));
            }
            break;
        case '3':
            bufor = 0;
            aktualneBity = 0;

            paletaWykryta();

            for (int i = 0; i < 32; i++) {
            wyjscie.write((char*)&paleta8[i].r, sizeof(Uint8));
            wyjscie.write((char*)&paleta8[i].g, sizeof(Uint8));
            wyjscie.write((char*)&paleta8[i].b, sizeof(Uint8));
            }
            for(int x = 0; x < szerokoscObrazka; x+=8){
                for(int y = 0; y < wysokoscObrazka; y++){
                        for(int i = 0; i < 8; i++){
                            int xx = x + i;

                            if(xx>=szerokoscObrazka) break;

                            kolor = getPixel(xx, y);
                            Uint8 indeks = znajdzNajblizszyKolor(kolor, paleta8);

                            bufor = (bufor << 5) | (indeks &0x1F);
                            aktualneBity += 5;

                            while(aktualneBity >= 8){
                                Uint8 bajt = (bufor >> (aktualneBity - 8)) &0xFF;
                                wyjscie.write((char*)&bajt, sizeof(Uint8));
                                aktualneBity -= 8;
                        }
                    }
                }
            }
            if(aktualneBity > 0){
                Uint8 bajt = (bufor << (8 - aktualneBity)) &0xFF;
                wyjscie.write((char*)&bajt, sizeof(Uint8));
            }
            break;
        case '4':
            bufor = 0;
            aktualneBity = 0;

            paletaMedianCutBW();

            for (int i = 0; i < 32; i++) {
                wyjscie.write((char*)&paleta8s[i].r, sizeof(Uint8));
                wyjscie.write((char*)&paleta8s[i].g, sizeof(Uint8));
                wyjscie.write((char*)&paleta8s[i].b, sizeof(Uint8));
            }
            for(int x = 0; x < szerokoscObrazka; x+=8){
                for(int y = 0; y < wysokoscObrazka; y++){
                        for(int i = 0; i < 8; i++){
                            int xx = x + i;
                            if(xx>=szerokoscObrazka) break;

                            kolor = getPixel(xx, y);
                            Uint8 indeks = znajdzNajblizszyKolor(kolor, paleta8s);

                            bufor = (bufor << 5) | (indeks &0x1F);
                            aktualneBity += 5;

                            while(aktualneBity >= 8){
                                Uint8 bajt = (bufor >> (aktualneBity - 8)) &0xFF;
                                wyjscie.write((char*)&bajt, sizeof(Uint8));
                                aktualneBity -= 8;
                        }
                    }
                }
            }
            while(aktualneBity > 0){
                Uint8 bajt = (bufor << (8 - aktualneBity)) &0xFF;
                wyjscie.write((char*)&bajt, sizeof(Uint8));
            }

            break;
        case '5':
            bufor = 0;
            aktualneBity = 0;

            paletaMedianCut();

            for (int i = 0; i < 32; i++) {
                wyjscie.write((char*)&paleta8k[i].r, sizeof(Uint8));
                wyjscie.write((char*)&paleta8k[i].g, sizeof(Uint8));
                wyjscie.write((char*)&paleta8k[i].b, sizeof(Uint8));
            }
            for(int x = 0; x < szerokoscObrazka; x+=8){
                for(int y = 0; y < wysokoscObrazka; y++){
                        for(int i = 0; i < 8; i++){
                            int xx = x + i;
                            if(xx>=szerokoscObrazka) break;

                            kolor = getPixel(xx, y);
                            Uint8 indeks = znajdzNajblizszyKolor(kolor, paleta8k);

                            bufor = (bufor << 5) | (indeks &0x1F);
                            aktualneBity += 5;

                            while(aktualneBity >= 8){
                                Uint8 bajt = (bufor >> (aktualneBity - 8)) &0xFF;
                                wyjscie.write((char*)&bajt, sizeof(Uint8));
                                aktualneBity -= 8;
                        }
                    }
                }
            }
            while(aktualneBity > 0){
                Uint8 bajt = (bufor << (8 - aktualneBity)) &0xFF;
                wyjscie.write((char*)&bajt, sizeof(Uint8));
            }
            break;
    }

    wyjscie.close();
    SDL_UpdateWindowSurface(window);
}

/*
Funkcja opt_odczytajPlik5 ma za zadanie odczytać plik zapisany w sposób zoptymalizowany.
*/

void opt_odczytajPlik5(char const* path){
    SDL_Color kolor;
    Uint8 kolor5bit;

    Uint16 szerokoscObrazka=szerokosc/2;
    Uint16 wysokoscObrazka=wysokosc/2;
    Uint8 ileBitow=24;

    char identyfikator=' ';

    cout<<"odczytujemy plik'obraz5_opt.bin' uzywajac read()"<<endl;
    ifstream wejscie( path,ios::binary);

    wejscie.read((char*)&identyfikator,sizeof(char));
    wejscie.read((char*)&szerokoscObrazka,sizeof(Uint16));
    wejscie.read((char*)&wysokoscObrazka,sizeof(Uint16));
    wejscie.read((char*)&ileBitow,sizeof(Uint8));

    cout<<"id: "<<identyfikator<<endl;
    cout<<"szerokosc: "<<szerokoscObrazka<<endl;
    cout<<"wysokosc: "<<wysokoscObrazka<<endl;
    cout<<"ile bitow: "<<(int)ileBitow<<endl;

    Uint32 bufor;
    int aktualneBity;

    switch(identyfikator){
      case '1':
          bufor = 0;
          aktualneBity = 0;

          for(int x=0;x<szerokoscObrazka;x+=8){
            for(int y=0;y<wysokoscObrazka;y++){
                    for(int i = 0; i < 8; i++){
                        int xx = x + i;
                        if(xx>=szerokoscObrazka) break;

                        while(aktualneBity < 5){
                            Uint8 bajt;
                            wejscie.read((char*)&bajt,sizeof(Uint8));
                            bufor = (bufor << 8) | bajt;
                            aktualneBity += 8;
                        }

                        Uint8 wartosc5bit = (bufor >> (aktualneBity - ileBitow)) & ((1 << ileBitow) - 1);
                        aktualneBity -= 5;

                        kolor = z5Kdo24K(wartosc5bit);
                        setPixel(xx+(szerokosc/2),y,kolor.r,kolor.g,kolor.b);
                    }
            }
          }
    break;
      case '2':
          bufor = 0;
          aktualneBity = 0;
          for(int x=0;x<szerokoscObrazka;x+=8){
                for(int y=0;y<wysokoscObrazka;y++){
                    for(int i = 0; i < 8; i++){
                        int xx = x + i;
                        if(xx>=szerokoscObrazka) break;

                        while(aktualneBity < 5){
                            Uint8 bajt;
                            wejscie.read((char*)&bajt,sizeof(Uint8));
                            bufor = (bufor << 8) | bajt;
                            aktualneBity += 8;
                        }

                        Uint8 wartosc5bit = (bufor >> (aktualneBity - 5)) &0x1F;
                        aktualneBity -= 5;

                        kolor = z5bitSzary(wartosc5bit);
                        setPixel(xx+(szerokosc/2),y,kolor.r,kolor.g,kolor.b);
                    }
                }
            }
        break;

    case '3':{
    SDL_Color paleta8[32];

    // Odczyt palety (32 kolorów po 3 bajty)
    for (int i = 0; i < 32; i++) {
        wejscie.read((char*)&paleta8[i].r, sizeof(Uint8));
        wejscie.read((char*)&paleta8[i].g, sizeof(Uint8));
        wejscie.read((char*)&paleta8[i].b, sizeof(Uint8));
        cout<<"["<<paleta8[i].r<<","<<paleta8[i].g<<","<<paleta8[i].b<<"]"<<endl;
    }

    // Odczyt pikseli jako indeksów do palety
    bufor = 0;
    aktualneBity = 0;

    for (int x = 0; x < szerokoscObrazka; x+=8) {
        for (int y = 0; y < wysokoscObrazka; y++) {
            for(int i = 0; i < 8; i++){
                int xx = x + i;

                if(xx >= szerokoscObrazka) break;

                while (aktualneBity < 5){
                    Uint8 bajt;
                    wejscie.read((char*)&bajt, sizeof(Uint8));
                    bufor = (bufor << 8) | bajt;
                    aktualneBity += 8;
                }
                Uint8 indeks = (bufor >> (aktualneBity - 5)) & 0x1F;
                aktualneBity -=5;
                kolor = paleta8[indeks];
                setPixel(xx + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
            }
        }
    }
    }
    break;
    case '4':{
        SDL_Color paleta[32];

    // Odczyt palety (32 kolorów po 3 bajty)
    for (int i = 0; i < 32; i++) {
        wejscie.read((char*)&paleta[i].r, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].g, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].b, sizeof(Uint8));
        cout<<"["<<paleta[i].r<<","<<paleta[i].g<<","<<paleta[i].b<<"]"<<endl;
    }

    bufor = 0;
    aktualneBity = 0;

    // Odczyt pikseli jako indeksów do palety
    for (int x = 0; x< szerokoscObrazka; x+=8) {
        for (int y = 0; y < wysokoscObrazka; y++) {
                for(int i = 0; i < 8; i++){
                    int xx = x + i;
                    if(xx >= szerokoscObrazka) break;

                    while(aktualneBity < 5){
                        Uint8 bajt;
                        wejscie.read((char*)&bajt, sizeof(Uint8));
                        bufor = (bufor << 8) | bajt;
                        aktualneBity += 8;
                    }
                    Uint8 indeks = (bufor >> (aktualneBity - 5)) & 0x1F;
                    aktualneBity-=5;
                    kolor = paleta[indeks];
                    setPixel(xx + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
                }

        }
    }
    break;
    }
    case '5':{
        SDL_Color paleta[32];

    // Odczyt palety (32 kolorów po 3 bajty)
    for (int i = 0; i < 32; i++) {
        wejscie.read((char*)&paleta[i].r, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].g, sizeof(Uint8));
        wejscie.read((char*)&paleta[i].b, sizeof(Uint8));
        cout<<"["<<paleta[i].r<<","<<paleta[i].g<<","<<paleta[i].b<<"]"<<endl;
    }

    // Odczyt pikseli jako indeksów do palety
    bufor = 0;
    aktualneBity = 0;
    for (int x = 0; x < szerokoscObrazka; x+=8) {
        for (int y = 0; y < wysokoscObrazka; y++) {
            for(int i = 0; i < 8; i++){
                int xx = x + i;
                if(xx >= szerokoscObrazka) break;

                while(aktualneBity < 5){
                    Uint8 bajt;
                    wejscie.read((char*)&bajt, sizeof(Uint8));
                    bufor = (bufor << 8) | bajt;
                    aktualneBity += 8;
                }
                Uint8 indeks = (bufor >> (aktualneBity - 5)) & 0x1F;
                aktualneBity -= 5;
                kolor = paleta[indeks];
                setPixel(xx + (szerokosc / 2), y, kolor.r, kolor.g, kolor.b);
            }
        }
    }
    break;
    }
}
    SDL_UpdateWindowSurface(window);
}
