#include <iostream>
#include <string>
#include <cstring>

#include "struktury.h"


#ifndef FUNKCJE_H
#define FUNKCJE_H

void pobierzPliki(int argc, char* argv[], std::vector<std::string>& tablica);
//void listowanieKatalogu(const char* sciezka, std::vector<std::string>& tablica);
int zliczanieWierszy(std::string nazwaPliku);
//
Wynik* PobierzWynik(std::string nazwaPliku, int numerWiersza);
//
Wezel* znajdzUczestnika(Wezel* pRoot, std::string nazwisko);
//
void DodajWynik(Wezel*& pRoot, Wynik* wynik);
//
void dodajWezel(Wezel*& pRoot, Wezel* Wezel);
//
void dodajDoListy(ListaWynikow*& pHead, Wynik* wynik);
//
void wypiszZawodnika(Wezel* pRoot);
//
void zapisywanieDoPliku(ListaWynikow* wynik);
//
void usunDrzewo(Wezel*& pRoot);
//
void usunZListy(ListaWynikow*& pHead);
//
void usunListy(Wezel* pRoot);

#endif