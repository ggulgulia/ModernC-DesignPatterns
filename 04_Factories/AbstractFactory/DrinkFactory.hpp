#ifndef DRINKFACTORY_H
#define DRINKFACTORY_H

#include <HotDrink.hpp>
#include <HotDrinkFactory.hpp>
#include <map>

class DrinkFactory
{
private:

    std::map<std::string, std::unique_ptr<HotDrinkFactory>> m_hotFactories;

public:
    DrinkFactory(){
        m_hotFactories["coffee"] = std::make_unique<CoffeeFactory>();
        m_hotFactories["tea"] = std::make_unique<TeaFactory>();
    }
    
    std::unique_ptr<HotDrink> make_drink(const std::string& name){
        auto drink = m_hotFactories[name]->make();
        drink->Prepare(200);
        return drink;
    }
    virtual ~DrinkFactory() = default;
};

#endif /* DRINKFACTORY_H */
