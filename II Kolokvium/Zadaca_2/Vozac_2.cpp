// vashiot kod ovde
#include <iostream>
#include <cstring>
using namespace std;
class Vozac{
protected:
    char name[100];
    int age;
    int numRaces;
    bool isVeteran;
public:
    Vozac(char* name, int age, int numRaces, bool veteran){
        strcpy(this->name,name);
        this->age = age;
        this->numRaces = numRaces;
        this->isVeteran = veteran;
    }
    friend ostream& operator << (ostream& os, Vozac& v);
    virtual float zarabotuvacka() = 0;
    virtual float danok() = 0;
    bool operator == (Vozac& other){
        return (this->zarabotuvacka() == other.zarabotuvacka());
    }
    virtual ~Vozac(){}

};
class Avtomobilist : public Vozac{
private:
    float price;
public:
    //Avtomobilist(ime, vozrast, trki, vet, cena_avto);
    Avtomobilist(char* name, int age, int numRaces, bool veteran, float price) : Vozac(name,age,numRaces,veteran){
        this->price = price;
    }
    float zarabotuvacka(){
        return (float)price/5.0;
    }
    float danok(){
        if(numRaces > 10){
            return (float)zarabotuvacka() * 0.15;
        }
        else{
            return (float)zarabotuvacka() * 0.10;
        }
    }

};
class Motociklist : public Vozac{
private:
    int HP;
public:
    Motociklist(char* name, int age, int numRaces, bool veteran, int HP) : Vozac(name,age,numRaces,veteran){
        this->HP = HP;
    }
    float zarabotuvacka(){
        return HP * 20;
    }
    float danok(){
        if(isVeteran){
            return (float)zarabotuvacka() * 0.25;
        }
        else{
            return (float)zarabotuvacka() * 0.2;
        }
    }
};
int soIstaZarabotuvachka(Vozac** vozaci,int num,Vozac* schumi){
    int total = 0;
    for(int i = 0; i < num; i++){
        if(*vozaci[i] == *schumi){
            total ++;
        }
    }
    return total;
}
ostream& operator <<(ostream& os, Vozac& v){
    os << v.name << endl << v.age << endl << v.numRaces << endl << (v.isVeteran ? "VETERAN\n":"");
    return os;
}
int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}