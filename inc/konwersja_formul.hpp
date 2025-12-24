/*////////////////////////////////////////
* Nazwa pliku: konwersja_formul.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef KONWERSJA_FORMUL_HPP
#define KONWERSJA_FORMUL_HPP


#include "kostka.hpp"
#include <vector>
#include <string>


class KonwersjaFormul
{
public:
    static std::string konwertuj_na_formule(const Kostka& kostka, const std::vector<std::string>& nazwy_wejsc);
};


#endif