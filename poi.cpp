#include "poi.h"
#include"ort.h"
Poi::Poi(const double Längengrad, const double Breitengrad, string Name, string Parameter):Ort(Längengrad,Breitengrad),Name(Name),Parameter(Parameter)
{

}

string Poi::getName() const
{
    return Name;
}

string Poi::getParameter() const
{
    return Parameter;
}


