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
	void zapiszPlikAPI();
	void odczytajPlikAPI();
	void zapiszPlik5API(char identyfikator);
	void odczytajPlik5API();
#ifdef __cplusplus
}
#endif