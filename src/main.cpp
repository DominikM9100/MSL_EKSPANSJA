/*////////////////////////////////////////
* Nazwa pliku: main.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include <fstream>
#include <string>
#include <iostream>
#include <chrono>
#include <sstream>

#include "pla_parser.hpp"
#include "minimalizacja.hpp"
#include "logger.hpp"
#include "konfiguracja.hpp"


int main(void)
{
    using std::chrono::microseconds;
    Logger::inicjalizuj(SCIEZKA_LOGGER, true); 

    PlaParser parser(SCIEZKA_DANE_WEJSCIOWE);
    s_pla_dane dane;

    if (!parser.wczytaj_dane(dane))
    {
        Logger::info("BŁĄD: Nie wczytano pliku wejściowego.");
        Logger::close();
        return 1;
    }

    ZbiorKostek F, R;
    for (std::size_t i = 0; i < dane.kostki_wejsciowe.rozmiar(); ++i)
    {
        if (dane.wartosci_wyjsc[i] == "1")  F.dodaj_kostke(dane.kostki_wejsciowe[i]);
        else                                R.dodaj_kostke(dane.kostki_wejsciowe[i]);
    }

    Logger::info("Liczba kostek w F: " + std::to_string(F.rozmiar()));
    Logger::info("Liczba kostek w R: " + std::to_string(R.rozmiar()));

    Minimalizacja minimalizacja;
    minimalizacja.ustaw_nazwy_wejsc(dane.nazwy_wejsc);
    minimalizacja.ustaw_nazwy_wyjsc(dane.nazwy_wyjsc);

    auto czas_start = std::chrono::system_clock::now();
    
    auto tablica_ip = minimalizacja.wyznacz_tablice_implikantow_prostych(F, R);
    
    auto minimalny_zbior = minimalizacja.wyznacz_minimalny_zbior_implikantow(tablica_ip);
    
    std::string nazwa_wyjscia = minimalizacja.get_nazwa_wyjscia(0);
    if (!dane.nazwy_wyjsc.empty())
    {
        nazwa_wyjscia = dane.nazwy_wyjsc[0];
    }

    minimalizacja.zapisz_formule(tablica_ip, minimalny_zbior, nazwa_wyjscia);
    auto czas_stop = std::chrono::system_clock::now();
    auto czas_pomiar = std::chrono::duration_cast<microseconds>(czas_stop - czas_start).count();

    std::ostringstream oss;
    oss << "Zmierzony czas: " << czas_pomiar << " us.";
    Logger::info(oss.str());
    Logger::close();

    return 0;
}