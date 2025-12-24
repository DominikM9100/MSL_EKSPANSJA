/*////////////////////////////////////////
* Nazwa pliku: generowanie_implikantow_prostych.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////



#ifndef GENEROWANIE_IMPLIKANTOW_PROSTYCH_HPP
#define GENEROWANIE_IMPLIKANTOW_PROSTYCH_HPP


#include <vector>
#include <string>
#include "kostka.hpp"
#include "szukanie_pokryc.hpp"


// struktura opisujaca tablice implikantow
struct TablicaImplikantowProstych
{
    std::vector<Kostka> implikanty_proste;  // kolumny
    std::vector<Kostka> kostki;             // wiersze z 'F'
    std::vector<std::vector<bool>> macierz; // macierz pokrycia
};


class GenerowanieImplikantowProstych
{
public:
    using PokrycieKolumnowe = std::vector<std::size_t>;
    using PokryciaDlaKostki = std::vector<PokrycieKolumnowe>;
    using PokryciaDlaZbioru = std::vector<PokryciaDlaKostki>;

    GenerowanieImplikantowProstych();

    TablicaImplikantowProstych wyznacz_tablice_implikantow_prostych(
        const ZbiorKostek& F,
        const ZbiorKostek& R,
        const std::vector<std::string>& nazwy_wejsc
    );

private:
    SzukaniePokryc szukaniePokryc;

    PokryciaDlaZbioru znajdz_pokrycia(
        const ZbiorKostek& F,
        const ZbiorKostek& R,
        const std::vector<std::string>& nazwy_wejsc
    );
};

#endif