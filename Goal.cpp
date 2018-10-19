#include "Goal.hpp"
#include <fstream>
#include <ctime>
#include <iostream>


using namespace std;

Cel::Cel() : tytul(""), opis(""), start(0), koniec(0), stan(ST_NZROBIONE){ /* ... */ }
void Cel::setTermin() {
    tm data;
    data = {0,0,0,0,0,0,0,0,0};
    cout << "Poczatek obowiazywania celu: " << endl;
    cout << "Podaj dzien: ";
    cin >> data.tm_mday;
    cout << "Podaj numer miesiaca: ";
    cin >> data.tm_mon;
    data.tm_mon-=1;
    cout << "Podaj rok: ";
    cin >> data.tm_year;
    data.tm_year-=1900;
    this->start = mktime(&data);
    #ifdef DEBUG
        cout << data.tm_hour << endl;
        cout << data.tm_isdst<< endl;
        cout << data.tm_mday<< endl;
        cout << data.tm_min << endl;
        cout << data.tm_mon << endl;
        cout << data.tm_sec << endl;
        cout << data.tm_wday << endl;
        cout << data.tm_yday<< endl;
        cout << data.tm_year << endl;
        cout << "start w time_t: " << this->start << endl;
    #endif // DEBUG

    cout << "Koniec obowiazywania celu: " << endl;
    cout << "Podaj dzien: ";
    cin >> data.tm_mday;
    cout << "Podaj numer miesiaca: ";
    cin >> data.tm_mon;
    data.tm_mon-=1;
    cout << "Podaj rok: ";
    cin >> data.tm_year;
    data.tm_year-=1900;
    this->koniec = mktime(&data);
    #ifdef DEBUG
        cout << data.tm_hour << endl;
        cout << data.tm_isdst<< endl;
        cout << data.tm_mday<< endl;
        cout << data.tm_min << endl;
        cout << data.tm_mon << endl;
        cout << data.tm_sec << endl;
        cout << data.tm_wday << endl;
        cout << data.tm_yday<< endl;
        cout << data.tm_year << endl;
        cout << "koniec w time_t: " << this->koniec << endl;
    #endif //DEBUG
}
void Cel::setOpis() {
    cout << "wpisz opis" << endl;
    getline(cin, this->opis);
}
void Cel::setTytul() {
    cout << "wpisz tytul" << endl;
    getline(cin, this->tytul);
}
void Cel::setStan() {
    unsigned liczba;
    cout << "Aby ustawic stan zrobione wpisz 0" << endl;
    cout << "Aby ustawic stan nie zrobione wpisz 1" << endl;
    cout << "Aby ustawic stan zrobione tak 2/10 wpisz 2" << endl;
    cout << "Aby ustawic stan nieobowiazuje w danym dniu wpisz 3" << endl;
    cin >> liczba;
    if(liczba > 3 || liczba < 0) cout << "blad podano zly stan" << endl;
    else this->stan = static_cast <STANY> (liczba);
}
void Cel::getStan() {
    switch(this->stan) {
        case ST_ZROBIONE: cout << "Zadanie zrobione" << endl; break;
        case ST_NZROBIONE: cout << "Zadanie nie zrobione" << endl; break;
        case ST_SREDNIO: cout << "Zadanie zrobione tak 2na10 :'D" << endl; break;
        case ST_NOBOWIAZUJE: cout << "Zadanie nie obowi¹zuje w danym dniu" << endl; break;
        default: cout << "NIE USTALONO STANU" << endl;
    }
}
void Cel::zapisz(ofstream *plik) {
    *plik << endl << this->tytul << endl;
    *plik << this->opis << endl;
    *plik << this->start << endl;
    *plik << this->koniec << endl;
    *plik << this->stan;
}
void Cel::odczytaj(ifstream *plik) {
    int liczba;
    string pusta_linia;
    getline(*plik, pusta_linia);
    getline(*plik, this->tytul);
    getline(*plik, this->opis);
    *plik >> this->start;
    *plik >> this->koniec;
    *plik >> liczba;
    this->stan = static_cast <STANY> (liczba);
}
void Cel::pokaz() {
    string dni_tygodnia[] = {"Niedziela", "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota"};
    string nazwy_miesiecy[] = {"Styczen","Luty","Marzec",
        "Kwiecien","Maj","Czerwiec",
        "Lipiec","Sierpien","Wrzesien",
        "Pazdziernik","Listopad","Grudzien"};
    #ifdef DEBUG
        cout << "start: " << this->start << endl;
        cout << "koniec: " << this->koniec << endl;
    #endif // DEBUG
    tm czasP = *(localtime(&this->start));
    tm czasK = *(localtime(&this->koniec));
    cout << "tytul: " << this->tytul << endl;
    cout << "opis: " << this->opis << endl;
    cout << "poczatek: " << dni_tygodnia[czasP.tm_wday] << ", " << czasP.tm_mday << " " << nazwy_miesiecy[czasP.tm_mon] << " " << czasP.tm_year+1900 << endl;
    cout << "koniec: " << dni_tygodnia[czasK.tm_wday] << ", " << czasK.tm_mday << " " << nazwy_miesiecy[czasK.tm_mon] << " " << czasK.tm_year+1900 << endl;
    cout << "STAN: "; this->getStan();
}
//void cel::zapiszStan(string, int) is deprecated
void Cel::zapiszStan(string nazwa_pliku, int ktory) {
    ifstream plikO(nazwa_pliku.c_str());
    ofstream plikZ;
    string empty_line;
    string seek[4];
    getline(plikO, empty_line);
    for(int i=0; i<4; i++) {
        getline(plikO, seek[i]);
    }
    ios::pos_type pozycja = plikO.tellg();
    plikO.close();
    plikZ.open(nazwa_pliku.c_str(), ios::app);
    plikZ.seekp(pozycja);
    plikZ << '\b';
    plikZ << this->stan; //niejawna konwersja na liczbe, wszystko powinno dzialac
    plikZ.close();
}
