#ifndef ADRESSE_H
#define ADRESSE_H

#include"ort.h"

class Adresse:public Ort
{
public:
    Adresse(const double Längengrad,const double Breitengrad,string Name,string Parameter);


    string getName() const;

    string getParameter() const;

private:
    string Name;
    string Parameter;


};

#endif // ADRESSE_H
