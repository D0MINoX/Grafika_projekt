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

void GKWrapper::save_file(System::String^ path)
{
	zapiszPlikAPI((const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());
}

void GKWrapper::load_file(System::String^ path)
{
	odczytajPlikAPI((const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());
}
void GKWrapper::save_file_5(System::Char identyfikator,System::String^ path)
{
	zapiszPlik5API((char)identyfikator, (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());
}


void GKWrapper::load_file_5(System::String^ path)
{
	odczytajPlik5API((const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());
}

void GKWrapper::opt_save_file_5(System::Char identyfikator,System::String^ path)
{
	opt_zapiszPlik5API((char)identyfikator, (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());
}

void GKWrapper::opt_load_file_5(System::String^ path)
{
	opt_odczytajPlik5API((const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(path)).ToPointer());
}

