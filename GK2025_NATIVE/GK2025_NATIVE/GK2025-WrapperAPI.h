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

#ifdef __cplusplus
}
#endif