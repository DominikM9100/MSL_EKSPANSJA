/*////////////////////////////////////////
* Nazwa pliku: minimalizacja.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "minimalizacja.hpp"


void Minimalizacja::ustaw_nazwy_wejsc(const std::vector<std::string>& nazwy)
{
    nazwy_wejsc = nazwy;
}


void Minimalizacja::ustaw_nazwy_wyjsc(const std::vector<std::string>& nazwy)
{
    nazwy_wyjsc = nazwy;
}


std::string Minimalizacja::get_nazwa_wyjscia(const unsigned int& numer)
{
    if (numer < nazwy_wyjsc.size())
        return nazwy_wyjsc[numer];
    return "";
}


TablicaImplikantowProstych Minimalizacja::wyznacz_tablice_implikantow_prostych(
    const ZbiorKostek& F,
    const ZbiorKostek& R
) {
    return generator.wyznacz_tablice_implikantow_prostych(F, R, nazwy_wejsc);
}


Minimalizacja::PokrycieKolumnowe Minimalizacja::wyznacz_minimalny_zbior_implikantow(
    const TablicaImplikantowProstych& tab
) {
    return reduktor.wyznacz_minimalny_zbior_implikantow(tab);
}


void Minimalizacja::zapisz_formule(
    const TablicaImplikantowProstych& tab,
    const PokrycieKolumnowe& minimalny_zbior,
    const std::string& nazwa_wyjscia
) const {
    pisanie.zapisz_formule(tab, minimalny_zbior, nazwa_wyjscia, nazwy_wejsc);
}