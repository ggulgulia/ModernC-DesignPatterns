#include <iostream>
#include <string>
#include <vector>
#include <memory>

//shapes - circle, sqaure, rectangle
//Rendereer - raster, vector

//bridge avoids creating cartesian product, i.e a 2x2 renderer
//RasterCircle, Raster Square
//vectorCircle, vectorSquare


struct Renderer{

    virtual void render_circle(float x, float y, float radius) = 0;
    virtual void render_square(float x, float y, float length) = 0;
    virtual void rander_rectangle(float x, float y, float length, float width) =0;

};

struct VectorRenderer : Renderer{

    void render_circle(float x, float y, float radius) override{
        std::cout << "Drawing a vector cricle of radius " << radius << "\n";
    }
    virtual void render_square(float x, float y, float length) override{
        std::cout << "Drawing a vector square of edge length " << length << "\n";
    }
    virtual void rander_rectangle(float x, float y, float length, float width) override{
        std::cout << "Drawing a vector square of edge length " << length 
                  << " and width of " << width << "\n";
    }

};

struct RasterRenderer : Renderer{

    void render_circle(float x, float y, float radius) override{
        std::cout << "rasterising a circle of radius " << radius <<"\n";
    }
    virtual void render_square(float x, float y, float length) override{
        std::cout << "rastering a square of edge length " << length << "\n";
    }
    virtual void rander_rectangle(float x, float y, float length, float width) override{
        std::cout << "rastering a square of edge length " << length 
                  << " and width of " << width << "\n";
    }

};

struct Shape{
    protected:
        Renderer& m_renderer;
        Shape(Renderer& renderer): m_renderer(renderer){    }
    public:
       virtual void draw() = 0;
       virtual void resize(float factor) = 0;
};

struct Circle : public Shape{
    float m_x;
    float m_y;
    float m_radius;

    Circle(Renderer& renderer, float x, float y, float radius): Shape(renderer),
    m_x(x), m_y(y), m_radius(radius){
    }

    void draw() override{
        m_renderer.render_circle(m_x, m_y, m_radius);
    }

    void resize(float factor) override{
        m_radius *= factor;
    }
};

int main(){

    RasterRenderer rr;
    Circle rast_circ(rr , 4,4,4);
    rast_circ.resize(3);
    rast_circ.draw();
    return 0;
}
