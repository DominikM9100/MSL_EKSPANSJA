/*////////////////////////////////////////
* Nazwa pliku: kostka.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef KOSTKA_HPP
#define KOSTKA_HPP


#include <string>
#include <vector>


class Kostka
{
public:
    // inicjalizuj kostke
    Kostka (
        const std::string& kostka
    );

    // zwroc wartosc kostki jako string
    std::string pobierz_wartosc() const;

    // zwroc rozmiar koskti
    size_t rozmiar() const;

    // zwroc znak z kostki spod podanego indeksu
    char operator[] (
        size_t indeks
    ) const;

private:
    std::string kostka;
};


class ZbiorKostek
{
public:
    // dodaj kostke do zbioru kostek
    void dodaj_kostke (
        const Kostka& kostka
    );

    // zwroc rozmiar zbioru kostek
    size_t rozmiar() const;

    // zwroc kostke spod podanego indeku
    const Kostka& operator[] (
        size_t indeks
    ) const;

    // zwroc zbior kostek
    std::vector<Kostka> pobierz_kostki() const;
    
private:
    std::vector<Kostka> kostki;
};


#endif