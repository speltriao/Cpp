#include <iostream>
#include <string>

static int user_count=0;
static int teacher_count=0;

class User{
protected:
    std::string name; //Nome do usuário
    int id; //ID do usuário
public:
    std::string curso; // Nome da graduação cursada pelo usuário
    User(){ //Construtor da classe usuário
        user_count++;
    }
    ~User(){//Destructor
        user_count--;
    }
    void set_User_name(std::string str){
        name = str;
    }
    std::string get_User_name(){
        return name;
    }

    void set_User_id(int ide){
        id = ide;
    }
    int get_User_id(){
        return id;
    }

};

class Teacher: protected User {
protected:
    float salario; //Salario do prof
public:
    std::string nivel; //Doutor, mestre ou so professor
    Teacher(){//Construtor da classe Teacher
        teacher_count++;
    }
    ~Teacher(){//Destrutor da classe Teacher
        teacher_count--;
    }
    void set_Tchr_name(std::string str){
        name = str;
    }
    std::string get_Tchr_name(){
        return name;
    }

    void set_Tchr_id(int ide){
        id = ide;
    }
    int get_Tchr_id(){
        return id;
    }
};


int main(){
    Teacher neide;
    User& n = neide; 
    std::cout<<user_count<<std::endl;
    std::cout<<teacher_count<<std::endl;
    return 0;
}