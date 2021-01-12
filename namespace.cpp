#include <iostream>
#include <vector>

namespace classes{
    class Pessoa{
    private:
        int idade;
    public:
        
        void set_age(int age){
            idade=age;
        }
        int get_age(){
            return idade;
        }
    };
}
namespace teste2{//Exemplo de utilidade do "namespace"
    int get_age(){
        return 23;
    }
}
int main(void)
    {
    classes::Pessoa eu;
    eu.set_age(23);
    std::cout<<"A idade é "<<eu.get_age()<<std::endl;
    std::cout<<"A idade, vindo da mesma função get_age, porém do namespace teste 2 é: "<<teste2::get_age()<<std::endl;
    }
