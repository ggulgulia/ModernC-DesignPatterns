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

struct HTMLElement{
    std::string m_name;
    std::string m_text;
    std::vector<HTMLElement> m_elements;
    const size_t m_indentSize = 2;

    HTMLElement(){  }
    HTMLElement(const std::string name, const std::string& text) : 
        m_name(name), m_text(text){ }

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
        
};


struct HTMLBuilder{

    HTMLElement m_root; //toplevel element

    HTMLBuilder(const std::string& root_name){
        m_root.m_name = root_name;
    }

    void add_child(const std::string& child_name, const std::string& child_text){
        m_root.m_elements.emplace_back(child_name, child_text);
    }

    std::string str() const {
        return m_root.str();
    }
};

//LIFE WITHOUT BUILDER PATTERN
//Manually adding the HTML signatures 
//in the code. 
int main(){

    //Can be clearly seen that the html structure is not enforced in 
    //an object oriented fashion.

    HTMLBuilder builder{"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "hello");

    std::cout << builder.str() << "\n";
    return 0;
}
