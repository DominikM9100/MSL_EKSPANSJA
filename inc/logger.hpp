/*////////////////////////////////////////
* Nazwa pliku: logger.hpp
* Projekt:     MSL - Ekspansja
* Autor:       Dominik Majak
*/////////////////////////////////////////


#ifndef LOGGER_HPP
#define LOGGER_HPP


#include <fstream>
#include <mutex>
#include <string>


class Logger
{
public:
    static void inicjalizuj (
        const std::string& sciezka = "log/log_przetwarzanie.txt", // domyslna sciezka: log/log_przetwarzanie.txt
        bool truncate = true // truncate==true — nadpisuje log przy starcie
    );

    // zapisz log w jednej linii
    static void info (
        const std::string& lina
    );

    // zamknij plik
    static void close();

    // dostęp do strumienia (np. do <<)
    static std::ofstream& stream();

private:
    static std::ofstream plik; // uchwyt do pliku
    static std::mutex mtx; // mutex do blokowania dostepu do zasobow w czasie zapisywania
};


#endif