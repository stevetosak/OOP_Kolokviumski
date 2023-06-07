#include <iostream>
#include <cstring>
using namespace std;

// vashiot kod ovde

class FudbalskaEkipa{
protected:
    char coachName[100];
    int goals[10];
public:
    FudbalskaEkipa(char* coachName, int* goals){
        strcpy(this->coachName,coachName);
        for(int i = 0 ; i < 10; i++){
            this->goals[i] = goals[i];
        }
    }
    virtual int uspeh() = 0;
    bool operator > (FudbalskaEkipa& other){
        return this->uspeh() > other.uspeh();
    }
    FudbalskaEkipa& operator +=(int newGoal){
        for(int i = 0; i < 10; ++i){
            goals[i] = goals[i+1];
        }
        goals[9] = newGoal;

        return *this;
    }


};
class Klub : public FudbalskaEkipa{
private:
    char clubName[64];
    int numTitles;
public:
    Klub(char* coachName, int* goals, char* clubName, int titles) : FudbalskaEkipa(coachName,goals){
        strcpy(this->clubName,clubName);
        this->numTitles = titles;
    }

    int uspeh() override{
        int total = 0;
        for(int i = 0; i < 10; i++){
            total += goals[i];
        }
        return (total * 3) + (1000 * numTitles);
    }

    friend ostream& operator << (ostream& os, FudbalskaEkipa& fb);

};

class Reprezentacija : public FudbalskaEkipa{
private:
    char countryName[64];
    int totalAppearances;
public:
    Reprezentacija(char* coachName, int* goals, char* countryName, int totalApp) : FudbalskaEkipa(coachName,goals){
        strcpy(this->countryName,countryName);
        this->totalAppearances = totalApp;
    }
    int uspeh() override{
        int total = 0;
        for(int i = 0; i < 10; i++){
            total += goals[i];
        }
        return (total * 3)  + (50 * totalAppearances);
    }
    friend ostream& operator << (ostream& os, FudbalskaEkipa& fb);
};

ostream& operator << (ostream& os, FudbalskaEkipa& fb){
    if(dynamic_cast <Klub*> (&fb)){
        Klub* klb = (Klub*)&fb;
        os << klb->clubName << endl << klb->coachName << endl << klb->uspeh() << endl;
    }
    else{
        Reprezentacija* rep = (Reprezentacija*)&fb;
        os << rep->countryName << endl << rep->coachName << endl << rep->uspeh() << endl;
    }
    return os;
}

void najdobarTrener(FudbalskaEkipa** ekipa, int n){
    int max = 0;
    int maxID = -1;
    for(int i = 0; i < n; i++){
        if(ekipa[i]->uspeh() > max){
            max = ekipa[i]->uspeh();
            maxID = i;
        }
    }
    cout << *ekipa[maxID];
}


int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}