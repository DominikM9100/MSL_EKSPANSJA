/*////////////////////////////////////////
* Nazwa pliku: redukcja_tablicy.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "redukcja_tablicy.hpp"
#include "logger.hpp"
#include "konfiguracja.hpp"
#include <algorithm>
#include <sstream>


RedukcjaTablicy::PokrycieKolumnowe RedukcjaTablicy::wyznacz_minimalny_zbior_implikantow(const TablicaImplikantowProstych& tab)
{
    PokrycieKolumnowe wynik;
    const std::size_t m = tab.kostki.size();
    const std::size_t n = tab.implikanty_proste.size();
    if (m == 0 || n == 0) {
#if WLACZ_LOGGER_POKRYC
        Logger::info("Wyznaczanie minimalnego zbioru implikantów: pusta tablica.");
#endif
        return wynik;
    }

    const auto& macierz_pokrycia = tab.macierz;
    std::vector<bool> implikant_istotny(n, false);

    for (std::size_t i = 0; i < m; ++i)
    {
        if (i >= macierz_pokrycia.size()) break;
        std::size_t licznik = 0;
        std::size_t ostatnia_kolumna = 0;
        const std::size_t dlugosc_wiersza = macierz_pokrycia[i].size();
        for (std::size_t j = 0; j < n && j < dlugosc_wiersza; ++j)
            if (macierz_pokrycia[i][j]) { ++licznik; ostatnia_kolumna = j; }

        if (licznik == 1)
            implikant_istotny[ostatnia_kolumna] = true;
    }

    std::vector<bool> wiersz_pokryty(m, false);
    for (std::size_t i = 0; i < m; ++i)
    {
        if (i >= macierz_pokrycia.size()) break;
        const std::size_t dlugosc_wiersza = macierz_pokrycia[i].size();
        for (std::size_t j = 0; j < n && j < dlugosc_wiersza; ++j)
        {
            if (implikant_istotny[j] && macierz_pokrycia[i][j]) {
                wiersz_pokryty[i] = true;
                break;
            }
        }
    }

    std::vector<std::size_t> mapa_wierszy, mapa_kolumn;
    for (std::size_t i = 0; i < m; ++i)
        if (!wiersz_pokryty[i]) mapa_wierszy.push_back(i);

    for (std::size_t j = 0; j < n; ++j)
    {
        if (implikant_istotny[j]) continue;
        bool przydatny = false;
        for (std::size_t indeks_wiersza = 0; indeks_wiersza < mapa_wierszy.size(); ++indeks_wiersza)
        {
            std::size_t i = mapa_wierszy[indeks_wiersza];
            if (i < macierz_pokrycia.size() && j < macierz_pokrycia[i].size() && macierz_pokrycia[i][j])
            {
                przydatny = true;
                break;
            }
        }
        if (przydatny) mapa_kolumn.push_back(j);
    }

    std::vector<std::vector<bool>> macierz_zredukowana;
    macierz_zredukowana.assign(mapa_wierszy.size(), std::vector<bool>(mapa_kolumn.size(), false));
    for (std::size_t indeks_wiersza = 0; indeks_wiersza < mapa_wierszy.size(); ++indeks_wiersza)
    {
        std::size_t i = mapa_wierszy[indeks_wiersza];
        for (std::size_t indeks_kolumny = 0; indeks_kolumny < mapa_kolumn.size(); ++indeks_kolumny)
        {
            std::size_t j = mapa_kolumn[indeks_kolumny];
            if (i < macierz_pokrycia.size() && j < macierz_pokrycia[i].size())
                macierz_zredukowana[indeks_wiersza][indeks_kolumny] = macierz_pokrycia[i][j];
        }
    }

    std::vector<PokrycieKolumnowe> minimalne_pokrycia;
    if (!mapa_wierszy.empty() && !mapa_kolumn.empty())
    {
        const std::size_t liczba_kolumn_zredukowanych = mapa_kolumn.size();
        PokrycieKolumnowe aktualne_pokrycie;
        for (std::size_t k = 1; k <= liczba_kolumn_zredukowanych; ++k)
        {
            bool znaleziono_poziom = false;
            aktualne_pokrycie.clear();
            szukajPokryc.dfs_minimalne_pokrycia(
                macierz_zredukowana,
                liczba_kolumn_zredukowanych,
                aktualne_pokrycie,
                minimalne_pokrycia,
                0, k, znaleziono_poziom
            );
            if (znaleziono_poziom) break;
        }
    }

    for (std::size_t j = 0; j < n; ++j)
        if (implikant_istotny[j]) wynik.push_back(j);

    if (!minimalne_pokrycia.empty())
    {
        const auto& pokrycie_zredukowane = minimalne_pokrycia.front();
        for (std::size_t indeks = 0; indeks < pokrycie_zredukowane.size(); ++indeks)
        {
            std::size_t kolumna_zredukowana = pokrycie_zredukowane[indeks];
            if (kolumna_zredukowana < mapa_kolumn.size())
                wynik.push_back(mapa_kolumn[kolumna_zredukowana]);
        }
    }

    std::sort(wynik.begin(), wynik.end());
    wynik.erase(std::unique(wynik.begin(), wynik.end()), wynik.end());

#if WLACZ_LOGGER_POKRYC
    {
        std::ostringstream oss;
        oss << "Minimalny zbiór implikantów (indeksy): { ";
        for (std::size_t t = 0; t < wynik.size(); ++t) {
            oss << wynik[t];
            if (t + 1 < wynik.size()) oss << ", ";
        }
        oss << " }";
        Logger::info(oss.str());
    }
    {
        std::ostringstream oss;
        oss << "Minimalny zbiór implikantów (nazwy): ";
        for (std::size_t t = 0; t < wynik.size(); ++t) {
            oss << "I" << wynik[t];
            if (t + 1 < wynik.size()) oss << ", ";
        }
        Logger::info(oss.str());
    }
#endif

    return wynik;
}