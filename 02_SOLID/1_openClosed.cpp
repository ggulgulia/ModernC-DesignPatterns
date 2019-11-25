#include <string>
#include <iostream>
#include <vector>

//Open Close Principle means that the design is Closed for modification
//but Open to extesion. 
enum class Color{red, green, blue};
enum class Size{small, medium, large};

struct Product{
    std::string m_name;
    Color m_color;
    Size m_size;
};

template<typename T> 
struct Specification{

    virtual bool is_staisfied(T* item) = 0;
};

//inherit and extend specification for colors
struct ColorSpecificiation : public Specification<Product>{

    Color m_color2;
    ColorSpecificiation(Color color) : m_color2(color){
        //empty constructor
    }

    bool is_staisfied(Product *item) override{
        return item->m_color == m_color2;
    }
};

//inherit and extend specification for size 
struct SizeSpecificiation : public Specification<Product>{

    Size m_size2;
    SizeSpecificiation(Size size) : m_size2(size){
        //empty constructor
    }

    bool is_staisfied(Product *item) override{
        return item->m_size== m_size2;
    }
};

//a template object to have two conditions to filter with
template<typename T>
struct AndSpecification : public Specification<T>
{
    Specification<T>& m_first;
    Specification<T>& m_second;

    AndSpecification(Specification<T>& first, Specification<T>& second):
        m_first{first}, m_second{second}{ }
    
    bool is_staisfied(T* item) override{
        return m_first.is_staisfied(item) && m_second.is_staisfied(item);
    }
};

template <typename T>
struct Filter{

    virtual std::vector<T*> filter(std::vector<T*> items, 
            Specification<T>& spec) = 0;

};

struct BetterFilter : public Filter<Product>{

    std::vector<Product*> filter(std::vector<Product*> items, Specification<Product>& spec) override{
            std::vector<Product*> result;
            for(auto& item : items){

                if(spec.is_staisfied(item)){
                    result.push_back(item);
                }
            }
            return result;
        }
};


int main(){

    Product apple{"apple", Color::green, Size::small};
    Product tree{"Tree", Color::green, Size::large};
    Product house{"House", Color::blue, Size::large};
    std::vector<Product*> items{&apple, &tree, &house};

    BetterFilter bf;
    ColorSpecificiation green_spec(Color::green);

    std::cout << "Using the color specification from Open-Close principle\n";
    std::cout << "Green things :\n";
    for(auto& item : bf.filter(items, green_spec)){
            std::cout << item->m_name << "\n";
    }
    


    std::cout << "Using a complicated specification to filter \"green\" and \"large\" things\n";
    SizeSpecificiation large_spec(Size::large);
    AndSpecification<Product> complicated_spec(green_spec, large_spec);

    for(auto& item : bf.filter(items, complicated_spec)){
        std::cout << item->m_name << "\n";
    }

    return 0;
}
