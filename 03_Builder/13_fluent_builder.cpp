#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <memory>

//some objects are simple and can be created in a single constructor call
//Not true for complicated objects. Need a lot of piece by piece ceremony

//Having a constructor with 10 constructor argument is not productive
//Instead opt for piecewise construction: use the BUILDER PATTERN

//When piecewise objct construction is complicated, provide an API
//for doing it succinctly.

class HTMLBuilder;
class HTMLElement{
    friend class HTMLBuilder;
    private: 
    std::string m_name;
    std::string m_text;
    std::vector<HTMLElement> m_elements;
    const size_t m_indentSize = 2;

    HTMLElement(){  }
    HTMLElement(const std::string name, const std::string& text) : 
        m_name(name), m_text(text){ }

    public:
    std::string str(size_t indent=0) const {
        std::ostringstream oss;
        std::string i(m_indentSize*indent, ' ');
        oss << i << "<" << m_name << ">" << "\n";
        if(m_text.size() > 0)
            oss << std::string(m_indentSize*(indent+1), ' ') << m_text << "\n";

        //the for loop below recursively
        //calls the str() method that has
        //been defined here to correctly
        //indent the constents of `m_elements`
        //within the `*this` object.
        for(const auto& e: m_elements)
            oss << e.str(indent+1);
        oss << i << "</" << m_name << ">" << "\n";

        return oss.str();
    }

    //function declaration
    //defined after the class HTMLBuilder has been defined
    static HTMLBuilder build(const std::string& root_name);
        
};


class HTMLBuilder{
    public:

    HTMLElement m_root; //toplevel element

    HTMLBuilder(const std::string& root_name){
        m_root.m_name = root_name;
    }

    //void add_child(const std::string& child_name, const std::string& child_text){
    //    m_root.m_elements.emplace_back(child_name, child_text);
    //}

    HTMLBuilder&  add_child(const std::string& child_name, const std::string& child_text){
        m_root.m_elements.emplace_back(child_name, child_text);
        return *this; //return the reference to the current element
                     //this allows for the construction of a FluentBuilder
    }
    std::string str() const {
        return m_root.str();
    }

    //this is an implicit conversion operator
    //check cpp resources on www to understand
    //what it means. But below, the call like
    //HTMLElement elem = HTMLBuilder("random root name")
    //will 'cast' , by which it means, 'return'
    //the underlying member `HTMLBuilder::m:root` which
    //is of the type `HTMLElement`
    operator HTMLElement() const {return m_root;}
};

//defining the method declared in HTMLElement struct
HTMLBuilder HTMLElement::build(const std::string& root_name){
    return {root_name};
}

int main(){

    //Can be clearly seen that the html structure is not enforced in 
    //an object oriented fashion.

    HTMLBuilder builder{"ul"};

    //With the fluent builder inplace,
    // the below two line  can be chained
    //builder.add_child("li", "hello");
    //builder.add_child("li", "hello");
    
    builder.add_child("li", "hello").add_child("li", "world");
    std::cout << builder.str() << "\n";

    auto builder2 = HTMLElement::build("ul").add_child("li", "some list").add_child("li", "more lists");

    std::cout << builder2.str() << "\n";

    std::cout << "using the implicit conversion operation to cast HTMLBuilder to HTMLElement\n";
    HTMLElement elem = HTMLElement::build("hul").add_child("..", ",,,");
    std::cout << elem.str() << "\n";
    return 0;
}
