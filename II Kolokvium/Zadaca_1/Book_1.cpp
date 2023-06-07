// 11
#include <iostream>
#include <cstring>

using namespace std;

class Book
{
protected:
    char isbn[21];
    char title[69];
    char author[31];
    float price;

public:
    Book(char *isbn = "", char *title = "", char *author = "", float price = 0)
    {
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
        this->price = price;
    }
    virtual float bookPrice() const = 0;
    virtual ~Book() {}
    bool operator>(const Book& o)
    {
        return (this->bookPrice() > o.bookPrice());
    }
    friend ostream& operator << (ostream& os, Book& b);
};

class OnlineBook : public Book
{
protected:
    char *url;
    int mb;

public:
    OnlineBook(char *isbn = "", char *title = "", char *author = "", float price = 0, char *url = "", int mb = 0)
            : Book(isbn, title, author, price)
    {
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
        this->mb = mb;
    }
    OnlineBook(const OnlineBook &o) : Book((Book&) o)
    {
        this->url = new char[strlen(o.url) + 1];
        strcpy(this->url, o.url);
        this->mb = o.mb;
    }
    OnlineBook &operator=(const OnlineBook &o)
    {
        if (this == &o)
            return *this;

        strcpy(this->isbn, o.isbn);
        strcpy(this->title, o.title);
        strcpy(this->author, o.author);
        this->price = o.price;
        delete[] url;
        this->url = new char[strlen(o.url) + 1];
        strcpy(this->url, o.url);
        this->mb = o.mb;

        return *this;
    }
    float bookPrice() const
    {
        if (mb > 20)
        {
            return (price * 1.2);
        }
        else
            return price;
    }

    void setISBN(char *i)
    {
        strcpy(isbn, i);
    }
    ~OnlineBook()
    {
        delete[] url;
    }
    friend ostream& operator << (ostream& os, Book& b);
};

class PrintBook : public Book
{
protected:
    float mass;
    bool available;

public:
    PrintBook(char *isbn = "", char *title = "", char *author = "", float price = 0, float mass = 0, bool available = 0)
            : Book(isbn, title, author, price)
    {
        this->mass = mass;
        this->available = available;
    }
    PrintBook(const PrintBook &o)
    {
        this->mass = o.mass;
        this->available = o.available;
    }

    float bookPrice() const
    {
        if (mass > 0.7)
        {
            return (price * 1.15);
        }
        else
            return price;
    }
    bool operator>(const PrintBook &o)
    {
        return (this->bookPrice() > o.bookPrice());
    }
    bool operator<(const PrintBook &o)
    {
        return (this->bookPrice() < o.bookPrice());
    }
    void setISBN(char *i)
    {
        strcpy(isbn, i);
    }
    ~PrintBook() = default;


    friend ostream& operator << (ostream& os, Book& o);
};

ostream& operator << (ostream& os, Book& o){
    os << o.isbn << ": " << o.title << ", " << o.author << " " << o.bookPrice() << endl;
    return os;
}

//p << o.isbn << " " << o.title << " " << o.author << " " << o.bookPrice() << endl;

void mostExpensiveBook(Book *niza[], int n)
{
    int i, online = 0, printed = 0, maxIndex = 0;
    for (i = 0; i < n; i++)
    {
        OnlineBook *tmp = dynamic_cast<OnlineBook *>(niza[i]);
        if (tmp)
        {
            online++;
        }
        else
        {
            printed++;
        }

        if (niza[i]->bookPrice() > niza[maxIndex]->bookPrice())
        {
            maxIndex = i;
        }
    }
    cout << "FINKI-Education" <<endl;
    cout << "Total number of online books: " << online << endl;
    cout << "Total number of print books: " << printed << endl;
    cout << "The most expensive book is:" << endl;
    cout << *niza[maxIndex];
    //FINKI-Education↩
    //Total number of online books: 2↩
    //Total number of print books: 1↩
    //The most expensive book is:↩
    //007-6092006565: Thinking in C++, Bruce Eckel 59.8

}

int main()
{

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1)
    {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << (*books[0]);
        else
            cout << *books[1];
    }
    if (testCase == 2)
    {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3)
    {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4)
    {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++)
        {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1)
            {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);
            }
            else
            {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++)
        delete books[i];
    delete[] books;
    return 0;
}