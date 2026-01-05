/*////////////////////////////////////////
* Nazwa pliku: szukanie_pokryc.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef SZUKANIE_POKRYC_HPP
#define SZUKANIE_POKRYC_HPP


#include <vector>
#include <cstddef>


class SzukaniePokryc
{
public:
    using MacierzBlokujaca = std::vector<std::vector<bool>>;
    using PokrycieKolumnowe = std::vector<std::size_t>;

    // metody dla ekspansji
    bool czy_jest_pokryciem(const MacierzBlokujaca& B, const PokrycieKolumnowe& kolumny) const;
    std::vector<PokrycieKolumnowe> znajdz_wszystkie_minimalne_pokrycia_kolumnowe(const MacierzBlokujaca& B);

    // metody dla redukcji tabeli
    bool czy_pokrywa(const std::vector<std::vector<bool>>& M, const PokrycieKolumnowe& kolumny);
    
    void dfs_minimalne_pokrycia(
        const std::vector<std::vector<bool>>& macierz_zredukowana,
        std::size_t liczba_kolumn_zredukowanych,
        PokrycieKolumnowe& aktualne_pokrycie,
        std::vector<PokrycieKolumnowe>& minimalne_pokrycia,
        std::size_t poczatek,
        std::size_t pozostalo,
        bool& znaleziono_poziom
    );

private:
    void szukaj_pokrycia(
        const MacierzBlokujaca& B,
        std::vector<PokrycieKolumnowe>& pokrycia,
        PokrycieKolumnowe& aktualny,
        std::size_t liczba_kolumn,
        std::size_t start,
        std::size_t pozostalo,
        bool& czy_znaleziono
    );
};


#endif