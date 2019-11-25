
#ifndef HOTDRINK_H
#define HOTDRINK_H
#include <iostream>
#include <memory>

class HotDrink
{
public:
     HotDrink () = default;
    virtual ~HotDrink () = default;
    virtual void Prepare(int volume) = 0;
};

class Tea : public HotDrink{

    public:
        Tea() = default;
        virtual ~Tea() = default;
        virtual void Prepare(int volume) override;
};

class Coffee : public HotDrink{

    public:
        Coffee() = default;
        virtual  ~Coffee() = default;
        virtual void Prepare(int volume) override;
};

#endif /*HOTDRINK_H */
