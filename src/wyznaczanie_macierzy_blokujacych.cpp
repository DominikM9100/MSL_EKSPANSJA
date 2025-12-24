/*////////////////////////////////////////
* Nazwa pliku: wyznaczenie_macierzy_blokujacych.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "wyznaczanie_macierzy_blokujacych.hpp"
#include "logger.hpp"
#include "konfiguracja.hpp"
#include <sstream>
#include <algorithm>
#include <string>


WyznaczanieMacierzyBlokujacych::MacierzBlokujaca WyznaczanieMacierzyBlokujacych::wyznacz_macierz_blokujaca(const Kostka& kostka, const ZbiorKostek& R)
{
    MacierzBlokujaca B;
    const std::size_t liczba_wierszy = R.rozmiar();
    const std::size_t liczba_kolumn = kostka.rozmiar();

    if (liczba_wierszy == 0)
    {
#if WLACZ_LOGGER_MACIERZY_BLOKUJACYCH
        Logger::info("Wyznaczanie macierzy blokującej: zbiór R jest pusty — macierz jest pusta.");
#endif
        return B;
    }

    B.assign(liczba_wierszy, std::vector<bool>(liczba_kolumn, false));
    for (std::size_t i = 0; i < liczba_wierszy; ++i)
    {
        const Kostka& r_kostka = R[i];
        if (r_kostka.rozmiar() != liczba_kolumn)
        {
#if WLACZ_LOGGER_MACIERZY_BLOKUJACYCH
            Logger::info("OSTRZEŻENIE: różna długość kostki w R[" + std::to_string(i) + "] niż kostki bazowej.");
#endif
        }

        const std::size_t wspolna_dlugosc = std::min(liczba_kolumn, r_kostka.rozmiar());
        for (std::size_t j = 0; j < wspolna_dlugosc; ++j)
        {
            const char k = kostka[j];
            const char r = r_kostka[j];
            if (k == '-' || r == '-') continue;
            if (k != r) B[i][j] = true;
        }
    }

#if WLACZ_LOGGER_MACIERZY_BLOKUJACYCH
    {
        std::ostringstream oss;
        oss << "Macierz blokująca dla kostki: " << kostka.pobierz_wartosc();
        Logger::info(oss.str());
        for (std::size_t i = 0; i < liczba_wierszy; ++i)
        {
            std::string wiersz;
            wiersz.reserve(liczba_kolumn);
            for (std::size_t j = 0; j < liczba_kolumn; ++j)
                wiersz += B[i][j] ? '1' : '0';
            Logger::info("R[" + std::to_string(i) + "] " + R[i].pobierz_wartosc() + " -> " + wiersz);
        }
    }
#endif

    return B;
}