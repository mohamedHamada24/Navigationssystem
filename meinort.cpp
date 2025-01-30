#include "meinort.h"

MeinOrt::MeinOrt(double Länge, double Breite, string Name, string Parameter):Länge(Länge),Breite(Breite),Name(Name),Parameter(Parameter)
{




}

double MeinOrt::getBreite() const
{
    return Breite;
}

double MeinOrt::getLänge() const
{
    return Länge;
}

string MeinOrt::getName() const
{
    return Name;
}

string MeinOrt::getParameter() const
{
    return Parameter;
}

int MeinOrt::getId() const
{
    return Id;
}

bool MeinOrt::getAktiv() const
{
    return aktiv;
}

void MeinOrt::setAktiv(bool newAktiv)
{
    aktiv = newAktiv;
}
