/*////////////////////////////////////////
* Nazwa pliku: logger.cpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#include "logger.hpp"
#include <filesystem>


std::ofstream Logger::plik;
std::mutex Logger::mtx;


void Logger::inicjalizuj (
    const std::string& sciezka,
    bool truncate
) {
    std::scoped_lock lock(mtx); // zablokuj dostep

    if ( !sciezka.empty()) // jezeli podano sciezke
    {
        auto s = std::filesystem::path(sciezka).parent_path();
        if (!s.empty())
            std::filesystem::create_directories( s); // utworz sciezke
    }

    if (plik.is_open())
        plik.close();

    std::ios::openmode tryb_otwarcia = std::ios::out;
    tryb_otwarcia |= truncate ? std::ios::trunc : std::ios::app; // wybierz jak otworzyc plik

    plik.open( sciezka, tryb_otwarcia);
}


void Logger::info (
    const std::string& lina
) {
    std::scoped_lock lock(mtx);

    if (plik.is_open())
    {
        plik << lina << '\n'; // zapisuj dane do bufora
        plik.flush(); // wymus zwolnienie bufora i zapisz dane
    }
}


void Logger::close()
{
    std::scoped_lock lock(mtx);

    if (plik.is_open())
        plik.close();
}


std::ofstream& Logger::stream()
{
    return plik;
}