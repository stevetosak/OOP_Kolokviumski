#include <iostream>
#include <cstring>
using namespace std;

class ExistingGame : public std::exception {
private:
    char msg [128];
public:
    ExistingGame(char* msg){
        strcpy(this->msg, msg);
    }
    void message(){
        cout << msg << endl;
    }
};

class Game{
protected:
    char name[100];
    float price;
    bool hasDiscount;
public:
     Game(char* name = "", float price = 0, bool discount = false){
        strcpy(this-> name, name);
        this->price = price;
        this->hasDiscount = discount;
    }

     virtual void print(){
        cout << "Game: " << name << ", regular price: $" << price << (hasDiscount ? ", bought on sale\n" : "\n");
    }
    virtual ~Game() = default;

    bool operator == (const Game& other){
         return !strcmp(this->name, other.name);
    }

    friend ostream& operator << (ostream& os, Game& game);
     friend istream& operator >> (istream& is, Game& game);
     friend class User;
};

class SubscriptionGame : public Game{
private:
    float subscription_Price;
    int monthAquired;
    int yearAquired;
public:
    SubscriptionGame(char* name = "", float price = 0, bool discount = false, float subscription = 0, int month = 0, int year = 0) : Game(name,price,discount){
        this-> subscription_Price = subscription;
        this->monthAquired = month;
        this->yearAquired = year;
    }

    ~SubscriptionGame(){}

    void print(){
        cout << "Game: " << name << ", regular price: $" << price << (hasDiscount ? ", bought on sale" : "")
        << ", monthly fee: $" << subscription_Price << ", purchased: " << monthAquired << "-" << yearAquired << endl;
    }

    friend istream& operator >> (istream& is, Game& game);
    friend ostream& operator << (ostream& os, Game& game);
    friend class User;
};

ostream& operator << (ostream& os, Game& game){
    game.print();
    return os;
}

istream& operator >> (istream& is, Game& game){
    try
    {
        SubscriptionGame& sg = dynamic_cast <SubscriptionGame&> (game);
        is.get();
        is.getline(game.name,100);
        is >> sg.price >> sg.hasDiscount >> sg.subscription_Price >> sg.monthAquired >> sg.yearAquired;
        return is;
    }
    catch(bad_cast &msg)
    {
        is.get();
        is.getline(game.name,100);
        is >> game.price >> game.hasDiscount;
        return is;
    }
}

class User{
private:
    char username[100];
    Game** games;
    int num_Games;
public:

    User(char* name){
        strcpy(this->username,name);
        num_Games = 0;
        games = new Game *[num_Games];
    }

    User& operator += (Game& newgame){
        for(int i = 0; i < num_Games; i++){
            if(*games[i] == newgame){
                throw ExistingGame("The game is already in the collection");
            }

        }

        Game** temp = new Game *[num_Games +1];
        for(int i = 0; i < num_Games; i++){
            temp[i] = games[i];
        }

        SubscriptionGame* sg = dynamic_cast <SubscriptionGame*> (&newgame);

        if(sg != nullptr){
            temp[num_Games] = new SubscriptionGame(*sg);
        }
        else{
            temp[num_Games] = new Game(newgame);
        }

        delete [] games;
        games = temp;
        num_Games++;

        return *this;
    }

    float total_spent(){
        float total = 0;
        for(int i = 0; i < num_Games; i++){
            if(games[i]->hasDiscount){
                total += games[i]->price * 0.3;
            }
            else{
                total += games[i]->price;
            }

            SubscriptionGame* sg = dynamic_cast<SubscriptionGame*>(games[i]);
            if(sg != nullptr){
                int monthsElapsed = (5 + (2018 * 12) - (sg->monthAquired + (sg->yearAquired * 12))); // za segasen mesec e zemen 5 maj 2018
                total += monthsElapsed * sg->subscription_Price;
            }
        }
        return total;
    }

    friend ostream& operator << (ostream& os, User& user);
};

ostream& operator << (ostream& os, User& user){
    cout << "\n";
    os << "User: " <<user.username << endl;
    for(int i = 0; i < user.num_Games; i++){
        cout << "- ";
        user.games[i]->print();
    }

    return os;
}

int main() {
    int test_case_num;

    cin>>test_case_num;

    // for Game
    char game_name[100];
    float game_price;
    bool game_on_sale;

    // for SubscritionGame
    float sub_game_monthly_fee;
    int sub_game_month, sub_game_year;

    // for User
    char username[100];
    int num_user_games;

    if (test_case_num == 1){
        cout<<"Testing class Game and operator<< for Game"<<std::endl;
        cin.get();
        cin.getline(game_name,100);
        //cin.get();
        cin>>game_price>>game_on_sale;

        Game g(game_name, game_price, game_on_sale);

        cout<<g;
    }
    else if (test_case_num == 2){
        cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
        cin.get();
        cin.getline(game_name, 100);

        cin>>game_price>>game_on_sale;

        cin>>sub_game_monthly_fee;
        cin>>sub_game_month>>sub_game_year;

        SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        cout<<sg;
    }
    else if (test_case_num == 3){
        cout<<"Testing operator>> for Game"<<std::endl;
        Game g;

        cin>>g;

        cout<<g;
    }
    else if (test_case_num == 4){
        cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
        SubscriptionGame sg;

        cin>>sg;

        cout<<sg;
    }
    else if (test_case_num == 5){
        cout<<"Testing class User and operator+= for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        try {

            for (int i=0; i<num_user_games; ++i){

                cin >> game_type;

                Game *g;
                // 1 - Game, 2 - SubscriptionGame
                if (game_type == 1){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;
                    g = new Game(game_name, game_price, game_on_sale);
                }
                else if (game_type == 2){
                    cin.get();
                    cin.getline(game_name, 100);

                    cin>>game_price>>game_on_sale;

                    cin>>sub_game_monthly_fee;
                    cin>>sub_game_month>>sub_game_year;
                    g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
                }

                //cout<<(*g);


                u+=(*g);
            }
        }catch(ExistingGame &ex){
            ex.message();
        }

        cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

    }
    else if (test_case_num == 6){
        cout<<"Testing exception ExistingGame for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);

            try {
                u+=(*g);
            }
            catch(ExistingGame &ex){
                ex.message();
            }
        }

        cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
    }
    else if (test_case_num == 7){
        cout<<"Testing total_spent method() for User"<<std::endl;
        cin.get();
        cin.getline(username,100);
        User u(username);

        int num_user_games;
        int game_type;
        cin >>num_user_games;

        for (int i=0; i<num_user_games; ++i){

            cin >> game_type;

            Game *g;
            // 1 - Game, 2 - SubscriptionGame
            if (game_type == 1){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;
                g = new Game(game_name, game_price, game_on_sale);
            }
            else if (game_type == 2){
                cin.get();
                cin.getline(game_name, 100);

                cin>>game_price>>game_on_sale;

                cin>>sub_game_monthly_fee;
                cin>>sub_game_month>>sub_game_year;
                g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
            }

            //cout<<(*g);


            u+=(*g);
        }

        cout << u <<endl;

        cout<<"Total money spent: $"<<u.total_spent()<<endl;
    }
}
