#include <iostream>
#include <DrinkFactory.hpp>


std::unique_ptr<HotDrink> make_drink(const std::string& type){
    std::unique_ptr<HotDrink> drink;
    if(type == "Tea"){
    }

    else if(type == "Coffee"){
    }

    return drink;
}
int main(){

    std::unique_ptr<HotDrink> coffee;//= CoffeeFactory::make(); 

    DrinkFactory df;
    coffee = df.make_drink("coffee");
    return 0;
}
