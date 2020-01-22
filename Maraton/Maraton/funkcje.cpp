#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "funkcje.h"
#include "struktury.h"
#include "nvwa/debug_new.h"

void pobierzPliki(int argc, char* argv[], std::vector<std::string>& tablica)
{
	for (int i = 1; i < argc; i++)
	{
		std::string parameter = argv[i];
		if (parameter.length() > 1)
		{
			if (parameter == "-i")
			{
				for (int i2 = ++i; i2 < argc; i2++)
					tablica.push_back(argv[i2]);

				break;
			}
		}
	}
}

//listowanie Katalogu i dodawanie jej elementow do dynamicznej tablicy
//void listowanieKatalogu(const char* sciezka, std::vector<std::string>& tablica) {  //tego nie ogarniam na tyle, zeby to dokladnie opisac
//	struct dirent* entry;
//	DIR* dir = opendir(sciezka);
//
//	if (dir == NULL) {
//		return;
//	}
//	while ((entry = readdir(dir)) != NULL) {
//		tablica.push_back(entry->d_name);  //dodawanie elementow katalogu do dynamicznej tablicy
//	}
//	tablica.erase(tablica.begin()); //usuniecie tych 2 kropek, co nie wiadomo skad sie biora
//	tablica.erase(tablica.begin());
//
//	closedir(dir);
//}

int zliczanieWierszy(std::string nazwaPliku) { //zliczanie wierszy w celu sprawdzenia ilu jest zawidkó, ¿eby dla kazdego wykonac petle i dodac do drzewa

	int liczbaWierszy = 0;  //poczatkowa wartosc
	std::string wiersz;
	std::ifstream plik(nazwaPliku);


	while (std::getline(plik, wiersz))
		++liczbaWierszy;
	return liczbaWierszy;
}		//w skopiowanym kodzie, nie by³o otwarica pliku, sprawdzania ani zamykania, upenic sie, czy tak moze byc

Wynik* PobierzWynik(std::string nazwaPliku, int numerWiersza) { //funkcja sluzaca do zapisania wyniku w strukturze

	std::ifstream plik;
	plik.open(nazwaPliku); //otwarcie pliku

	if (!plik) { //jesli plik sie nie otowrzy
		std::cout << "Blad pliku" << std::endl; //wyswietla blad pliku
		Wynik* blad = nullptr;
		return blad;
	}

	Wynik* wynik = new Wynik; //nullptr; //todo to nie jest zaden wynik

	std::string wiersz, nazwisko;
	getline(plik, wynik->nazwa); //przypisanie nazwy do struktury
	getline(plik, wynik->data); //przypisanie daty do struktury
	numerWiersza += 2;

	for (int i = 2; i < numerWiersza; i++) //w zalezniosci od numeru wiersza, skipuje tyle wersow, zeby sie dostac do konkretnego
		getline(plik, wiersz);

	getline(plik, wiersz);
	int found = wiersz.find(',');  //szukanie przecinka w celu oddzielenia od reszty ciagu
	if (found != std::string::npos) {  //jesli wynik nie jest rowny temu co wyskakuje, gdy nie znajdzie przecinka 
		&wiersz.erase(0, found + 2);  //wymazuje niepotrzebne miejsce na mecie
		found = wiersz.find(','); //znajduje kolejny przecinek, ktory wskazuje na nazwisko
		nazwisko = wiersz.substr(0, found); // przerabianie wiersza, w celu zdobycia nazwiska
		wynik->nazwisko = nazwisko; //przypisanie nazwiska do struktury

		found = wiersz.find_last_of(','); //szukanie ostatniego przecinka
		wiersz.erase(0, found + 2); // kasowanie zawartosci wiersza, w celu pozostawienia jedynie czasu
		wynik->czas = wiersz; //przypisanie czasu
	}
	return wynik;
}

	Wezel* znajdzUczestnika(Wezel * pRoot, std::string nazwisko)
	{
		if (pRoot)
		{
			if (pRoot->zawodnik->nazwisko == nazwisko)
				return pRoot;

			if (nazwisko < pRoot->zawodnik->nazwisko)
				return znajdzUczestnika(pRoot->pLeft, nazwisko);
			else
				return znajdzUczestnika(pRoot->pRight, nazwisko);
		}
		else
			return nullptr;
	}

	void dodajWezel(Wezel * &pRoot, Wezel * wezel)
	{
		if (!pRoot)
			pRoot = wezel;
		else
		{
			if (wezel->zawodnik->nazwisko < pRoot->zawodnik->nazwisko)
				dodajWezel(pRoot->pLeft, wezel);
			else
				dodajWezel(pRoot->pRight, wezel);
		}
	}

	void dodajDoListy(ListaWynikow * &pHead, Wynik * wynik)
	{
		//pHead = new ListaWynikow{ wynik, pHead };
		 //nie ma listy
		if (not pHead)
		{
			pHead = new ListaWynikow{ wynik,nullptr };
		}
		//czy trzeba zmienic glowe
		else if ((pHead->wynik->data) > wynik->data)
		{
			auto w = pHead->wynik;
			auto p = pHead;
			auto x = pHead->pNext;
			pHead = new ListaWynikow{ wynik,p };
			p = new ListaWynikow{ w,x };
		}
		//w liscie jest 1 data
		else if (pHead->pNext == nullptr)
		{
			pHead->pNext = new ListaWynikow{ wynik,nullptr };
		}
		//w liscie sa 2 lub wiecej datai
		else
		{
			ListaWynikow* obecny = pHead;
			ListaWynikow* nastepny = pHead->pNext;
			//przesuwanie sie w liscie
			while (!(obecny->wynik->data > wynik->data) && (nastepny->wynik->data < wynik->data))
			{
				obecny = nastepny;
				nastepny = nastepny->pNext;
				//jesli dojdziemy do konca
				if (nastepny == nullptr)
				{
					obecny->pNext = new ListaWynikow{ wynik,nullptr };
					return;
				}
			}
			obecny->pNext = new ListaWynikow{ wynik,nastepny };

		}
	}

	void DodajWynik(Wezel*& pRoot, Wynik* wynik)
	{
		std::string nazwisko = wynik->nazwisko;
	
		auto runner = znajdzUczestnika(pRoot, nazwisko);

		//Je¿eli wêze³ z biegaczem nie istnieje, utwórz go.

		if (!runner)
		{
			runner = new Wezel{ new Zawodnik{ nazwisko, nullptr } };
			dodajWezel(pRoot, runner);
		}
	
		//Je¿eli istnieje dodaje kolejny Wynik do listy
		dodajDoListy(runner->zawodnik->pHead, wynik);
	}

	void wypiszZawodnika(Wezel* pRoot) {
		if (pRoot) 
		{
			zapisywanieDoPliku(pRoot->zawodnik->pHead);
			wypiszZawodnika(pRoot->pRight);
			wypiszZawodnika(pRoot->pLeft);	
		}
	}

	void zapisywanieDoPliku(ListaWynikow* wynik) {
		std::ofstream plik;
		if (wynik) {
			plik.open("uczestnicy/" + wynik->wynik->nazwisko, std::ios_base::app);
			plik << wynik->wynik->nazwisko << std::endl;
			plik << std::endl;
			while (wynik) {
				plik << wynik->wynik->data << " " << wynik->wynik->nazwa << " " << wynik->wynik->czas << std::endl;
				wynik = wynik->pNext;
			}
			plik.close();
		}
	}

	void usunZListy(ListaWynikow*& pHead)
	{
		if (pHead->pNext) 
		{
			usunZListy(pHead->pNext);
			delete pHead;
			pHead = nullptr;
		}
	}

	void usunListy(Wezel* pRoot)
	{
		if (pRoot)
		{
			usunListy(pRoot->pLeft);
			usunZListy(pRoot->zawodnik->pHead);
			usunListy(pRoot->pRight);
		}
	}

	void usunDrzewo(Wezel*& pRoot)
	{
		if (pRoot)
		{
			usunDrzewo(pRoot->pLeft);
			usunDrzewo(pRoot->pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}