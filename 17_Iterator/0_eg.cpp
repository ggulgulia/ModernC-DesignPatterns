#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <memory>
//Iterator pattern facilitates the traversal
//of different data structures. Core functionality of various
//data structures

//Iterator keeps a reference to the current element
//Iterator knows how to move to a different element

//Iterator can be used implicitly like in range based for loops and corutines


int main(){
        
    std::vector<std::string> names{"john", "jane", "jill", "jack"};
    std::vector<std::string>::iterator it = names.begin(); //begin(names)

    std::cout << *it << "\n";

    ++it;
    it->append(" goodaall");
    std::cout << *it << "\n";


    while(++it != names.end()){
        std::cout << *it << " ";
    }

    std::cout << "\n";
    for(auto ri = names.rbegin(); ri != names.rend(); ++ri){
        std::cout << *ri ;
        if(ri+1 != names.rend()) std::cout << ", ";
    }
    std::cout << "\n";


    //std::vector<std::string>::const_reverse_iterator jack = names.crbegin();
    //*jack += std::string(" reacher); // not allowed
    
    for(auto&& name : names){
        std::cout << "names = " << name <<"\n";
    }
    return 0;
}
