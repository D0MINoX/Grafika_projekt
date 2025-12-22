#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	void RunSDL();
	void laduj_BMP(const char* nazwaPliku, int x, int y);
	void paletanarzuconaAPI();
	void paletaNarzuconaSzaraAPI();
	void bayerDitheringAPI();
	void bayerDitheringSzaryAPI();

#ifdef __cplusplus
}
#endif