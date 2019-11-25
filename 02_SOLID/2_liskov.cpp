#include <iostream>

class Rectangle{

    protected:
        double m_width;
        double m_height;

    public:
        Rectangle(const double width, const double height):
            m_width(width), m_height(height){   }

        double get_width() const{
            return m_width;
        }

        double get_height() const{
            return m_height;
        }

        virtual void set_width(const double width){
            m_width = width;
        }

        virtual void set_height(const double height){
            m_height = height;
        }

        double area()const{
            return (m_width*m_height);
        }
};


class Square : public Rectangle{
    public:
        Square(const double size):
            Rectangle(size, size){  }

        void set_width(const double width) override{
            this->m_width = this->m_height = width;
        }

        void set_height(const double height)override{
            this->m_width = this->m_height = height;
        }

};

void process(Rectangle& r){
    double w = r.get_width();
    r.set_height(10.0);

    std::cout << "expected area = " << (w*10.0);
    std::cout << "\ngot " << r.area() << "\n";
}



int main()
{

    Rectangle r1{3,4};
    process(r1);

    Square s1{6};
    process(s1);
    return 0;
}
