#include <iostream>
#include <cstring>
using namespace std;

class Transport{
protected:
    char destination[64];
    int basePrice;
    int distanceToDest;
public:
    Transport(char* destination, int price, int distance){
        strcpy(this->destination,destination);
        this->basePrice = price;
        this->distanceToDest = distance;
    }
    bool operator < (Transport& other){
        return this->distanceToDest < other.distanceToDest;
    }
    virtual float cenaTransport() = 0;
    char* getDestination(){
        return destination;
    }
    int getDistance(){
        return distanceToDest;
    }

    friend void pecatiPolosiPonudi(Transport** ponudi,int n,Transport& T);
};

class AvtomobilTransport : public Transport{
private:
    bool hasPaidDriver;
public:
    AvtomobilTransport(char* destination, int price, int distance, bool shofer) : Transport(destination,price,distance){
        this->hasPaidDriver = shofer;
    }
    float cenaTransport() override{
        if(hasPaidDriver){
            return basePrice * 1.2;
        }
        else{
            return basePrice;
        }
    }
};

class KombeTransport : public Transport{
private:
    int capacity;
public:
    KombeTransport(char* destination, int price, int distance, int capacity) : Transport(destination,price,distance){
        this->capacity = capacity;
    }
    float cenaTransport() override{
        return basePrice - (200 * capacity);
    }
};
void swap(Transport& a, Transport& b){
    Transport& temp = a;
    a = b;
    b = temp;
}
void sort(Transport** niza, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n - i -1; i++){
            if(*niza[j+1] < *niza[j]){
                swap(niza[j],niza[j+1]);
            }
        }
    }
}
void pecatiPoloshiPonudi(Transport** ponudi,int n,Transport& T){
    Transport** poskapi = new Transport *[n];
    int j = 0;
    for(int i = 0; i < n; i++){
        if(ponudi[i]->cenaTransport() > T.cenaTransport()){
            poskapi[j++] = ponudi[i];
        }
    }
    sort(poskapi,j);

    for(int i = 0; i < j; i++){
        cout << poskapi[i]->getDestination() << " " << poskapi[i]->getDistance() << " " << poskapi[i]->cenaTransport() << endl;
    }
}
int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }

    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
