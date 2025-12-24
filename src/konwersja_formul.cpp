/*////////////////////////////////////////
* Nazwa pliku: konwersja_formul.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "konwersja_formul.hpp"


std::string KonwersjaFormul::konwertuj_na_formule(const Kostka& kostka, const std::vector<std::string>& nazwy_wejsc)
{
    std::string formula;
    for (size_t i = 0; i < kostka.rozmiar(); ++i)
    {
        if (kostka[i] == '0') {
            formula += "~" + nazwy_wejsc[i] + " * ";
        } else if (kostka[i] == '1') {
            formula += nazwy_wejsc[i] + " * ";
        }
    }
    if (!formula.empty()) {
        formula = formula.substr(0, formula.size() - 3);
    }
    return formula;
}