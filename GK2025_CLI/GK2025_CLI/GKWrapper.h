#pragma once
public ref class GKWrapper
{
public:
	void StartSDL();
	void LoadBMP(System::String^ fileName, int x, int y);
	void palette_imposeed();
	void palette_imposeed_gray();
	void palette_imposeed_bit();
	void palette_median_cut();
	void palette_median_cut_gray();
	void bayer_dithering();
	void bayer_dithering_gray();
	void save_file();
	void load_file();
};

