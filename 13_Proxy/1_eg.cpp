#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>

//This is property proxy
//can be used instead of getters and setters
//coded into the class and being coded 
//in the Property<T> struct
template<typename T>
struct Property{
    T m_value;
    Property(T val){
        *this = val; //this needs assignment
                     //operator overloaded
                    //as overloaded 
    }

    T operator=(T new_val){
        std::cout << "assignment operator\n";
        return (m_value = new_val);
    }

    operator T(){
        return m_value;
    }
};

struct Creature{
    Property<int> m_strength{0};
    Property<int> m_agility{0};

    int get_strength(){
        return m_strength;
    }
    int get_(){
        return m_agility;
    }
};
int main(){
    Creature c1;
    c1.m_strength =10;
    return 0;
}
