#include<iostream>
#include<string>
using namespace std;
class Animal{
    protected:
        int age;
        string name;
    public:
        void set_value(int a, string n){
            age=a;
            name=n;

        }
};
class Zebra :public  Animal{
    public:
        string local;
        void imprimir(){ 
            cout<<"Idade da zebra: "<<age<<endl;
            cout<<"Nome da zebra: " << name<<endl;
            cout<<"Local de origem da zebra: " <<local<<endl; 
            }
};

int main(){
    string nome="Zebra 1";
    Zebra minha_zebra;
    minha_zebra.set_value(10,nome);
    minha_zebra.local="Africa";
    minha_zebra.imprimir();
    return 0;
}