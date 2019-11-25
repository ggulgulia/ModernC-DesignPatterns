#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>

struct Pingable{
    virtual std::string ping(const std::string& message) = 0;
};

struct Pong : public Pingable{
    std::string ping(const std::string& message) override{
        return message + " pong";
    }
};

void tryit(Pingable& pp){
    std::cout << pp.ping("ping") << "\n";
}

int main(){
    
    Pong pp;
    for(size_t i=0; i<3; ++i){
        tryit(pp);
    }
    return 0;
}
