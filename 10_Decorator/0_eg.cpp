#include <iostream> 
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
    
    //Note resize is not specified as a part 
    //of `Shape` interface, hence at runtime,
    //`resize()` method is not resolved
    //as a part of some `shape` object
    //which is also a `Circle`
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
};

//Now add the feature Color to each of the 
//possible shape that could occur. Using the decorator 
//pattern, rather than creatign a class for each colored shape,
//we can write a class for colored shape inheriting from shape itself


//Using inheritance, something known as dynamic decorator
//is constructed 
struct ColoredShape : public Shape{

    //Note m_shape is an aggregate 
    //in ColoredShape
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

int main(){

    Circle c1(3.0);
    ColoredShape coloredCircle{c1, "green"};

    //Draw back of DynamicDecorator
    //coloredCircle.resize(3) is not resolved and causes error

    //This is possible because `TransparentShape` and `ColoredShape` 
    //are both `Shape`
    TransparentShape transp_greenCirc{coloredCircle, 51};
    std::cout << transp_greenCirc.str();


    Square s1(3);
    ColoredShape red_square{s1, "red"};
    TransparentShape trans_red_square{red_square, 102};
    std::cout << trans_red_square.str() << "\n";
    return 0;
}
