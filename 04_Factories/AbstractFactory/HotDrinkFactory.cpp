#include <HotDrinkFactory.hpp>

std::unique_ptr<HotDrink> TeaFactory::make() const{
    return std::make_unique<Tea>();
}

std::unique_ptr<HotDrink> CoffeeFactory::make() const{
    return std::make_unique<Coffee>();
}

