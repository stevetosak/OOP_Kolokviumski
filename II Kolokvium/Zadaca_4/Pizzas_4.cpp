#include <cstring>
#include <iostream>
using namespace std;
enum Size{Small,Large,Family};

void convert(Size t){
    if(t == Small){
        cout << "small";
    }
    else if(t == Family){
        cout << "family";
    }
    else if(t == Large){
        cout << "large";
    }
}

class Pizza{
protected:
    char name[20];
    char ingredients[100];
    float base_Price;
public:
    Pizza(char* name, char* ingredients, float price){
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->base_Price = price;
    }

    virtual float price() = 0;
    virtual ~Pizza() = default;
    virtual bool operator < (Pizza& p) = 0;
    virtual void print() = 0;

    friend ostream& operator << (ostream& os, Pizza& p);

};
class FlatPizza : public Pizza{
private:
    Size size = Small;
public:
    FlatPizza(char* _name, char* _ingredients, float _price) : Pizza(_name,_ingredients,_price){
    }
    FlatPizza(char* _name, char* _ingredients, float _price, Size size) : Pizza(_name,_ingredients,_price){
        this->size = size;
    }

    void print(){
        cout << name << ": " << ingredients << ", " ;
        convert(size);
        cout << " - " << price() << endl;
    }

    float price(){
        if(size == Small){
            float percent  = (base_Price * 10) / 100;
            return base_Price + percent;
        }
        else if(size == Family){
            float percent  = (base_Price * 30) / 100;
            return base_Price + percent;
        }
        else{
            float percent  = (base_Price * 50) / 100;
            return base_Price + percent;
        }
    }

    bool operator < (Pizza& other){
        if(this->price() < other.price()){
            return true;
        }
        else {
            return false;
        }
    }

    ~FlatPizza(){}

};

class FoldedPizza : public Pizza{
private:
    bool hasWhiteFlour;
public:
    FoldedPizza(char* _name, char* _ingredients, float _price) : Pizza(_name,_ingredients,_price){
        hasWhiteFlour = true;
    }

    void setWhiteFlour(bool value){
        hasWhiteFlour = value;
    }

    void print (){
        cout << name << ": " << ingredients << ", " << (hasWhiteFlour ? "wf" : "nwf") <<" - " << price()  << endl;
    }

    float price(){
        if(hasWhiteFlour){
            float percent = (base_Price * 10) / 100;
            return base_Price + percent;
        }
        else{
            float percent = (base_Price * 30) / 100;
            return base_Price + percent;
        }
    }

    bool operator < (Pizza& other){
        if(this->price() < other.price()){
            return true;
        }
        else {
            return false;
        }
    }

    ~FoldedPizza(){}

};

//За рамна пица:[име]: [состојки], [големина] - [продажната цена на пицата].
//За преклопена пица: [име]: [состојки], [wf - ако е со бело брашно / nwf - ако не е со бело брашно] - [продажната цена на пицата]

ostream& operator << (ostream& os, Pizza& p){
    p.print();
    return os;
}

void expensivePizza(Pizza** pizzas, int n){
    float max = 0;
    Pizza* memPtr;
    for(int i = 0 ; i < n; i++){
        if(pizzas[i]->price() > max){
            max = pizzas[i] -> price();
            memPtr = pizzas[i];
        }
    }

    memPtr->print();
}

// Testing

int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}
