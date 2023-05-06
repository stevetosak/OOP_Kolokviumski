#include <iostream>
#include <cstring>
#define MAX 50
enum typeC {STANDARD,LOYAL,VIP};
using namespace std;
class Customer{
private:
    char name [MAX];
    char email [MAX];
    typeC type;
    static int base_Discount;
    const static int additional_Discount;
    int no_Items;
public:
    Customer(){}
    Customer(char* name, char* email, typeC t, int no_items){
        strcpy(this->name, name);
        strcpy(this->email,email);
        this->type = t;
        this->no_Items = no_items;
    }
    Customer(const Customer& other){
        strcpy(this->name, other.name);
        strcpy(this->email,other.email);
        this->type = other.type;
        this->no_Items = other.no_Items;
    }
    void setDiscount1(int d){
        base_Discount = d;
    }

    bool operator == (const Customer& other){
        return strcmp(email, other.email) == 0;
    }

    Customer& operator =(const Customer& other){
        if(this != &other){
            strcpy(this->name, other.name);
            strcpy(this->email,other.email);
            this->type = other.type;
            this->no_Items = other.no_Items;
            return *this;
        }
        return *this;
    }

    friend ostream& operator << (ostream& os, Customer& c);
    friend class FINKI_bookstore;
};
int Customer::base_Discount = 10;
const int Customer::additional_Discount = 20;

ostream& operator << (ostream& os, Customer& c){
    os << c.name << endl;
    os << c.email << endl;
    os << c.no_Items << endl;
    if(c.type == STANDARD){
        os << "standard " << 0 << endl;
    }
    else if(c.type == LOYAL){
        os << "loyal "<< c.base_Discount << endl;
    }
    else{
        os << "vip "<< c.base_Discount + c.additional_Discount << endl;
    }
    return os;
}

class FINKI_bookstore{
private:
    Customer* customers;
    int no_Customers;
public:
    FINKI_bookstore(){
        no_Customers = 0;
        customers = new Customer[no_Customers];
    }
    ~FINKI_bookstore(){
        delete [] customers;
    }
    FINKI_bookstore& operator += (Customer& c){
        for(int i = 0; i < no_Customers; i++){
            if(customers[i] == c){
                throw "UserExistsException";
            }
        }

        Customer* temp = new Customer[no_Customers + 1];
        for(int i = 0; i < no_Customers; i++){
            temp[i] = customers[i];
        }
        temp[no_Customers] = c;
        delete [] customers;
        customers = temp;
        no_Customers ++;

        return *this;

    }

    void update(){
        for(int i = 0; i < no_Customers; i++){
            if (customers[i].type == STANDARD && customers[i].no_Items > 5){
                customers[i].type = LOYAL;
                continue;
            }
            if(customers[i].type == LOYAL && customers[i].no_Items > 10){
                customers[i].type = VIP;
            }
        }

    }

    void setCustomers(Customer* c, int n){
        for(int i = 0 ; i < n; i++){
            *this += c[i];
        }
    }

    friend ostream& operator << (ostream& os, FINKI_bookstore& fb);
};

ostream& operator << (ostream& os, FINKI_bookstore& fb){
    for(int i = 0; i < fb.no_Customers; i++){
        cout << fb.customers[i];
    }

    return os;
}



int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }
        try{
        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
            fc+=c;
        }
        catch(const char* msg){
            cout << "The user already exists in the list!" << endl;
        }


        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
