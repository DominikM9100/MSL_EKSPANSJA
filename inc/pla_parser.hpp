/*////////////////////////////////////////
* Nazwa pliku: pla_parser.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////



#ifndef PLA_PARSER_HPP
#define PLA_PARSER_HPP



#include <vector>
#include <string>
#include <fstream>
#include "kostka.hpp"


// struktura na dane w formacie PLA
struct s_pla_dane
{
    int liczba_wejsc;
    int liczba_wyjsc;
    ZbiorKostek kostki_wejsciowe;
    std::vector<std::string> wartosci_wyjsc;
    std::string typ_pliku;
    std::vector<std::string> nazwy_wejsc;
    std::vector<std::string> nazwy_wyjsc;
};


class PlaParser
{
public:
    // otworz plik pod podana sciezka
    PlaParser (
        const std::string& sciezka_pliku
    );

    // otworz plik z danymi w formacie PLA
    // odczytaj dane i zapisz je w strukturze 's_pla_dane'
    bool wczytaj_dane (
        s_pla_dane& dane
    );


private:
    std::ifstream plik;
};


#endif