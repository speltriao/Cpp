#include<iostream>
using namespace std;

class Forma_Geometrica{
    protected:
        double base,altura; 
    public:
        double criar_forma(double a, double b){
            altura=a;
            base=b;
            return(altura,base);
        }
};
class Retangulo: public Forma_Geometrica{
    public:
        double area_retangulo(){ 
            return(base*altura);
        }
};
class Triangulo: public Retangulo{
    public:
        double area_triangulo(){
            return(area_retangulo()/2);
        }
};

int main(){
    double a,b;
    cout<<"Digite A e B respectivamente "<<endl;
    cin>>a>>b;
    Retangulo meu_retangulo;
    meu_retangulo.criar_forma(a,b);
    Triangulo meu_triangulo;
    meu_triangulo.criar_forma(a,b);
    cout <<"Area do retangulo "<<meu_retangulo.area_retangulo()<<endl<<"Area do triangulo "<<meu_triangulo.area_triangulo()<<endl;
    return(0);
}
