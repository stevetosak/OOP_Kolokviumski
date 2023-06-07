#include<iostream>
#include<cstring>
using namespace std;

class BadInputException{
public:
    void message(){
        cout << "Greshna opisna ocenka" << endl;
    }
};

char* fix(char* badString){
    char* temp = new char[strlen(badString)+1];
    for(int i = 0, j = 0; i < strlen(badString); i++){
        if(isalpha(badString[i])){
            temp[j++] = badString[i];
        }
    }
    return temp;
}
class StudentKurs{
protected:
    char ime[30];
    int ocenka;
    bool daliUsno;
    static int MAX;
    const static int MINOCENKA;
public:
    StudentKurs() = default;

    StudentKurs(char* ime,int finalenIspit){
        strcpy(this->ime,ime);
        this->ocenka=finalenIspit;
        this->daliUsno=false;
    }
   static void setMAX(int nmx){
        MAX = nmx;
    }

    virtual int calcOcenka(){
        return ocenka;
    }
    bool getDaliUsno(){
        return daliUsno;
    }
    friend class KursFakultet;
    friend ostream& operator << (ostream& os, StudentKurs& sk);
    virtual ~StudentKurs() = default;
};

int StudentKurs:: MAX = 10;
const int StudentKurs:: MINOCENKA = 6;

class StudentKursUsno : public StudentKurs{
private:
    char* opisnaOcenka;
public:
    StudentKursUsno() : StudentKurs(){
        opisnaOcenka = new char[0];
        daliUsno = true;
    }

    StudentKursUsno(char* name, int ocenka) : StudentKurs(name,ocenka){
        opisnaOcenka = new char[0];
        daliUsno = true;
    }
    StudentKursUsno(const StudentKursUsno& other) : StudentKurs((StudentKurs&)other){
        this->opisnaOcenka = new char[strlen(other.opisnaOcenka)+1];
        strcpy(this->opisnaOcenka,other.opisnaOcenka);
    }

    StudentKursUsno& operator +=(char* usnaOcenka){
        for(int i = 0; i < strlen(usnaOcenka); i++){
            if(!isalpha(usnaOcenka[i])){
                opisnaOcenka = new char[strlen(fix(usnaOcenka)) +1];
                strcpy(opisnaOcenka, fix(usnaOcenka));
                throw BadInputException();
            }
        }
        opisnaOcenka = new char[strlen(usnaOcenka) +1];
        strcpy(opisnaOcenka,usnaOcenka);

        return *this;
    }

    int calcOcenka(){
        if(!strcmp(opisnaOcenka,"odlicen")){
            if(StudentKurs::calcOcenka() + 2 >= MAX){
                return StudentKurs::calcOcenka();
            }
            else{
                return StudentKurs::calcOcenka() + 2;
            }
        }
        else if(!strcmp(opisnaOcenka,"dobro")){
            if(StudentKurs::calcOcenka() + 1 >= MAX){
                return StudentKurs::calcOcenka();
            }
            else{
                return StudentKurs::calcOcenka() + 1;
            }
        }
        else if(!strcmp(opisnaOcenka,"losho")){
           return StudentKurs::calcOcenka() -1;
        }
        else{
            return StudentKurs:: calcOcenka();
        }
    }
    ~StudentKursUsno(){
        delete [] opisnaOcenka;
    }

    friend ostream& operator << (ostream& os, StudentKurs& sk);
};

ostream& operator << (ostream& os, StudentKurs& sk){
    os << sk.ime << " --- " << sk.calcOcenka() << endl;
    return os;
}

class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako studentot ima usno isprashuvanje
            if (studenti[i]->getDaliUsno()){
                this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
            }
            else this->studenti[i]=new StudentKurs(*studenti[i]);
        }
        this->broj=broj;
    }
    ~KursFakultet(){
        for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti() const{
        cout << "Kursot " << naziv << " go polozile:" << endl;
        for(int i = 0; i < broj; i++){
            if(studenti[i]->calcOcenka() >= StudentKurs::MINOCENKA){
                cout << *studenti[i];
            }
        }

    }
    void postaviOpisnaOcenka(char* ime,char* opisnaOcenka){
        for(int i = 0; i < broj; i++){
            if(!strcmp(studenti[i]->ime,ime)){
                if(dynamic_cast <StudentKursUsno*>(studenti[i])){
                    StudentKursUsno* sku = (StudentKursUsno*)studenti[i];
                    *sku += opisnaOcenka;
                }
                else{
                    return ;
                }
            }
        }
    }




    //дополни ја класата
};

int main(){

    StudentKurs **niza;
    int n,m,ocenka;
    char ime[30],opisna[10];
    bool daliUsno;
    cin>>n;
    niza=new StudentKurs*[n];
    for (int i=0;i<n;i++){
        cin>>ime;
        cin>>ocenka;
        cin>>daliUsno;
        if (!daliUsno)
            niza[i]=new StudentKurs(ime,ocenka);
        else
            niza[i]=new StudentKursUsno(ime,ocenka);
    }

    KursFakultet programiranje("OOP",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    try{
        for (int i=0;i<m;i++){
            cin>>ime>>opisna;
            programiranje.postaviOpisnaOcenka(ime,opisna);
        }
    }
    catch (BadInputException& exp){
        exp.message();
    }

    programiranje.pecatiStudenti();

    StudentKurs::setMAX(9);
    
}
