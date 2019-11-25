#include <iostream> 
#include <type_traits>
#include <vector> 
#include <string>
#include <sstream>
#include <utility>
#include <memory>

//Decorator facilitates addition of additional behavior or functionality
//Question: How do we give this functionality?
//DO not want to rewrite or alter existing  code (OCP)
//Want to keep new functionality separate (SRP)
//need to be able to interact with existing structures, Two Options:
//1. Aggregate the decorated object, i.e stick the existing object via reference
//2. (More direct): Inherit from the decorated object

struct Shape{
    virtual std::string str() const = 0;
};

struct Circle : public Shape{
    float m_radius;
    Circle(){}
    Circle(float rad): m_radius(rad){}

    std::string str()const override{
        std::ostringstream oss;
        oss << "A circle of radius " << m_radius << "\n";
        return oss.str();
    }
    
    void resize(const float factor){
        m_radius *= factor;
    }

};

struct Square : public Shape{

    float m_side;
    Square(){ }
    Square(float side):m_side(side){    }
    std::string str()const override {
        std::ostringstream oss;
        oss << "A square of side length " << m_side << "\n";
        return oss.str();
    }

    //Note: Resize function as in Circle is not 
    //a member of Square
};

//Now add the feature Color to each of the 
//possible shape that could occur. Using the decorator 
//pattern, rather than creatign a class for each colored shape,
//we can write a class for colored shape inheriting from shape itself


//Using inheritance, something known as dynamic decorator
//is constructed 
struct ColoredShape : public Shape{

    Shape& m_shape;
    std::string m_color;

    ColoredShape(Shape& shape, const std::string& color): m_shape(shape), m_color(color)
    { }

    std::string str()const override{
        std::ostringstream oss;
        oss << m_shape.str() << " has the color " << m_color <<"\n";
        return oss.str();
    }
};

struct TransparentShape : public Shape{
    Shape& m_shape;
    uint8_t m_transparency;

    TransparentShape(Shape& shape, const uint8_t transparency):
        m_shape(shape), m_transparency(transparency){   }

    std::string str() const override{
        std::ostringstream oss;
        oss << m_shape.str() << " has "
            << static_cast<float>(m_transparency)/255.f*100 << "% transparency\n";
        return oss.str();
    }
};


//static decorator pattern, but user has to ensure that
//proper type T is inherited from
//This is mixin inheritence
template <typename T>
struct ColoredShape2 : T{
    static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a shape");
    
    std::string m_color;
    ColoredShape2(){ }

    //ColoredShape<TransparentShape<Circle>> could be used
    //if a constructor accepting variadic arguments can be 
    //created
    template<typename ...Args>
    ColoredShape2(const std::string& color, Args ...args):
    T(std::forward<Args>(args)...), m_color{color}{    }

    std::string str()const override{
        std::ostringstream oss;
        oss << T::str() << "has the color " << m_color << "\n";
        return oss.str();
        }
};

template <typename T>
struct TransparentShape2 : public T{
    static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a Shape");
    uint8_t m_transparency;
    TransparentShape2() { }
    template<typename ...Args>
        TransparentShape2(const uint8_t transparency, Args ...args ):
            m_transparency(transparency), T(std::forward<Args>(args)...) 
    {
        //empty constructor body
    }

    std::string str() const override{
        std::ostringstream oss;
        oss << T::str() << " is " <<
            static_cast<float>(m_transparency)/255.f*100 
            << "% transparent";
        return oss.str();
    }
};

template <typename T>
struct ColoredShape3 : public T{
    static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a base of `Shape`");
    std::string m_color;
    ColoredShape3() = default;

    //ColoredShape<TransparentShape<SomeOtherShapePropety<Square>>> could be used if a 
    //constructor accepting  variadic arguments can be created
    template <typename ...Args>
    ColoredShape3(const std::string& color, Args ...args):
        m_color(color),  T(std::forward<Args>(args)...){    }

    std::string str() const override {
        std::ostringstream oss;
        oss << T::str() <<  " has the color " << m_color <<"\n";
        return oss.str();
    }
};

template <typename T>
struct TransparentShape3 : public T{

    static_assert(std::is_base_of<Shape, T>::value, "Template argument must be a base of `Shape`");
    uint8_t m_transparency;

    TransparentShape3() = default;
    template <typename ...Args>
    TransparentShape3(uint8_t transparency, Args ...args):
        m_transparency(transparency), T(std::forward<Args>(args)...){   }

    std::string str()const override{

        std::ostringstream oss;
        oss << T::str() << " has a transparency value of " 
            << static_cast<float>(m_transparency)/255.f*100 << "%\n";
        return oss.str();
    }
};


//Mixin Inheritance allows us to access the API of 
//whatever object we're decorating through the decorator itself

int main(){

    Circle c1(3.0);
    ColoredShape coloredCircle{c1, "green"};

    TransparentShape transp_greenCirc{coloredCircle, 51};
    std::cout << transp_greenCirc.str();


    ColoredShape3<Circle> green_circle{"orange", 5};
    std::cout << green_circle.str() << "\n";

    TransparentShape3<ColoredShape3<Circle>> transp_g2{153, "blue", 12};
    transp_g2.resize(0.4); //not resize() calls the correct method 
                           //as this has been resolved at compile time
    std::cout << transp_g2.str() << "\n";
    return 0;
}
