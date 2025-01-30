#include "navigationsverwaltung.h"
#include"ort.h"
#include"adresse.h"
#include"poi.h"
#include"meinort.h"
#include<iomanip>
#include<cmath>
#include<vector>

#include<fstream>
#include<sstream>

Navigationsverwaltung::Navigationsverwaltung()
{


}

Navigationsverwaltung::~Navigationsverwaltung()
{
    for(auto it:Orte){
        delete it;
    }
    for(auto it:Meinort){
        delete it;
    }
}

void Navigationsverwaltung::benutzerDialog()
{
    AktuellePosition();

    while(true){
        cout<<"Navigationssystem: "<<endl;
        cout<<"1: Ort anlegen"<<endl;
        cout<<"2: Karte anzeigen"<<endl;
        cout<<"3: Entfernung berechnen"<<endl;
        cout<<"4: karte speichern/laden"<<endl;
        cout<<"0: Programm beenden"<<endl;
        cout<<"Geben Sie bitte den Auswahl ein"<<endl;
        char choice;
        cin>>choice;
        switch(choice){
        case('1'):{
            cout<<"Möchten Sie eine Adresse (1) oder einen Point of Interess(2)"<<endl;
            char choice;
            cin>>choice;
            if(choice=='1'){
                Ortanlegenadresse();
                break;

            }
            else if(choice=='2'){
                Ortanlegenpoi();

                break;


            }
            else{
                cout<<"Ungültige Eingabe"<<endl;
            }
            break;




        }
        case('2'):{
            Karteanzeigen();
            break;




        }
        case('3'):{

            MeinOrt* ort1 = nullptr;
            Ort* ort2 = nullptr;

            if (Orte.empty()) {
                cout << "Keine ausreichenden Orte" << endl;
                break;
            } else {
                cout << "Geben Sie den Id des Orts" << endl;
                Karteanzeigen();
                bool found = false;
                cout << "Geben Sie die Ids von den Orten" << endl;
                int Id1, Id2;
                cin >> Id1;
                cin >> Id2;
                for (auto pos : Meinort) {
                    if (pos->getId() == Id1) {
                        ort1 = pos;

                    }
                }

                for (auto ort : Orte) {
                    if (ort->getId() == Id2) {
                        ort2 = ort;
                    }

                }

                if (ort1 == nullptr || ort2 == nullptr) {
                    cout << "Falsche Eingabe" << endl;
                    break;
                }
                cout << "Distanz: " << berechnungvonentfernung(ort1, ort2) << endl;
            }

            break;
        }





        case('4'):{
            cout<<"1: Speicehrn 2: Laden"<<endl;
            char choice;
            cin>>choice;
            if(choice=='1'){
                Kartespeichern();
                break;

            }
            else if(choice=='2'){
                Karteladen();
                break;

            }
            break;

        }
        case('0'):{
            cout<<"Sie wollen uns verlassen"<<endl;
            return;

        }
        }
    }


}

void Navigationsverwaltung::Ortanlegenadresse()
{
    double Längen,Breite;
    string Name,Parameter;
    cout<<"Geben Sie bitte die Länge ein"<<endl;
    cin>>Längen;
    cout<<"Geben Sie bitte die Breite ein"<<endl;
    cin>>Breite;
    cout<<"Geben Sie bitte die Name"<<endl;
    cin.ignore();

    getline(cin,Name);
    cout<<"Geben Sie bitte die Parameter"<<endl;
    cin.ignore();
    getline(cin,Parameter);
    Ort*adresse=new Adresse(Längen,Breite,Name,Parameter);
    Orte.push_back(adresse);
    cout<<"Adresse wird angelegt mit dem Nummer: "<<adresse->getId()<<endl;

}

void Navigationsverwaltung::Ortanlegenpoi()
{
    double Länge,Breite;
    cout<<"Geben Sie bitte die Länge ein"<<endl;
    cin>>Länge;
    cout<<"Geben Sie bitte die Breite ein"<<endl;
    cin>>Breite;
    string Name,Parameter;
    cout<<"Geben Sie bitte die Name ein"<<endl;
    cin.ignore();
    getline(cin,Name);
    cout<<"Geben Sie bitte die Parameter ein"<<endl;
    cin.ignore();
    getline(cin,Parameter);

    Ort*poi=new Poi(Länge,Breite,Name,Parameter);
    Orte.push_back(poi);
    cout<<"Point of Interess wird angelegt: "<<poi->getId()<<endl;

}

void Navigationsverwaltung::Karteanzeigen()
{
    cout<<left<<setw(10)<<"ID:"
         <<setw(20)<<"Typ:"
         <<setw(20)<<"Breitengrad:"
         <<setw(20)<<"Längengrad: "
         <<setw(20)<<"Name: "
         <<setw(20)<<"Parameter: "<<endl;
    for(auto it :Meinort){



        cout<<left<<setw(10)<<it->getId()
             <<setw(20)<<"Aktuelle Pos"
             <<setw(20)<<it->getBreite()
             <<setw(20)<<it->getLänge()
             <<setw(20)<<it->getName()
             <<setw(20)<<it->getParameter()<<endl;





    }



    for(Ort*ort:Orte){
        if(auto adr=dynamic_cast<Adresse*>(ort)){
            cout<<left<<setw(10)<<adr->getId()
                 <<setw(20)<<"Adresse"
                 <<setw(20)<<adr->getBreitengrad()
                 <<setw(20)<<adr->getLängengrad()
                 <<setw(20)<<adr->getName()
                 <<setw(20)<<adr->getParameter()<<endl;



        }
        else if(auto poi=dynamic_cast<Poi*>(ort)){


            cout<<left<<setw(10)<<poi->getId()
                 <<setw(20)<<"POI"
                 <<setw(20)<<poi->getBreitengrad()
                 <<setw(20)<<poi->getLängengrad()
                 <<setw(20)<<poi->getName()
                 <<setw(20)<<poi->getParameter()<<endl;

        }
    }

}


void Navigationsverwaltung::Karteladen()
{
    ifstream datei("Kartenavi.txt");
    if (!datei) {
        cerr << "Fehler beim Öffnen der Datei" << endl;
        return;
    }

    Orte.clear();
    string line;

    while (getline(datei, line)) {
        if (line == "Adresse:") {
            double längengrad, breitengrad;
            string Name, Parameter;

            datei.ignore(256, ':'); datei >> längengrad;
            datei.ignore(256, ':'); datei >> breitengrad;
            datei.ignore(256, ':'); getline(datei, Name);
            datei.ignore(256, ':'); getline(datei, Parameter);
            Ort* adresse = new Adresse(längengrad, breitengrad, Name,Parameter);
            Orte.push_back(adresse);
        } else if (line == "Poi:") {
            double längengrad, breitengrad;
            string Name, Parameter;
            datei.ignore(256, ':'); datei >> längengrad;
            datei.ignore(256, ':'); datei >> breitengrad;
            datei.ignore(256, ':'); getline(datei, Name);
            datei.ignore(256, ':'); getline(datei, Parameter);
            Ort* poi = new Poi(längengrad, breitengrad,Name ,Parameter );
            Orte.push_back(poi);
        }
    }

    datei.close();
    //cout << "Karte wird geladen" << endl;
}

void Navigationsverwaltung::Kartespeichern()
{
    cout<<"Karte speichern "<<endl;
    ofstream datei("Kartenavi.txt");
    if(!datei){
        cerr<<"Fehler bei der Öffnung"<<endl;
    }


    for(Ort*ort:Orte){
        if(auto adresse=dynamic_cast<Adresse*>(ort)){
            datei<<"Adresse:"<<endl;
            datei<<"Längengrad:"<<adresse->getLängengrad()<<endl;
            datei<<"Breitengrad:"<<adresse->getBreitengrad()<<endl;
            datei<<"Name:"<<adresse->getName()<<endl;
            datei<<"Parameter:"<<adresse->getParameter()<<endl;
        }
        else if(auto poi=dynamic_cast<Poi*>(ort)){
            datei<<"Poi: "<<endl;
            datei<<"Längengrad: "<<poi->getLängengrad()<<endl;
            datei<<"Breitengrad: "<<poi->getBreitengrad()<<endl;
            datei<<"Name: "<<poi->getName()<<endl;
            datei<<"Parameter: "<<poi->getParameter()<<endl;
        }




    }
    datei.close();
    //cout<<"Karte wurde gespeichert"<<endl;

}

void Navigationsverwaltung::AktuellePosition()
{
    cout<<"Möchten Sie ihre aktuelle Position eingeben "<<endl;

    char choice;
    cin>>choice;
    switch(choice){
    case('j'):{
        if(!Meinort.empty()){
            Meinort.clear();
        }





        double Längen,Breiten;
        string Name,Parameters;
        cout<<"Geben Sie bitte Längengrade ein"<<endl;
        cin>>Längen;
        cout<<"Geben Sie bitte Breitengrad ein"<<endl;
        cin>>Breiten;
        cout<<"Geben Sie bitte die Name ein"<<endl;
        cin.ignore();
        getline(cin,Name);
        cout<<"Geben Sie bitte die Parameters ein"<<endl;
        cin.ignore();
        getline(cin,Parameters);
        MeinOrt*aktuelle=new MeinOrt(Längen,Breiten,Name,Parameters);
        Meinort.push_back(aktuelle);
        aktuelle->setAktiv(true);
        cout<<"ur Position is in the vector"<<endl;
        for(auto it:Meinort){

            cout<<"Längen: "<<it->getLänge()<<setw(15)
                 <<"Breiten: "<<it->getBreite()<<setw(15)
                 <<"Name: "<<it->getName()<<setw(15)
                 <<"Parameter: "<<it->getParameter()<<endl;

        }


        break;



    }
    case('n'):{

        cout<<"Die Adresse von h-da wurde benutzt als Ihre aktuelle Position"<<endl;
        MeinOrt*position=new MeinOrt(8.639912 , 49.86682, "h-da", "Hochschule, Bildungseinrichtung");
        Meinort.push_back(position);
        position->setAktiv(false);
        for(auto it:Meinort){
            cout<<"Längen: "<<it->getLänge()<<setw(15)
                 <<"Breiten: "<<it->getBreite()<<setw(15)
                 <<"Name: "<<it->getName()<<setw(15)
                 <<"Parameter: "<<it->getParameter()<<endl;
        }
        break;


    }
    default:{
        cout<<"Ungültige Eingabe"<<endl;
        break;

    }

    }




}

vector<Ort *> &Navigationsverwaltung::getOrte()
{
    return Orte;
}

vector<MeinOrt *> &Navigationsverwaltung::getMeinort()
{
    return Meinort;
}
double Navigationsverwaltung::berechnungvonentfernung(MeinOrt* pos ,Ort*ort2)
{


    double lag1=doubletoradians(pos->getLänge());
    double bre1=doubletoradians(pos->getBreite());
    double lag2=doubletoradians(ort2->getLängengrad());
    double bre2=doubletoradians(ort2->getBreitengrad());
    double difbe=lag2-lag1;
    double difla=bre2-bre1;
    double a =sin(difla / 2) * sin(difla / 2) +cos(lag1) *cos(lag2) *sin(difbe / 2) * sin(difbe/ 2);

    double c=2*atan2(sqrt(a),sqrt(1-a));
    double distanz= R*c  ;
    return distanz;



}

double Navigationsverwaltung::doubletoradians(double degree)
{
    return degree*(M_PI/180.0);
}
