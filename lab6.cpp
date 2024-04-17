#include <iostream>
#include <string>
#include <vector>

using namespace std;

class KontoBankowe{
private:
    string numer;
    double saldo;
    int debet;
public:
    KontoBankowe(string numer = "<brak_danych>",double saldo = 0.0, int debet = 0) : numer(numer), saldo(saldo), debet(debet){}

    void sprawdzStan(){
        cout << "Numer konta: " << this->numer << endl;
        cout << "Saldo: " << this->saldo << " PLN" << endl;
        cout << "Debet: " << this->debet << " PLN" << endl;
    }
    void wyplac(double ile){
        this->saldo -= ile;
        cout << "Wyplacono " << ile << " PLN " << endl;
        cout << "Stan konta: " << this->saldo << endl;
    }
    void wplac(double ile) {
        this->saldo += ile;
        cout << "Wplacono " << ile << " PLN." << endl;
        cout << "Stan konta: " << this->saldo << endl;
    }
    void zmianaDebetu(int nowyDebet){
        this->debet = nowyDebet;
        cout << "Zmieniono debet na " << nowyDebet << " PLN." << endl;
    }
    void przelew(KontoBankowe cel,double ile){
        if (saldo >= ile) {
            wyplac(ile);
            cel.wplac(ile);
            cout << "Wykonano przelew na kwote " << ile << " PLN." << endl;
        } else {
            cout << "Brak wystarczających srodkow do wykonania przelewu." << endl;
        }
    }
    double getSaldo(){
        return saldo;
    }

};

class Klient{
private:
    KontoBankowe konto;
    string pesel;
    string imie_nazwisko;
public:
    Klient(KontoBankowe konto, string pesel = "<bark danych>", string imie_nazwisko = "<bark danych>") : konto(konto), pesel(pesel), imie_nazwisko(imie_nazwisko){}

    KontoBankowe getKonto(){
        return konto;
    }

    KontoBankowe stanKontaKlienta(Klient klient){
        return klient.getKonto();
    }

    void wypiszDane(){
        cout << "PESEL: " << this->pesel << endl;
        cout << "Imie i nazwisko: " << this->imie_nazwisko << endl;
        this->konto.sprawdzStan();
        cout << endl;
    }
};

bool czy_saldo_ujemne(KontoBankowe konto){
    return konto.getSaldo() < 0;
}

int main(){


    KontoBankowe konto1("12345", 1500.0);
    KontoBankowe konto2("23344", -500.0, 200);
    KontoBankowe konto3("43567", 3000.0, 1000);

    Klient klient1(konto1, "12234667801", "Jan Kowalski");
    Klient klient2(konto2, "98766252310", "Bob Nowak");
    Klient klient3(konto3, "55555323559", "Adam Smith");

    vector<Klient> bazadanych = {klient1,klient2,klient3};

    klient1.getKonto().przelew(klient2.getKonto(),100);

    cout << "Stan konta dla kazdego klienta:" << endl;
    for (auto klient : bazadanych) {
        klient.wypiszDane();
    }

    cout << "Klienci posiadajacy ujemne saldo:" << endl;
    for (auto klient : bazadanych) {
        if (czy_saldo_ujemne(klient.getKonto())) {
            klient.wypiszDane();
        }
    }

    return 0;
};
