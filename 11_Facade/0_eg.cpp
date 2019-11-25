#include <iostream>
#include <map>
#include <vector>
#include <string>


class Window;
class Console{
    public:

    static Console& instance(){
        static Console con;
        return con;
    }

    std::vector<std::shared_ptr<Window>> wins;

    private:
    const int m_charWidth=10;
    const int m_charHeight = 14;
    Console(){  }
    Console(const Console& ){   }
};
int main(){

    return 0;
}
