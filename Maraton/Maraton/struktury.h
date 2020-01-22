#ifndef STRUKTURY_H
#define STRUKTURY_H

#include <string>

typedef struct ListaWynikow;

struct Zawodnik
{
	std::string nazwisko;
	ListaWynikow* pHead;
};

struct Wynik
{
	std::string nazwisko;
	std::string nazwa;
	std::string data;
	std::string czas;
};

struct ListaWynikow
{
	Wynik* wynik;
	ListaWynikow* pNext;
};

struct Wezel
{
	Zawodnik* zawodnik;
	Wezel* pLeft;
	Wezel* pRight;
};

#endif