#ifndef POI_H
#define POI_H
#include"ort.h"


class Poi:public Ort
{
public:
    Poi(const double Längengrad,const double Breitengrad,string Name,string Parameter);

    string getName() const;

    string getParameter() const;

private:
    string Name;
    string Parameter;

};

#endif // POI_H
