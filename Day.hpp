#ifndef DAY_HPP_INCLUDED
#define DAY_HPP_INCLUDED

#include <ctime>
#include <vector>

#include "Goal.hpp"

class Dzien {
public:
    /* POLA */
    tm data;
    std::vector<Cel> cele;

    /* METODY */
    Dzien();
    Dzien(int day, int month, int year);
    void przypiszCel(Cel *cel);
    void wyswietlCele();
    void zmienStan(Cel *cel);
    std::string toString(int);
    std::string strData();
    void nadpisz();
    void zapisz();
    bool odczytaj();
};

#endif // DAY_HPP_INCLUDED
