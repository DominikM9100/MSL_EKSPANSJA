/*////////////////////////////////////////
* Nazwa pliku: redukcja_tablicy.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef REDUKCJA_TABLICY_HPP
#define REDUKCJA_TABLICY_HPP


#include <vector>
#include "generowanie_implikantow_prostych.hpp" // dla TablicaImplikantowProstych
#include "szukanie_pokryc.hpp"


class RedukcjaTablicy
{
public:
    using PokrycieKolumnowe = std::vector<std::size_t>;

    PokrycieKolumnowe wyznacz_minimalny_zbior_implikantow(const TablicaImplikantowProstych& tab);

private:
    SzukaniePokryc szukaniePokryc;
};


#endif