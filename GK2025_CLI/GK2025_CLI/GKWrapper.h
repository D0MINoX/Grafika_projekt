#pragma once
public ref class GKWrapper
{
public:
	void StartSDL();
	void LoadBMP(System::String^ fileName, int x, int y);
	void palette_imposeed();
	void palette_imposeed_gray();
	void bayer_dithering();
	void bayer_dithering_gray();
};

