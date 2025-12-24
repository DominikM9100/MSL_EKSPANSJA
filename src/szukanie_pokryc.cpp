/*////////////////////////////////////////
* Nazwa pliku: szukanie_pokryc.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "szukanie_pokryc.hpp"


bool SzukaniePokryc::czy_jest_pokryciem(const MacierzBlokujaca& B, const PokrycieKolumnowe& kolumny) const
{
    const std::size_t liczba_wierszy = B.size();
    if (liczba_wierszy == 0) return true;

    for (std::size_t i = 0; i < liczba_wierszy; ++i)
    {
        bool pokryty = false;
        const std::size_t liczba_kolumn_w_wierszu = B[i].size();
        for (std::size_t j = 0; j < kolumny.size(); ++j)
        {
            std::size_t k = kolumny[j];
            if (k >= liczba_kolumn_w_wierszu) continue;
            if (B[i][k]) { pokryty = true; break; }
        }
        if (!pokryty) return false;
    }
    return true;
}


void SzukaniePokryc::szukaj_pokrycia(
    const MacierzBlokujaca& B,
    std::vector<PokrycieKolumnowe>& pokrycia,
    PokrycieKolumnowe& aktualny,
    std::size_t liczba_kolumn,
    std::size_t start,
    std::size_t pozostalo,
    bool& czy_znaleziono
) {
    if (pozostalo == 0)
    {
        if (czy_jest_pokryciem(B, aktualny))
        {
            pokrycia.push_back(aktualny);
            czy_znaleziono = true;
        }
        return;
    }
    if (start >= liczba_kolumn) return;

    for (std::size_t j = start; j <= liczba_kolumn - pozostalo; ++j)
    {
        aktualny.push_back(j);
        szukaj_pokrycia(B, pokrycia, aktualny, liczba_kolumn, j + 1, pozostalo - 1, czy_znaleziono);
        aktualny.pop_back();
    }
}


std::vector<SzukaniePokryc::PokrycieKolumnowe> SzukaniePokryc::znajdz_wszystkie_minimalne_pokrycia_kolumnowe(const MacierzBlokujaca& B)
{
    std::vector<PokrycieKolumnowe> pokrycia;
    const std::size_t liczba_wierszy = B.size();
    if (liczba_wierszy == 0) return pokrycia;
    const std::size_t liczba_kolumn = B[0].size();
    if (liczba_kolumn == 0) return pokrycia;

    for (std::size_t i = 0; i < liczba_wierszy; ++i)
    {
        bool czy_ma_jedynke = false;
        for (bool b : B[i]) if (b) { czy_ma_jedynke = true; break; }
        if (!czy_ma_jedynke) return pokrycia;
    }

    PokrycieKolumnowe aktualny;
    for (std::size_t k = 1; k <= liczba_kolumn; ++k)
    {
        bool czy_znaleziono = false;
        aktualny.clear();
        szukaj_pokrycia(B, pokrycia, aktualny, liczba_kolumn, 0, k, czy_znaleziono);
        if (czy_znaleziono) break;
    }
    return pokrycia;
}


bool SzukaniePokryc::czy_pokrywa(const std::vector<std::vector<bool>>& M, const PokrycieKolumnowe& cols)
{
    const std::size_t rows = M.size();
    if (rows == 0) return true;
    for (std::size_t i = 0; i < rows; ++i)
    {
        bool covered = false;
        const std::size_t row_len = M[i].size();
        for (std::size_t k = 0; k < cols.size(); ++k)
        {
            std::size_t j = cols[k];
            if (j < row_len && M[i][j]) { covered = true; break; }
        }
        if (!covered) return false;
    }
    return true;
}


void SzukaniePokryc::dfs_minimalne_pokrycia(
    const std::vector<std::vector<bool>>& macierz_zredukowana,
    std::size_t liczba_kolumn_zredukowanych,
    PokrycieKolumnowe& aktualne_pokrycie,
    std::vector<PokrycieKolumnowe>& minimalne_pokrycia,
    std::size_t poczatek,
    std::size_t pozostalo,
    bool& znaleziono_poziom
) {
    if (pozostalo == 0)
    {
        if (czy_pokrywa(macierz_zredukowana, aktualne_pokrycie))
        {
            minimalne_pokrycia.push_back(aktualne_pokrycie);
            znaleziono_poziom = true;
        }
        return;
    }
    if (poczatek >= liczba_kolumn_zredukowanych) return;

    for (std::size_t j = poczatek; j <= liczba_kolumn_zredukowanych - pozostalo; ++j)
    {
        aktualne_pokrycie.push_back(j);
        dfs_minimalne_pokrycia(macierz_zredukowana, liczba_kolumn_zredukowanych, aktualne_pokrycie, minimalne_pokrycia, j + 1, pozostalo - 1, znaleziono_poziom);
        aktualne_pokrycie.pop_back();
    }
}