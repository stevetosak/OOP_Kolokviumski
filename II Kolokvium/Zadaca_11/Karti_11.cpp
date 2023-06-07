#include<iostream>
#include<cstring>
using namespace std;
class Delo{
private:
    char name[64];
    int year;
    char countryOrigin[64];
public:
    Delo(char* ime = "", int year = 69, char* zemja =""){
        strcpy(this->name,ime);
        strcpy(this->countryOrigin,zemja);
        this->year = year;
    }
    bool operator == (const Delo& d){
       return !strcmp(this->name,d.name);
    }
    char* getIme(){
        return name;
    }
    friend class Pretstava;
};
int myStrtoi(char* str){
    int num = 0;
    int n = 1;
    for(int i = strlen(str) - 4;i < strlen(str); i++){
        num = num + ((str[i] - '0') * (1000/n));
        n*=10;
    }
    return num;
};
class Pretstava{
protected:
    Delo delo;
    int soldTickets;
    char date[16];
public:
    Pretstava(Delo d, int tickets, char* date){
        this-> delo = d;
        this->soldTickets = tickets;
        strcpy(this->date,date);
    }
    Delo& getDelo(){
        return delo;
    }
    virtual int cena(){
        int m,n;
        if(delo.year/100 == 20 || delo.year/100 == 19){
            m = 50;
        }
        else if(delo.year/100 == 18){
            m = 75;
        }
        else{
            m = 100;
        }

        if(!strcmp(this->delo.countryOrigin,"Italija")){
            n = 100;
        }
        else if(!strcmp(this->delo.countryOrigin,"Rusija")){
            n = 150;
        }
        else{
            n = 80;
        }
        return m + n;
    }
    friend int brojPretstaviNaDelo(Pretstava** pretstavi, int n, Delo& d);
    friend int prihod(Pretstava** pretstavi, int n);
};
class Balet :public Pretstava{
private:
    static int price;
public:
    Balet(Delo d, int tickets, char* date) : Pretstava(d,tickets,date){}
    static void setCenaBalet(int newPrice){
        Balet::price = newPrice;
    }
    int cena(){
        return Pretstava::cena() + price;
    }

};

class Opera :public Pretstava{
public:
    Opera(Delo d, int tickets, char* date) : Pretstava(d,tickets,date){}
};



int prihod(Pretstava** pretstavi, int n){
    int total = 0;
    for(int i = 0; i < n; i++){
        total += pretstavi[i]->cena() *  pretstavi[i]->soldTickets;

    }
    return total;
}

int brojPretstaviNaDelo(Pretstava** pretstavi, int n, Delo& d){
    int total = 0;
    for(int i = 0; i < n; i++){
        if(pretstavi[i]->delo == d){
            total ++;
        }
    }
    return total;
}

int Balet::price = 150;

//место за вашиот код


//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
