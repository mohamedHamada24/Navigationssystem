#include "adresse.h"
#include"ort.h"

Adresse::Adresse(const double Längengrad, const double Breitengrad, string Name, string Parameter):Ort(Längengrad,Breitengrad), Name(Name), Parameter(Parameter)
{


}

string Adresse::getName() const
{
    return Name;
}

string Adresse::getParameter() const
{
    return Parameter;
}

