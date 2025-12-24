/*////////////////////////////////////////
* Nazwa pliku: wypisywanie_wynikow.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "wypisywanie_wynikow.hpp"
#include "logger.hpp"
#include "konfiguracja.hpp"
#include <iostream>
#include <sstream>


void WypisywanieWynikow::zapisz_formule(
    const TablicaImplikantowProstych& tab,
    const PokrycieKolumnowe& minimalny_zbior,
    const std::string& nazwa_wyjscia,
    const std::vector<std::string>& nazwy_wejsc
) const {
    if (minimalny_zbior.empty())
    {
        std::string komunikat = "Brak implikantów w minimalnym zbiorze dla wyjścia " + nazwa_wyjscia;
        std::cout << komunikat << std::endl;
#if WLACZ_LOGGER_POKRYC
        Logger::info(komunikat);
#endif
        return;
    }

    {
        std::ostringstream oss;
        oss << nazwa_wyjscia << " = ";
        for (std::size_t idx = 0; idx < minimalny_zbior.size(); ++idx)
        {
            oss << "I" << minimalny_zbior[idx];
            if (idx + 1 < minimalny_zbior.size()) oss << " + ";
        }
        const std::string linia = oss.str();
        std::cout << linia << std::endl;
#if WLACZ_LOGGER_POKRYC
        Logger::info(linia);
#endif
    }

    {
        std::ostringstream oss;
        oss << nazwa_wyjscia << " = ";

        const auto& PI = tab.implikanty_proste;
        bool pierwszy_termin = true;
        for (std::size_t t = 0; t < minimalny_zbior.size(); ++t)
        {
            std::size_t kol = minimalny_zbior[t];
            if (kol >= PI.size()) continue;

            const std::string wartosc = PI[kol].pobierz_wartosc();
            std::ostringstream term;
            bool pierwszy_literal = true;
            for (std::size_t bit = 0; bit < wartosc.size(); ++bit)
            {
                char c = wartosc[bit];
                if (c == '-') continue;
                if (!pierwszy_literal) term << " * ";
                if (c == '0') term << "~";
                if (!nazwy_wejsc.empty() && bit < nazwy_wejsc.size())
                    term << nazwy_wejsc[bit];
                else
                    term << "x" << (bit + 1);
                pierwszy_literal = false;
            }

            std::string termStr = term.str();
            if (termStr.empty()) termStr = "1";

            if (!pierwszy_termin) oss << " + ";
            oss << "(" << termStr << ")";
            pierwszy_termin = false;
        }

        const std::string linia = oss.str();
        std::cout << linia << std::endl;
#if WLACZ_LOGGER_POKRYC
        Logger::info(linia);
#endif
    }
}