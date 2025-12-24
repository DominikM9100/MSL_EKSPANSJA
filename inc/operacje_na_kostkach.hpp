/*////////////////////////////////////////
* Nazwa pliku: operacje_na_kostkach.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef OPERACJE_NA_KOSTKACH_HPP
#define OPERACJE_NA_KOSTKACH_HPP


#include "kostka.hpp"


// klasa pomocnicza do operacji logicznych na kostkach
class OperacjeNaKostkach
{
public:
    static bool czy_kostki_roznia_sie_o_jeden_bit(const Kostka& k1, const Kostka& k2);
    static Kostka lacz_kostki(const Kostka& k1, const Kostka& k2);
    static int liczba_jednynek_w_kostce(const Kostka& k);
    static bool czy_kostka_zawiera(const Kostka& wieksza, const Kostka& mniejsza);
    static bool czy_implikant_pokrywa_kostke(const Kostka& P, const Kostka& K);
};


#endif