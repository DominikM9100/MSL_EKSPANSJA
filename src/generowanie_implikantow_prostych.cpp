/*////////////////////////////////////////
* Nazwa pliku: generowanie_implikantow_prostych.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "generowanie_implikantow_prostych.hpp"
#include "wyznaczanie_macierzy_blokujacych.hpp"
#include "operacje_na_kostkach.hpp"
#include "logger.hpp"
#include "konfiguracja.hpp"
#include <sstream>


GenerowanieImplikantowProstych::GenerowanieImplikantowProstych() {}


GenerowanieImplikantowProstych::PokryciaDlaZbioru GenerowanieImplikantowProstych::znajdz_pokrycia(
    const ZbiorKostek& F,
    const ZbiorKostek& R,
    const std::vector<std::string>& nazwy_wejsc
) {
    PokryciaDlaZbioru wszystkie_pokrycia;
    const std::size_t n = F.rozmiar();
    wszystkie_pokrycia.resize(n);

    for (std::size_t i = 0; i < n; ++i)
    {
        const Kostka& f = F[i];
#if WLACZ_LOGGER_POKRYC
        Logger::info("Przetwarzanie kostki F[" + std::to_string(i) + "]: " + f.pobierz_wartosc());
#endif
        auto B = WyznaczanieMacierzyBlokujacych::wyznacz_macierz_blokujaca(f, R);
        auto pokrycia = szukaniePokryc.znajdz_wszystkie_minimalne_pokrycia_kolumnowe(B);

        if (pokrycia.empty())
        {
#if WLACZ_LOGGER_POKRYC
            Logger::info("  Brak pokrycia kolumnowego dla tej macierzy blokującej.");
#endif
            wszystkie_pokrycia[i].clear();
            continue;
        }

        for (const auto& pokrycie : pokrycia)
        {
            if (!szukaniePokryc.czy_jest_pokryciem(B, pokrycie))
            {
#if WLACZ_LOGGER_POKRYC
                Logger::info("  UWAGA: sprawdzane pokrycie nie pokrywa macierzy blokującej.");
#endif
            }
#if WLACZ_LOGGER_POKRYC
            {
                std::ostringstream oss;
                oss << "  Minimalne pokrycie kolumnowe (indeksy): { ";
                for (std::size_t k = 0; k < pokrycie.size(); ++k) {
                    oss << pokrycie[k];
                    if (k + 1 < pokrycie.size()) oss << ", ";
                }
                oss << " }";
                Logger::info(oss.str());
            }
            {
                std::ostringstream oss;
                oss << "  Minimalne pokrycie kolumnowe (wejścia): { ";
                for (std::size_t j = 0; j < pokrycie.size(); ++j) {
                    std::size_t p = pokrycie[j];
                    if (!nazwy_wejsc.empty() && p < nazwy_wejsc.size())
                        oss << nazwy_wejsc[p];
                    else if (p < 26)
                        oss << static_cast<char>('a' + static_cast<char>(p));
                    else
                        oss << "kol" << p;
                    if (j + 1 < pokrycie.size()) oss << ", ";
                }
                oss << " }";
                Logger::info(oss.str());
            }
#endif
        }
        wszystkie_pokrycia[i] = std::move(pokrycia);
    }
    return wszystkie_pokrycia;
}


TablicaImplikantowProstych GenerowanieImplikantowProstych::wyznacz_tablice_implikantow_prostych(
    const ZbiorKostek& F,
    const ZbiorKostek& R,
    const std::vector<std::string>& nazwy_wejsc
) {
    TablicaImplikantowProstych tab;
    const std::size_t n = F.rozmiar();
    if (n == 0) {
#if WLACZ_LOGGER_POKRYC
        Logger::info("Wyznaczanie tablicy implikantów prostych: zbiór F jest pusty.");
#endif
        return tab;
    }

#if WLACZ_LOGGER_POKRYC
    Logger::info("Wyznaczanie tablicy implikantów prostych dla F (" + std::to_string(n) + " kostek).");
#endif

    std::vector<Kostka> implikanty_proste;
    auto wszystkie_pokrycia = znajdz_pokrycia(F, R, nazwy_wejsc);

    for (std::size_t i = 0; i < n; ++i)
    {
        const Kostka& f = F[i];
#if WLACZ_LOGGER_POKRYC
        Logger::info("  Kostka F[" + std::to_string(i) + "] = " + f.pobierz_wartosc());
#endif
        const auto& pokrycia = wszystkie_pokrycia[i];
        if (pokrycia.empty()) {
#if WLACZ_LOGGER_POKRYC
            Logger::info("    Brak minimalnych pokryć kolumnowych dla tej kostki.");
#endif
            continue;
        }

        for (const auto& pokrycie : pokrycia)
        {
            std::string wartosc = f.pobierz_wartosc();
            std::vector<bool> w_pokryciu(wartosc.size(), false);
            for (std::size_t j = 0; j < pokrycie.size(); ++j) {
                std::size_t p = pokrycie[j];
                if (p < w_pokryciu.size()) w_pokryciu[p] = true;
            }
            for (std::size_t j = 0; j < wartosc.size(); ++j)
                if (!w_pokryciu[j]) wartosc[j] = '-';

            Kostka implikant(wartosc);
            bool czy_istnieje = false;
            for (const Kostka& k : implikanty_proste)
                if (k.pobierz_wartosc() == wartosc) { czy_istnieje = true; break; }

            if (!czy_istnieje) {
#if WLACZ_LOGGER_POKRYC
                Logger::info("    Dodano implikant prosty: " + wartosc + " (z kostki F[" + std::to_string(i) + "])");
#endif
                implikanty_proste.push_back(implikant);
            }
        }
    }

    tab.implikanty_proste = implikanty_proste;
    tab.kostki.clear();
    tab.kostki.reserve(n);
    for (std::size_t i = 0; i < n; ++i) tab.kostki.push_back(F[i]);

    const std::size_t liczba_wierszy = tab.kostki.size();
    const std::size_t liczba_kolumn = tab.implikanty_proste.size();
    tab.macierz.assign(liczba_wierszy, std::vector<bool>(liczba_kolumn, false));

    for (std::size_t i = 0; i < liczba_wierszy; ++i)
    {
        const Kostka& k = tab.kostki[i];
        for (std::size_t j = 0; j < liczba_kolumn; ++j)
        {
            const Kostka& ip = tab.implikanty_proste[j];
            if (OperacjeNaKostkach::czy_implikant_pokrywa_kostke(ip, k))
                tab.macierz[i][j] = true;
        }
    }

#if WLACZ_LOGGER_POKRYC
    {
        std::ostringstream oss;
        oss << "Implikanty proste (kolumny): ";
        for (std::size_t j = 0; j < liczba_kolumn; ++j)
            oss << "I" << j << " = " << tab.implikanty_proste[j].pobierz_wartosc() << "  ";
        Logger::info(oss.str());
    }
    {
        std::ostringstream oss;
        oss << "Tablica implikantów (wiersze = kostki F):";
        Logger::info(oss.str());
    }
    for (std::size_t i = 0; i < liczba_wierszy; ++i)
    {
        std::ostringstream oss;
        oss << "k" << i << " (" << tab.kostki[i].pobierz_wartosc() << "): ";
        for (std::size_t j = 0; j < liczba_kolumn; ++j)
            oss << (tab.macierz[i][j] ? '1' : '0') << ' ';
        Logger::info(oss.str());
    }
#endif

    return tab;
}