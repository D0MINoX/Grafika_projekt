#include "pch.h"
#include "GKWrapper.h"
#include "../../GK2025_NATIVE/GK2025_NATIVE/GK2025-WrapperAPI.h"

void GKWrapper::StartSDL()
{
    RunSDL();   // wywo³anie funkcji z biblioteki .lib
}

void GKWrapper::LoadBMP(System::String^ fileName, int x, int y)
{
	laduj_BMP((const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(fileName)).ToPointer(), x, y);
}

void GKWrapper::palette_imposeed()
{
	paletanarzuconaAPI();
}

void GKWrapper::palette_imposeed_gray()
{
	paletaNarzuconaSzaraAPI();
}

void GKWrapper::palette_imposeed_bit()
{
	paletaNarzuconaBitAPI();
}

void GKWrapper::palette_median_cut()
{
	paletaMedianCutAPI();
}

void GKWrapper::palette_median_cut_gray()
{
	paletaMedianCutSzaryAPI();
}

void GKWrapper::bayer_dithering()
{
	bayerDitheringAPI();
}

void GKWrapper::bayer_dithering_gray()
{
	bayerDitheringSzaryAPI();
}

void GKWrapper::save_file()
{
	zapiszPlikAPI();
}

void GKWrapper::load_file()
{
	odczytajPlikAPI();
}
void GKWrapper::save_file_5(System::Char identyfikator)
{
	zapiszPlik5API((char)identyfikator);
}


void GKWrapper::load_file_5()
{
	odczytajPlik5API();
}

void GKWrapper::opt_save_file_5(System::Char identyfikator)
{
	opt_zapiszPlik5API((char)identyfikator);
}

void GKWrapper::opt_load_file_5()
{
	opt_odczytajPlik5API();
}

