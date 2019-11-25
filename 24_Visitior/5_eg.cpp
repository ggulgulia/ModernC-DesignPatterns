#include <iostream>
#include <string>
#include <variant>
#include <vector>
#include <type_traits>

struct AddressPrinter{
    void operator()(const std::string& houseName) const{
        std::cout << "A house called " << houseName << "\n";
    }
    void operator()(const int houseNum) const{
        std::cout << "A house numbered " << houseNum << "\n";
    }
};
int main(){
        
    std::variant<std::string, int> house;
    house = 123;
    //house = "Montefiore castle";
    
    AddressPrinter ap;
    //std::visit(ap, house);
    std::visit([](auto& arg){
            using T = std::decay_t<decltype(arg)>;
            if constexpr(std::is_same_v<T, std::string>){
                    std::cout << "a house called " << arg << "\n";
                }
            else{
                std::cout << "House number " << arg << "\n";
                }
            }, house);

}
