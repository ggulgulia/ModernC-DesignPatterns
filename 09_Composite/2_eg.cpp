#include <vector>
#include <algorithm>
#include <numeric>
#include <string>
#include <iostream>
#include <memory>
#include <utility>
//intersection of composite and proxy design pattern

class Creture{

    //properties of cretaures 
    int m_strength;
    int m_intelligence;
    int m_agility;

    //getters
    int get_strength()const{
        return m_strength;
    }
    int get_intelligence()const{
        return m_intelligence;
    }
    int get_agility()const{
        return m_agility;
    }

    //setters
    void set_intelligence(const int intelligence){
        m_intelligence = intelligence;
    }
    void set_strength(const int strength){
        m_strength = strength;
    }
    void set_agility(const int agility){
        m_agility = agility;
    }

    //some properties which are aggregate of the properites 
    //of a creatrures.
    //We see this is not a sclable approach because if a
    //property is added later, the aggregagte properties 
    //have to be changed completely
    int sum()const{
        return m_strength + m_intelligence + m_agility;
    }

    float average()const{
        return static_cast<float>(sum())/3.0;
    }

    int max()const{
        return std::max(std::max(m_strength, m_intelligence), m_agility);
    }
};


//composite pattern for aggregate storage of 
//properties 
class Creature2{

    //notice this is old fashioned `enum` and not 
    //`enum class` and old enums degenerate to 
    //integers
    enum Abilities{str, intl, agl, count }; //count is the terminating element, and shows the 
                                            //size of this aggregate.  length(abilities) will yield 3, 
                                            //which is the value of the member count
    std::array<int, count>m_abilities; //array backed property `m_abilities
    public:
    int get_strength()const{return m_abilities[str];}
    void set_strength(int val){m_abilities[str] = val;}

    int  get_intelligence()const{return m_abilities[intl];}
    void set_intelligence(int val){m_abilities[intl] = val;}

    int  get_agility()const{return m_abilities[agl];}
    void set_agility(int val){m_abilities[agl] = val;}

    int sum() const{
        //note using enum and std algorithms makes the data structure
        //scalable
        return std::accumulate(m_abilities.begin(), m_abilities.end(), 0);
    }

    float average()const{
        return (float)sum()/((float)count);
    }

    int max() const{
        //std::max_element gives pointer to the max element
        return *std::max_element(m_abilities.begin(), m_abilities.end());
    }

    int num() const{
        return m_abilities.size();
    }
};


int main(){

    Creature2 orc;
    orc.set_strength(30);
    orc.set_agility(19);
    orc.set_intelligence(4);

    std::cout << "The orc has an average stat of: "
              << orc.average()
              << "\nAnd a maximum stat of: "
              << orc.max() << "\n";

    std::cout << "Count of abilities of the orc creature " << orc.num() << "\n";

    return 0;
}
