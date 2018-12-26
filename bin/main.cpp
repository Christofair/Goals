#include "../Aplication.hpp"
#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>

using namespace std;


int main(){
    Aplikacja* app;
    app = Aplikacja::getInstance();
    char wybor=0;
    bool stage = false;
    bool zamknij = false;
    int ktory_cel;
while(!zamknij){
    cin.sync();
    system("cls");
    app->viewDzien(app->dzien);
    app->dzien->cele.clear();
    stage = (app->dzien->odczytaj())? true : false;
    if(!stage) cout << "Nie znaleziono pliku :/" << endl;
    else app->dzien->wyswietlCele();

    cout << endl << endl;
    cout << "0. zamyka" << endl;
    cout << "1. ustaw dzien" << endl;
    cout << "2. dodaj cel" << endl;
    cout << "3. zmien stan" << endl;
    cout << "4. usun cel" << endl;
    cout << "Strzalki boczne przesuwaja dni :D" << endl;
    wybor = getch();
    switch(wybor)
    {
    case '1':
        uint32_t nr_day, nr_miech, nr_rok;
        cout << "podaj numer dnia w miesiacu: "; cin >> nr_day;
        cout << "podaj numer miesiaca: "; cin >> nr_miech;
        cout << "podaj numer roku: "; cin >> nr_rok;
        app->setDzien(nr_day, nr_miech, nr_rok);
        break;
    case '2':
        app->setCel();
        app->zapiszCel();
        break;
    case '3':
        if(app->nieMozliwa()){
            cout << "Operacja niemozliwa, poniewaz ten dzien dopiero nastapi :'D" << endl;
        }
        else {
            cout << endl << endl;
            cout << "Podaj ktory cel chcesz zmienic: ";
            cin >> ktory_cel;
            app->dzien->cele[ktory_cel-1].setStan();
            app->dzien->cele[ktory_cel-1].pokaz();
            app->dzien->nadpisz();
            cout << endl << endl;
        }
        break;
    case '4': {
        Cel *postanowienie;
        cout << endl << endl;
        cout << "Podaj ktory cel chcesz zmienic: ";
        cin >> ktory_cel;
        postanowienie = new Cel();
        postanowienie->start = app->dzien->cele[ktory_cel-1].start;
        postanowienie->koniec = app->dzien->cele[ktory_cel-1].koniec;
        postanowienie->tytul = app->dzien->cele[ktory_cel-1].tytul;
        app->usunCel(postanowienie);
        delete postanowienie;
    }
        break;
    case 224: case 0: {
        tm obecny;
        time_t must_be;
        case 77: {
            if(app->dzien != nullptr){
                must_be = mktime(&app->dzien->data);
                delete app->dzien;
            }
            must_be += (3600*24);
            obecny = *(localtime(&must_be));
            app->setDzien(obecny.tm_mday, obecny.tm_mon+1, obecny.tm_year+1900);
        }
            break;
        case 75: {
             if(app->dzien != nullptr){
                must_be = mktime(&app->dzien->data);
                delete app->dzien;
            }
            must_be -= (3600*24);
            obecny = *(localtime(&must_be));
            app->setDzien(obecny.tm_mday, obecny.tm_mon+1, obecny.tm_year+1900);
        }
            break;
    }
    break;
    case '0': case 27:
        zamknij = true;
        break;
    }
}
    delete app;
    Aplikacja::usunInstancje();
    return 0;
}
