#ifndef GOAL_HPP_INCLUDED
#define GOAL_HPP_INCLUDED

#include <string>
#include <fstream>

enum STANY {
    ST_ZROBIONE,
    ST_NZROBIONE,
    ST_SREDNIO,
    ST_NOBOWIAZUJE
};

struct Cel {
    /* POLA */
    std::string tytul;
    std::string opis;
    time_t start;
    time_t koniec;
    STANY stan;

    /* METODY */
    Cel();
    void setTermin();
    void setOpis();
    void setTytul();
    void setStan();
    void pokaz();
    void edytuj();
    void getStan();
    void zapiszStan(std::string, int); //deprecated D:
    void zapisz(std::ofstream*);
    void odczytaj(std::ifstream*);
};


#endif // GOAL_HPP_INCLUDED
