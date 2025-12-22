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

void GKWrapper::bayer_dithering()
{
	bayerDitheringAPI();
}

void GKWrapper::bayer_dithering_gray()
{
	bayerDitheringSzaryAPI();
}

