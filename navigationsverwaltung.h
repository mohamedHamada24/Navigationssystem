#ifndef NAVIGATIONSVERWALTUNG_H
#define NAVIGATIONSVERWALTUNG_H
#include<iostream>
#include<vector>
#include<ort.h>
#include<meinort.h>
using namespace std;

class Navigationsverwaltung
{
public:
    Navigationsverwaltung();
    ~Navigationsverwaltung();
    const double R=6371.0;
    double doubletoradians(double degree);
    double berechnungvonentfernung(MeinOrt *ort1, Ort *ort2);

    void benutzerDialog();
    void Ortanlegenadresse();
    void Ortanlegenpoi();
    void Karteanzeigen();
    void Karteladen();
    void Kartespeichern();
    void AktuellePosition();
    vector<Ort *> &getOrte();

    vector<MeinOrt *> &getMeinort() ;

protected:
    vector<Ort*>Orte;
    vector<MeinOrt*>Meinort;
};

#endif // NAVIGATIONSVERWALTUNG_H
