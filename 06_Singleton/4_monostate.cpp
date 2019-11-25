#include <iostream>
#include <memory>
#include <vector>
#include <string>

class Printer
{
private:
    /* data */
    static int m_id;
public:
    Printer () = default;
    virtual ~Printer () = default;
    
    int get_id()const{return m_id;}
    void set_id(const int id){m_id = id;}
};
int Printer::m_id = 2;

int main(){

    Printer p1;
    std::cout << p1.get_id() << "\n";

    Printer p2;
    
    p2.set_id(100);
    std::cout << p1.get_id() << "\n";

    return 0;
}
