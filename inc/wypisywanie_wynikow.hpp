/*////////////////////////////////////////
* Nazwa pliku: wypisywanie_wynikow.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef WYPISYWANIE_WYNIKOW_HPP
#define WYPISYWANIE_WYNIKOW_HPP


#include <string>
#include <vector>
#include "generowanie_implikantow_prostych.hpp" // TablicaImplikantowProstych


class WypisywanieWynikow
{
public:
    using PokrycieKolumnowe = std::vector<std::size_t>;

    void zapisz_formule(
        const TablicaImplikantowProstych& tab,
        const PokrycieKolumnowe& minimalny_zbior,
        const std::string& nazwa_wyjscia,
        const std::vector<std::string>& nazwy_wejsc
    ) const;
};


#endif