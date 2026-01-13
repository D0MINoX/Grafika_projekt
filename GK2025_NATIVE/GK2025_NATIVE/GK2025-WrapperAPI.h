#pragma once

#ifdef __cplusplus
extern "C" {
#endif

	void RunSDL();
	void laduj_BMP(const char* nazwaPliku, int x, int y);
	void paletaNarzuconaBitAPI();
	void paletanarzuconaAPI();
	void paletaNarzuconaSzaraAPI();
	void paletaMedianCutAPI();
	void paletaMedianCutSzaryAPI();
	void bayerDitheringAPI();
	void bayerDitheringSzaryAPI();
	void zapiszPlikAPI(char const* path);
	void odczytajPlikAPI(char const* path);
	void zapiszPlik5API(char identyfikator, char const* path);
	void odczytajPlik5API(char const* path);
	void opt_zapiszPlik5API(char identyfikator, char const* path);
	void opt_odczytajPlik5API(char const* path);
#ifdef __cplusplus
}
#endif