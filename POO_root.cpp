#include <iostream>
#include <string>
#include <list>


class User{
    protected:
        std::string id;
        std::string name;
    public:
        std::string getID() {return id;}
        std::string getName() {return name;}
        void setID(std::string s) {id=s;};
        void setName(std::string s) {name=s;}
}; 

class SuperUser:public User{
    private:
        std::string pswd = "admin";
    public:
        bool checkPswd(std::string s){
            if(s.compare(pswd)==0){
                std::cout<<"Logged in as root. You can now create new users.\n\n";
                return true;
            }
            else {
                std::cout<<"Wrong password. Please try again\n";
                return false;
            }
        }
};

std::list<User> create_users(){
    std::string id;
    std::string name;
    std::list<User> lista;

    while (1){
        std::cout<<"Type the user name or type \"exit\" to leave:\n";
        std::cin>>name;
        if(name.compare("exit")==0) break;
        std::cout<<"Type the user id:\n";
        std::cin >> id;
        User u;
        u.setID(id);
        u.setName(name);
        lista.push_back(u);
    }
    return lista;
}

void print_users(std::list<User> l){
    for(User us : l){
        std::cout<<"The user name is: "<<us.getName()<<". This user id is: "<<us.getID()<<"\n"; 
    }
}



int main() {
    SuperUser su;
    std::string password;
    do{
        std::cout<<"Type root password: ";
        std::cin>>password;
    }while(su.checkPswd(password)==false);
    print_users(create_users());
}


