/*////////////////////////////////////////
* Nazwa pliku: wyznaczenie_macierzy_blokujacych.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef WYZNACZANIE_MACIERZY_BLOKUJACYCH_HPP
#define WYZNACZANIE_MACIERZY_BLOKUJACYCH_HPP


#include <vector>
#include "kostka.hpp"


class WyznaczanieMacierzyBlokujacych
{
public:
    using MacierzBlokujaca = std::vector<std::vector<bool>>;

    static MacierzBlokujaca wyznacz_macierz_blokujaca(const Kostka& kostka, const ZbiorKostek& R);
};


#endif