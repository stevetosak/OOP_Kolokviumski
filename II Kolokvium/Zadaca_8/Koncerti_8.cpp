#include <iostream>
#include <cstring>
using namespace std;
class Koncert{
protected:
    char name[20];
    char location[20];
    static double seasonalDiscount;
    double price;
public:

    Koncert(char* name, char* location, double price){
        strcpy(this->name,name);
        strcpy(this->location,location);
        this->price = price;
    }
    char* getNaziv(){
        return name;
    }
    static double getSezonskiPopust(){
        return double(seasonalDiscount);
    }
    static void setSezonskiPopust(double newDiscount){
        seasonalDiscount = newDiscount;
    }

    virtual double cena(){
        return (double)price - (price * seasonalDiscount);
    }
};

class ElektronskiKoncert : public Koncert{
private:
    char* DJname = new char [0];
    double duration;
    bool isDayParty; //day == true, night == false
public:
    //ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
    ElektronskiKoncert(char* name, char* location, double price, char* djName, double duration, bool IsDay) : Koncert(name,location,price){
        this->DJname = new char[strlen(djName) +1];
        strcpy(this->DJname,djName);
        this->duration = duration;
        this->isDayParty = IsDay;
    }
    ElektronskiKoncert(const ElektronskiKoncert& other) : Koncert((Koncert&) other){
        copy(other,true);
    }
    ElektronskiKoncert& operator = (const ElektronskiKoncert& other){
        if(this != &other){
            delete [] DJname;
            copy(other,false);
            return *this;
        }
        return *this;
    }
    double cena(){
        double total = Koncert::cena();
        if(duration > 7){
            total += 360;
        }
        else if(duration > 5){
            total += 150;
        }
        if(isDayParty){
            total -=50;
        }
        else{
            total += 100;
        }
        return total;
    }

private:
    void copy(const ElektronskiKoncert& other, bool inConstr){
        if(inConstr){
            this->DJname = new char[strlen(other.DJname) +1];
            strcpy(this->DJname,other.DJname);
            this->isDayParty = other.isDayParty;
        }
        else{
            this->DJname = new char[strlen(other.DJname) +1];
            strcpy(this->DJname,other.DJname);
            this->isDayParty = other.isDayParty;
            strcpy(this->name,other.name);
            strcpy(this->location,other.location);
            this->price = other.price;
        }
    }

};

void najskapKoncert(Koncert ** koncerti, int n){
    int numElectronic = 0;
    double max = 0; // koncerti[0]->cena;
    int memID = -1;
    for(int i = 0; i < n; i++){
        if(dynamic_cast <ElektronskiKoncert*> (koncerti[i])){
            numElectronic ++;
            if(koncerti[i]->cena() > max){
                max = koncerti[i]->cena();
                memID = i;
            }
        }
    }

    cout << "Najskap koncert: " << koncerti[memID]->getNaziv() << " " << koncerti[memID]->cena() << endl;
    cout << "Elektronski koncerti: " << numElectronic << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * naziv, bool elektronski){
    if(elektronski){
        for(int i = 0; i < n; i++){
            if(dynamic_cast <ElektronskiKoncert*> (koncerti[i])){
                if(!strcmp(koncerti[i]->getNaziv(),naziv)){
                    cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                    return true;
                }
            }
        }
        return false;
    }
    else{
        for(int i = 0; i < n; i++){
            if(!strcmp(koncerti[i]->getNaziv(),naziv)){
                cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                return true;
            }
        }
        return false;
    }
}

double Koncert::seasonalDiscount = 0.2;

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
