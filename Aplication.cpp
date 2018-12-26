using namespace std;

#include <ctime>
#include <iostream>

#include "Aplication.hpp"

Aplikacja* Aplikacja::instance = nullptr;

Aplikacja::Aplikacja() : cel(nullptr), dzien(nullptr), dzisiaj({0,0,0,0,0,0,0,0,0}){
    const time_t now = time(nullptr);
    tm* teraz = localtime(&now);
    dzisiaj = *teraz;
    this->setDzien();
}
void Aplikacja::viewDzien(Dzien* d) {
    string dni_tygodnia[] = {"Niedziela", "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota"};
    string nazwy_miesiecy[] = {"Styczen","Luty","Marzec",
        "Kwiecien","Maj","Czerwiec",
        "Lipiec","Sierpien","Wrzesien",
        "Pazdziernik","Listopad","Grudzien"};
         cout << dni_tygodnia[d->data.tm_wday] << ", " << d->data.tm_mday << " " << nazwy_miesiecy[d->data.tm_mon] << " " << d->data.tm_year+1900 << endl;
}
bool Aplikacja::nieMozliwa() {
    if(this->dzien == nullptr) return false;
    else {
        time_t z_dnia = mktime(&this->dzien->data);
        time_t z_dzisiaj = mktime(&dzisiaj);
        double roznica = difftime(z_dnia, z_dzisiaj);
        if(roznica < 0) return false;
        else return true;
    }
}
Aplikacja* Aplikacja::getInstance() {
    if(instance == nullptr) {
            instance = new Aplikacja();
    }
    return instance;
}
Aplikacja::~Aplikacja() {
    if(!dzien) delete this->dzien;
    if(!cel) delete this->cel;
    instance = nullptr;
    this->cel = nullptr;
    this->dzien = nullptr;
}
Cel* Aplikacja::setCel() {
    this->cel = new Cel();
    this->cel->setTytul();
    this->cel->setOpis();
    this->cel->setTermin();
    this->cel->stan = ST_NZROBIONE;
    return this->cel;
}
void Aplikacja::usunInstancje() {
    delete instance;
}
void Aplikacja::setDzien(int da, int mo, int ye) {
    this->dzien = new Dzien(da,mo,ye);
}
void Aplikacja::setDzien() {
    this->dzien = new Dzien(dzisiaj.tm_mday, dzisiaj.tm_mon+1, dzisiaj.tm_year+1900);
}
void Aplikacja::zapiszCel() {
    time_t czas = this->cel->start;
    tm c;
    Dzien *d;
    while(czas != (cel->koniec+(3600*24))) {
        c = *(localtime(&czas));
        d = new Dzien(c.tm_mday, c.tm_mon+1, c.tm_year+1900);
        d->przypiszCel(this->cel);
        d->zapisz();
        czas += (3600*24);
        delete d;
    }
}
void Aplikacja::usunCel(Cel* post) {
    time_t czas = post->start;
    tm c;
    Dzien *d;
    int pozycja;
    while(czas != (post->koniec+(3600*24))) {
        c = *(localtime(&czas));
        d = new Dzien(c.tm_mday, c.tm_mon+1, c.tm_year+1900);
        d->odczytaj();
        for(int i=0; i < d->cele.size(); i++){
            if(post->tytul == d->cele[i].tytul){
                pozycja = i;
                break;
            }
        }
        d->cele.erase(d->cele.begin() + pozycja);
        d->nadpisz();
        delete d;
        czas += (3600*24);
    }
}
