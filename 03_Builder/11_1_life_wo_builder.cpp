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



//LIFE WITHOUT BUILDER PATTERN
//Manually adding the HTML signatures 
//in the code. 
int main(){

    auto text = "hello";
    std::string output;
    output += "<p>";
    output += text;
    output += "</p>";

    std::cout << output << "\n";

    std::string words[] = {"hello", "world"};
    std::ostringstream oss;
    oss << "<ul>";
    for(auto w : words){
        oss << " <li> " << w << "</li>";

    }

    oss << "</ul>" ;
    std::cout << oss.str() << "\n";

    //Can be clearly seen that the html structure is not enforced in 
    //an object oriented fashion.

    return 0;
}
