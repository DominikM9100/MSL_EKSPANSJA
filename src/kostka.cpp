/*////////////////////////////////////////
* Nazwa pliku: kostka.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "kostka.hpp"


// inicjalizuj kostke
Kostka::Kostka (
    const std::string& kostka
) {
    this->kostka = kostka;
}


// zwroc wartosc kostki jako string
std::string Kostka::pobierz_wartosc() const
{
    return kostka;
}


// zwroc rozmiar koskti
size_t Kostka::rozmiar() const
{
    return kostka.size();
}


// zwroc znak z kostki spod podanego indeksu
char Kostka::operator[] (
    size_t indeks
) const {
    return kostka[indeks];
}


// dodaj kostke do zbioru kostek
void ZbiorKostek::dodaj_kostke (
    const Kostka& kostka
) {
    kostki.push_back( kostka); // dodaj kostke do zbioru
}


// zwroc rozmiar zbioru kostek
size_t ZbiorKostek::rozmiar() const
{
    return kostki.size();
}


// zwroc kostke spod podanego indeku
const Kostka& ZbiorKostek::operator[] (
    size_t indeks
) const {
    return kostki[indeks];
}


// zwroc zbior kostek
std::vector<Kostka> ZbiorKostek::pobierz_kostki() const
{
    return kostki;
}