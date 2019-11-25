#include <tuple>
#include <iostream>
#include <vector>
#include <cmath>

static constexpr double pi = 3.14151;

class Point
{
private:
    /* data */

    double m_x{0.0};
    double m_y{0.0};

    //the constructor is made private so that
    //clients of Point cannot directly access/create
    //the Point object directly rather are foreced to use
    //some other means of object creation 
    //(like Point::PointFactory) 
    Point(double x, double y):
        m_x(x), m_y(y){     }
public:

    friend std::ostream& operator<<(std::ostream& os, const Point &pnt){
        return os << "x: " << pnt.m_x << " y: " << pnt.m_y << "\n";
        
    }

private:
    //creating an inner class called PointFactory
    //The inner class, irrespective of its specifier
    //can access all private and public members 
    //of the outer class
    class PointFactory{
        private:
            PointFactory(){ };
    public:

    static Point NewCartesian(double x, double y){
        return {x,y};
    }

    static Point NewPolar(double r, double theta){
        return {r*sin(theta), r*cos(theta)};
    }

};
 
public:
//a singleton to expose a single instance 
//of `PointFactory`
static PointFactory Factory;

};


int main(){

    Point p1 = Point::Factory.NewCartesian(10, -10);
    Point p2 = Point::Factory.NewPolar(10, pi/4.0);
    std::cout << p1;
    std::cout << p2;
    
    return 0;
}
