#ifndef HOTDRINKFACTORY_H
#define HOTDRINKFACTORY_H

#include <HotDrink.hpp>

class HotDrinkFactory
{
    

public:
    HotDrinkFactory() = default;
    virtual ~HotDrinkFactory() = default;

    virtual std::unique_ptr<HotDrink> make() const = 0;
};

class TeaFactory : public HotDrinkFactory{

    std::unique_ptr<HotDrink> make() const override;
};

class CoffeeFactory : public HotDrinkFactory{

    std::unique_ptr<HotDrink> make() const override;
};

#endif /* HOTDRINKFACTORY_H */
