using namespace std;

#include <iostream>
#include <sstream>
#include <ctime>
#include <fstream>
#include <cstdlib>

#include "Aplication.hpp"

Dzien::Dzien() { this->cele.clear(); this->data = {0,0,0,0,0,0,0,0,0}; }
Dzien::Dzien(int d, int m, int y) {
    this->cele.clear();
    this->data = {0,0,0,0,0,0,0,0,0};
    this->data.tm_mday = d;
    this->data.tm_mon = m-1;
    this->data.tm_year = y-1900;
}
string Dzien::toString(int liczba) {
     ostringstream ss;
     ss << liczba;
     return ss.str();
}
void Dzien::przypiszCel(Cel* c) {
    time_t ten=0;
    #ifdef DEBUG
        cout << this->data.tm_hour << endl;
        cout << this->data.tm_isdst<< endl;
        cout << this->data.tm_mday<< endl;
        cout << this->data.tm_min << endl;
        cout << this->data.tm_mon << endl;
        cout << this->data.tm_sec << endl;
        cout << this->data.tm_wday << endl;
        cout << this->data.tm_yday<< endl;
        cout << this->data.tm_year << endl;
    #endif // DEBUG
    ten = mktime(&this->data);
    #ifdef DEBUG
        cout << "czas w time_t z danego dnia" << ten << endl;
    #endif // DEBUG
    if(ten >= c->start && ten <= c->koniec)
    {
        #ifdef DEBUG
            cout << "przypisano." << endl;
            c->pokaz();
        #endif // DEBUG
        this->cele.push_back(*c);
    }
}
void Dzien::zmienStan(Cel* c) {
    c->setStan();
}
string Dzien::strData() {
    string rok = toString(this->data.tm_year+1900);
    string miech = toString(this->data.tm_mon+1);
    string dzien = toString(this->data.tm_mday);
    string path = rok + "\\" + miech + "\\" + dzien + ".txt";
    return path;
}
void Dzien::zapisz() {
    string rok = toString(this->data.tm_year+1900);
    string miech = toString(this->data.tm_mon+1);
    string dzien = toString(this->data.tm_mday);
    string folder = "mkdir " + rok + "\\" + miech;
    system(folder.c_str());
    string path = rok + "\\" + miech + "\\" + dzien + ".txt";
    ofstream zapis(path.c_str(), ios::app);
    for(int i=this->cele.size()-1; i < this->cele.size(); i++) {
        cele[i].zapisz(&zapis);
    }
    zapis.close();
}
void Dzien::nadpisz() {
    string rok = toString(this->data.tm_year+1900);
    string miech = toString(this->data.tm_mon+1);
    string dzien = toString(this->data.tm_mday);
    string path = rok + "\\" + miech + "\\" + dzien + ".txt";
    ofstream zapis(path.c_str(), ios::out);
    for(int i=0; i < this->cele.size(); i++) {
        cele[i].zapisz(&zapis);
    }
    zapis.close();
}
bool Dzien::odczytaj() {
    string rok = toString(this->data.tm_year+1900);
    string miech = toString(this->data.tm_mon+1);
    string dzien = toString(this->data.tm_mday);
    string path = rok + "/" + miech + "/" + dzien + ".txt";
    ifstream odczyt(path.c_str());
    Cel *c;
    if(odczyt.good()) {
        while(!odczyt.eof()) {
            c = new Cel();
            c->odczytaj(&odczyt);
            this->cele.push_back(*c);
            delete c;
        }
        odczyt.close();
        return true;
    }
    else {
        odczyt.close();
        return false;
    }
}
void Dzien::wyswietlCele() {
    for(int i=0; i < this->cele.size(); i++) {
        if(this->cele[i].tytul == "") break;
        cout << endl << endl;
        cout << "CEL: "<< i+1 << endl;
        cele[i].pokaz();
    }
}
