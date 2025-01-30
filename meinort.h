#ifndef MEINORT_H
#define MEINORT_H
#include<iostream>
using namespace std;

class MeinOrt
{
public:
    MeinOrt(double Länge, double Breite, string Name, string Parameter);
    double getBreite() const;

    double getLänge() const;

    string getName() const;

    string getParameter() const;

    int getId() const;

    bool getAktiv() const;
    void setAktiv(bool newAktiv);

private:
    double Länge,Breite;
    string Name,Parameter;
    bool aktiv=false;
    int Id=0;


};

#endif // MEINORT_H
