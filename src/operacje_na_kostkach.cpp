/*////////////////////////////////////////
* Nazwa pliku: operacje_na_kostkach.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "operacje_na_kostkach.hpp"
#include <algorithm>


bool OperacjeNaKostkach::czy_kostki_roznia_sie_o_jeden_bit(const Kostka& k1, const Kostka& k2)
{
    if (k1.rozmiar() != k2.rozmiar()) return false;
    int roznice = 0;
    for (size_t i = 0; i < k1.rozmiar(); ++i)
    {
        if (k1[i] != k2[i])
        {
            if (k1[i] == '-' || k2[i] == '-') return false;
            roznice++;
            if (roznice > 1) return false;
        }
    }
    return roznice == 1;
}


Kostka OperacjeNaKostkach::lacz_kostki(const Kostka& k1, const Kostka& k2)
{
    std::string wynik = k1.pobierz_wartosc();
    for (size_t i = 0; i < k1.rozmiar(); ++i)
    {
        if (k1[i] != k2[i]) wynik[i] = '-';
    }
    return Kostka(wynik);
}


int OperacjeNaKostkach::liczba_jednynek_w_kostce(const Kostka& k)
{
    int licznik = 0;
    for (size_t i = 0; i < k.rozmiar(); ++i)
    {
        if (k[i] == '1') licznik++;
    }
    return licznik;
}


bool OperacjeNaKostkach::czy_kostka_zawiera(const Kostka& wieksza, const Kostka& mniejsza)
{
    if (wieksza.rozmiar() != mniejsza.rozmiar()) return false;
    for (size_t i = 0; i < wieksza.rozmiar(); ++i)
    {
        if (wieksza[i] != '-' && wieksza[i] != mniejsza[i]) return false;
    }
    return true;
}


bool OperacjeNaKostkach::czy_implikant_pokrywa_kostke(const Kostka& P, const Kostka& K)
{
    const std::size_t n = std::min(P.rozmiar(), K.rozmiar());
    for (std::size_t i = 0; i < n; ++i)
    {
        const char p = P[i];
        const char k = K[i];
        if (k == '-') {
            if (p != '-') return false;
        } else {
            if (!(p == '-' || p == k)) return false;
        }
    }
    for (std::size_t i = n; i < P.rozmiar(); ++i) {
        if (P[i] != '-') return false;
    }
    return true;
}