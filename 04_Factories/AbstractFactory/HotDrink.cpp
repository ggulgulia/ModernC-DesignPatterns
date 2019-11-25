#include <HotDrink.hpp>

void Tea::Prepare(int volume){
    int halfVol = volume*0.5;
    std::cout << "Add tea leaves " << halfVol << " ml of milk and" 
              << halfVol << " water, sugar to taste and enjoy\n";
}

void Coffee::Prepare(int volume){
    std::cout << "Crush coffee beans, add " << volume 
              << "ml of hot water , and some cream and enjoy\n";
}
