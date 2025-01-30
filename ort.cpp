#include "ort.h"
#include<iostream>
int Ort::counter=1;



Ort::Ort(double Längengrad, double Breitengrad):Längengrad(Längengrad),Breitengrad(Breitengrad)
{
    Id=counter;
    counter++;

}


double Ort::getLängengrad() const
{
    return Längengrad;
}



double Ort::getBreitengrad() const
{
    return Breitengrad;
}



int Ort::getId() const
{
    return Id;
}

