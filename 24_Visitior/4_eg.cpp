#include <iostream>
#include <tuple>
#include <map>
#include <sstream>
#include <typeindex>

//Multimethod.
//This could be a possible technique to avoid double dispatch

struct GameObjcet;
void collide(GameObjcet& first, GameObjcet& second);
struct GameObjcet{
    
    virtual std::type_index type() const = 0;
    virtual void collide(GameObjcet& other){
        //this is the global scope resolution
        ::collide(*this, other);
    }
};

template <typename T> 
struct GameObjcetImpl : public GameObjcet{
    std::type_index type() const override{
            
        return typeid(T);
    }
};

//for the purpose of demonstration, this
//CRTP creates a type for which a type_index
//could be created and later be mapped to 
//appropriate function calls
struct Planet : public GameObjcetImpl<Planet>{
        
};

struct Asteroid : public GameObjcetImpl<Asteroid>{
        
};

struct SpaceShip : public GameObjcetImpl<SpaceShip>{
        

};

void spaceship_planet() {
    std::cout << "space ship lands on a planet\n";
}

void asteroid_planet(){
    std::cout <<"asteroid burns up in the atmosphere\n";
}

void asteroid_spaceship(){
    std::cout << "space ship is destroyed by the asteroid\n";
}

std::map<std::pair<std::type_index, std::type_index>, void(*)(void)> outcomes{
                                                                                {{typeid(SpaceShip), typeid(Planet)}, spaceship_planet},
                                                                                {{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
                                                                                {{typeid(Asteroid), typeid(SpaceShip)}, asteroid_spaceship}
                                                                             };

void collide(GameObjcet& first, GameObjcet& second){
    auto it = outcomes.find({first.type(), second.type()});

    //if not found, check in reverse combination
    if(it == outcomes.end()){
        it = outcomes.find({second.type(), first.type()});
        
        //if still not found, the objects are allowed
        //to pass each other harmlessly
        if(it == outcomes.end()){
            std::cout << "objects pass each other harmlessly\n";

            //we still need to return else
            //there's a segmentation fault
            return;
        }
    }
        //calls the appropriate function
        return it->second();
}
int main(){

    SpaceShip sp;
    Asteroid as;
    Planet pl;

    collide(pl, as);
    collide(pl, sp);
    collide(sp, as);
    collide(sp, sp);
    return 0;
}
