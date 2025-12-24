/*////////////////////////////////////////
* Nazwa pliku: pla_parser.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "pla_parser.hpp"
#include <sstream>
#include <iostream>


PlaParser::PlaParser (
    const std::string& sciezka_pliku
) {
    plik.open( sciezka_pliku); // otworz plik przy inicjalizacji
}


bool PlaParser::wczytaj_dane (
    s_pla_dane& dane
) {
    if ( !plik.is_open()) // czy plik jest zamkniety?
        return false;

    std::string linia;

    while ( std::getline( plik, linia)) // dopoki sa linie do odczytania
    {
        if (linia.empty()) // jezeli jest pusta linia
            continue;
        
        std::istringstream strumien( linia);
        std::string klucz;
        strumien >> klucz; // zapisz znaki, wg ktorych przydzielisz do odpowiedniej grupy

        if (klucz == ".type")
        {
            strumien >> dane.typ_pliku;
        }
        else if (klucz == ".i")
        {
            strumien >> dane.liczba_wejsc;
        }
        else if (klucz == ".o")
        {
            strumien >> dane.liczba_wyjsc;
        }
        else if (klucz == ".ilb")
        {
            for ( int i=0; i < dane.liczba_wejsc; ++i)
            {
                std::string nazwa;
                strumien >> nazwa;
                dane.nazwy_wejsc.push_back( nazwa);
            }
        }
        else if (klucz == ".ob")
        {
            for (int i = 0; i < dane.liczba_wyjsc; ++i)
            {
                std::string nazwa;
                strumien >> nazwa;
                dane.nazwy_wyjsc.push_back( nazwa);
            }
        }
        else if (klucz == ".p")
        {
            // ignoruj liczbe kostek
        }
        else if (klucz == ".e")
        {
            break; // zakoncz czytanie pliku
        }
        else if ( !klucz.empty() && klucz[0] != '.')
        {
            std::string wejscie = klucz;   // pierwszy klucz to wzorzec wejsciowy
            std::string wyjscie;

            // drugi klucz to wartosc wyjsciowa
            if ( !(strumien >> wyjscie))
            {
                std::cerr << "Pominieto wiersz danych (brak wyjscia): " << wejscie << "\n";
                continue;
            }

            // sprawdzenie: dlugosc wejscia = liczba wejsc
            if ( !wejscie.empty() && static_cast<int>(wejscie.size()) == dane.liczba_wejsc)
            {
                dane.kostki_wejsciowe.dodaj_kostke( Kostka(wejscie)); // dodaj kostke
                dane.wartosci_wyjsc.push_back( wyjscie); // dodaj wyjscie
            }
            else
            {
                std::cerr << "Pominieto wiersz danych (niewlasciwa długosc): " << wejscie << " " << wyjscie << "\n";
            }
        }
    }

    return true;
}