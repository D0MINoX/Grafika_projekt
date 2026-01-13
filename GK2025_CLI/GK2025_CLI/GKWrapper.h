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
	void save_file(System::String^ path);
	void load_file(System::String^ path);
	void save_file_5(System::Char identyfikator, System::String^ path);
	void load_file_5(System::String^ path);
	void opt_save_file_5(System::Char identyfikator, System::String^ path);
	void opt_load_file_5(System::String^ path);
};

