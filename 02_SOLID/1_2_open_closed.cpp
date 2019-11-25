#include <iostream>
#include <vector>
#include <memory>
#include <string>

enum class Color{red, green, blue};
enum class Size{small, medium, large};

struct Product{

    std::string m_name;
    Color m_color;
    Size m_size;
    Product(std::string name, Color col, Size size):
        m_name(name), m_color(col), m_size(size)
    { }

    Product(const Product&) = delete;
};


//type def to get rid of ugly name
typedef std::shared_ptr<Product> ProdPtr;
typedef std::vector<ProdPtr> ProdContainer; 

//bad way of making a product filter as this will require the same class object to be 
//modified over and again. This violates the "Open Closed Principle"
class ProductFilter{

    public:
        static ProdContainer by_color(const ProdContainer& items, Color col){

             ProdContainer result;
            for(const auto& item : items){
                if(item->m_color == col){
                    result.push_back(item);
                }
            }    
            return result;
        }
};


template <typename T>
struct Specification{
    virtual bool is_satisfied(const std::shared_ptr<T>& item)const = 0;
};

struct ColorSpec : public Specification<Product>{

    Color m_color2;
    ColorSpec(const Color& col):m_color2{col}{  }

    bool is_satisfied(const ProdPtr& prod)const override{
        return prod->m_color == m_color2;
    }
};


struct SizeSpec : public Specification<Product>{
    
    Size m_size2;
    SizeSpec(const Size& size): m_size2{size}{  }
    bool is_satisfied(const ProdPtr& prod)const override{
        return prod->m_size == m_size2;
    }
};


template <typename T>
struct Filter{

    typedef std::shared_ptr<T> shared_t;
    typedef std::vector<shared_t> vector_shared_t;

    virtual vector_shared_t filter(const vector_shared_t&, const Specification<T>& spec) = 0;
};


struct ProductFilter2 : public Filter<Product>{
    
    ProdContainer filter(const ProdContainer& items, const Specification<Product>& spec) override{
        ProdContainer result;
        for(const auto item : items){
            if(spec.is_satisfied(item)){
                result.push_back(item);
            }
        }

        return result;
    }
};

int main(){

    ProdPtr apple = std::make_shared<Product>("apple", Color::green, Size::small);
    ProdPtr car = std::make_shared<Product>("BMW", Color::blue, Size::medium);
    ProdPtr house = std::make_shared<Product>("Villa", Color::blue, Size::large);
    ProdPtr handy  = std::make_shared<Product>("samsung", Color::blue, Size::small);
    ProdPtr laptop  = std::make_shared<Product>("Acer", Color::blue, Size::small);
    ProdPtr tree = std::make_shared<Product>("Bonsai", Color::green, Size::small);

    ProdContainer items{std::move(apple), std::move(car), std::move(house),std::move(handy), 
                        std::move(laptop), std::move(tree)};
    
    for(const auto item : items){
        std::cout << "Product name " << item->m_name << "\n";
    }

    ProductFilter blueFilter, greenFilter;
    ProdContainer blueThings = blueFilter.by_color(items, Color::blue);
    ProdContainer greenThings = greenFilter.by_color(items, Color::green);

    std::cout << "Printing the blue things in the list of above product:\n";
    for(const auto item : blueThings){
        std::cout << "Product name " << item->m_name << "\n";
    }

    std::cout << "Printing the green things in the list of above product:\n";
    for(const auto item : greenThings){
        std::cout << "Product name " << item->m_name << "\n";
    }


    ProductFilter2 pf2;
    ColorSpec blueColSpec{Color::blue};
    SizeSpec  smallSizeSpec(Size::small);

    std::cout << "using \"OPEN CLOSED PRINCIPLE\" for filtering\n";
    std::cout << "Filtering BLUE things using OCP\n";
    for(const auto item : pf2.filter(items, blueColSpec)){
        std::cout << "Product name " << item->m_name << "\n";
    }

    std::cout << "Filtering SMALL things using OCP\n";
    for(const auto item : pf2.filter(items, smallSizeSpec)){
        std::cout << "Product name " << item->m_name << "\n";
    }

    


    return 0;
}
