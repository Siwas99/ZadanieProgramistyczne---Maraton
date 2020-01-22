#include <string>
#include <vector>

#include "funkcje.h"
#include "struktury.h"

int main(int argc, char* argv[])
{
	std::vector<std::string> tablicaNazw; // zdeklarowanie puestej tablicy o zmiennym rozmiarze, do przechowywania nazw plikow

	Wynik* uczestnik; //zdeklarowanie zmiennej do której wprowadzanie beda dane uczestnikow

	Wezel* pKorzen = nullptr;

	//listowanieKatalogu("zawody", tablicaNazw);
	pobierzPliki(argc, argv, tablicaNazw);

	for (int i = 0; i < tablicaNazw.size(); i++) 
	{ //petla dla wszystkich elementow w katalogu
		std::string nazwaPliku("zawody/" + tablicaNazw[i]); //dopisanie do popranych nazw -> zawody/

		int liczbaWierszy = zliczanieWierszy(nazwaPliku);  //zliczenie wierszy w celu ustalenia jak wiele jest zawodnikow, aby dla kazdego z osobna wykonac petle i osobno dodac do drzewa

		for (int idUczestnika = 0; idUczestnika <= liczbaWierszy - 3; idUczestnika++) { //petla do wypisania po kolei kazdego uczestnika
			uczestnik = PobierzWynik(nazwaPliku, idUczestnika); //funckja do tego co wyzej
			DodajWynik(pKorzen, uczestnik);
		}
	}

	wypiszZawodnika(pKorzen);

	usunListy(pKorzen);
	usunListy(pKorzen);
	usunDrzewo(pKorzen);
	usunDrzewo(pKorzen);

	return 0;
}