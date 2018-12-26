#ifndef APLICATION_HPP_INCLUDED
#define APLICATION_HPP_INCLUDED

#include "Day.hpp"
#include "Goal.hpp"

class Aplikacja {

private:
    Aplikacja();
    Aplikacja(const Aplikacja&);
    operator=(const Aplikacja&);
    static Aplikacja *instance;

public:
    /* POLA */
    Cel *cel;
    Dzien *dzien;
    tm dzisiaj;

    /* METODY */
    static Aplikacja *getInstance();
    ~Aplikacja();
    static void usunInstancje();
    bool nieMozliwa();
    void viewDzien(Dzien*);
    void setDzien();
    Cel* setCel();
    void zapiszCel();
    void usunCel(Cel*);
    void setDzien(int day, int month, int year);
};


#endif // APLICATION_HPP_INCLUDED
