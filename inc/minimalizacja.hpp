/*////////////////////////////////////////
* Nazwa pliku: minimalizacja.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef MINIMALIZACJA_HPP
#define MINIMALIZACJA_HPP


#include <vector>
#include <string>
#include "kostka.hpp"
#include "generowanie_implikantow_prostych.hpp" // definicja TablicaImplikantowProstych
#include "redukcja_tablicy.hpp"
#include "wypisywanie_wynikow.hpp"


class Minimalizacja
{
public:
    using PokrycieKolumnowe = std::vector<std::size_t>;

    // przekazanie nazw wejsc
    void ustaw_nazwy_wejsc(const std::vector<std::string>& nazwy);
    // przekazanie nazw wyjsc
    void ustaw_nazwy_wyjsc(const std::vector<std::string>& nazwy);
    std::string get_nazwa_wyjscia(const unsigned int& numer);

    // glowna logika (przekierowana GenerowanieImplikantowProstych)
    TablicaImplikantowProstych wyznacz_tablice_implikantow_prostych(
        const ZbiorKostek& F,
        const ZbiorKostek& R
    );

    // glowna logika (przekierowana do RedukcjaTablicy)
    PokrycieKolumnowe wyznacz_minimalny_zbior_implikantow(
        const TablicaImplikantowProstych& tab
    );

    // glowna logika (przekierowana WypisywanieWynikow)
    void zapisz_formule(
        const TablicaImplikantowProstych& tab,
        const PokrycieKolumnowe& minimalny_zbior,
        const std::string& nazwa_wyjscia
    ) const;

private:
    std::vector<std::string> nazwy_wejsc;
    std::vector<std::string> nazwy_wyjsc;

    GenerowanieImplikantowProstych generator;
    RedukcjaTablicy reduktor;
    WypisywanieWynikow pisanie;
};


#endif