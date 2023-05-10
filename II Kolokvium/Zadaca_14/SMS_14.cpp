#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;
class SMS{
protected:
    double price;
    char ReceivingNumber[14];
    const static double DDV;
public:
    SMS(double price, char* number){
        this->price = price;
        strcpy(this->ReceivingNumber,number);
    }
    SMS(const SMS& other){
        this->price = other.price;
        strcpy(this->ReceivingNumber,other.ReceivingNumber);
    }
    virtual double SMS_cena () = 0;
    virtual ~SMS() = default;
    friend ostream& operator << (ostream& os, SMS& sms);
};

const double SMS::DDV = 18;

class RegularSMS : public SMS{
private:
    char* msg = new char [0];
    bool wasRoaming = true;
    static float pctForRoaming;
public:
    RegularSMS(char* number, double price, char* msg, bool roaming) : SMS(price,number){
        this->msg = new char [strlen(msg) + 1];
        strcpy(this->msg,msg);
        this->wasRoaming = roaming;
    }
    RegularSMS(const RegularSMS& other) : SMS(other){
        copy(other,true);
    }
    RegularSMS& operator = (const RegularSMS& other){
        if(this != & other){
            delete [] msg;
            copy(other,false);
            return *this;
        }
        return *this;
    }
    double SMS_cena() override{
        double total = price;
        double remainder = (double)strlen(msg)/160.0;
        total *= ceil(remainder);
        if(wasRoaming){
            total *= ((pctForRoaming/100) +1);
            return total;
        }
        else{
            total += (DDV/100) * total;
            return total;
        }

    }
    static void set_rProcent (int pct){
        pctForRoaming = pct;
    }

    ~RegularSMS(){
        delete [] msg;
    }
private:
    void copy(const RegularSMS& other, bool a){
        if(a){
            this->msg = new char [strlen(other.msg) +1];
            strcpy(this->msg,other.msg);
            this->wasRoaming = other.wasRoaming;
        }
        else{
            this->msg = new char [strlen(other.msg) +1];
            strcpy(this->msg,other.msg);
            this->wasRoaming = other.wasRoaming;
            this->price = other.price;
            strcpy(this->ReceivingNumber,other.ReceivingNumber);

        }
    }
};
float RegularSMS::pctForRoaming = 300;

class SpecialSMS : public SMS{
private:
    bool isHumanitarian = true;
    static double pctForSpecial;
public:
    SpecialSMS(char* number, double price, bool humanitarian) : SMS(price,number){
        this->isHumanitarian = humanitarian;
    }

    double SMS_cena() override{
        double total = price;
        if(!isHumanitarian){
            total *= ((pctForSpecial/100.0) +1);
            return total;
        }
        else{
            return total;
        }
    }

    static void set_sProcent(int pct){
        pctForSpecial = pct;
    }

};
double SpecialSMS::pctForSpecial = 150;
//Tel: 0038971111222 - cena: 50den.
ostream& operator << (ostream& os, SMS& sms){
    os << "Tel: "<< sms.ReceivingNumber << " - "<< "cena: " << sms.SMS_cena() << "den." << endl;
    return os;
}

void vkupno_SMS(SMS** poraka, int n){
    int numRegular = 0;
    int numSpecial = 0;
    double totalPriceRegular = 0;
    double totalPriceSpecial = 0;

    for(int i = 0; i < n; i++){
        if(dynamic_cast <RegularSMS*> (poraka[i])){
            RegularSMS* rSMS = (RegularSMS*)poraka[i];
            numRegular++;
            totalPriceRegular += rSMS->SMS_cena();
        }
        else if(dynamic_cast <SpecialSMS*> (poraka[i])){
            SpecialSMS* spSMS = (SpecialSMS*)poraka[i];
            numSpecial++;
            totalPriceSpecial+= spSMS->SMS_cena();
        }
    }
//Vkupno ima 0 regularni SMS poraki i nivnata cena e: 0
//Vkupno ima 3 specijalni SMS poraki i nivnata cena e: 412.5
    cout << "Vkupno ima " << numRegular << " regularni SMS poraki i nivnata cena e: " << totalPriceRegular << endl;
    cout << "Vkupno ima " << numSpecial << " specijalni SMS poraki i nivnata cena e: " << totalPriceSpecial << endl;
}

int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;

                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        sms1 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin.get();
        cin.getline(msg, 1000);
        cin >> roam;
        cin >> p;
        RegularSMS::set_rProcent(p);
        sms2 = new RegularSMS(tel, cena, msg, roam);
        cout << *sms2;

        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        cin >> tel;
        cin >> cena;
        cin >> hum;
        sms1 = new SpecialSMS(tel, cena, hum);
        cout << *sms1;

        cin >> tel;
        cin >> cena;
        cin >> hum;
        cin >> p;
        SpecialSMS::set_sProcent(p);
        sms2 = new SpecialSMS(tel, cena, hum);
        cout << *sms2;

        delete sms1, sms2;
    }

    return 0;
}
