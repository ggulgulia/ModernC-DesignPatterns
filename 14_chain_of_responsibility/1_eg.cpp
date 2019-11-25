#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <boost/signals.hpp>

//a class we can request some 
//information about the creature
struct Query{
        std::string m_creatureName;
        enum Argument{attack, defence} m_argument;
        int m_result;

        Query(const std::string& creatureName, Argument argument, 
              int result):
            m_creatureName{creatureName}, m_argument{argument}, m_result{result}{ }

};

struct Game{
        
    //a void function which takes a 
    //`Query` reference
    boost::signal<void(Query&)> m_queries;
};

class Creature{
    private:
    Game& m_game;
    int m_attack;
    int m_defence;
    std::string m_name;

    public:
    Creature(Game & game, int attack, int defence, const std::string& name):
        m_game(game), m_attack(attack), m_defence(defence), m_name(name){ }
        
    int get_attack()const{
        Query q{m_name, Query::Argument::attack, m_attack};
        m_game.m_queries(q);
        return q.m_result;
    }

    int get_defence() const{
        Query q{m_name, Query::Argument::defence, m_defence};
        m_game.m_queries(q);
        return q.m_result;
    }

    std::string get_name()const{
        return m_name;
    }

    void set_attack(const int attack){
        m_attack = attack;
    }

    void set_defence(const int defence){
        m_defence = defence;
    }

    friend std::ostream& operator<<(std::ostream& os, const Creature& creature){
        os << " attack: " << creature.get_attack() 
           << " defence: " << creature.get_defence() << " name " << creature.m_name <<"\n";
        return os;
    }
};

class CreatureModifier{
        private:
            Game& m_game;
            Creature& m_creature;
        public:
            CreatureModifier(Game& game, Creature& creature):
                m_game{game}, m_creature{creature}{     }
            virtual ~CreatureModifier() = default;

};

class DoubleAttackModifier : public CreatureModifier{
        public:
            DoubleAttackModifier(Game& game, Creature& creature):
                CreatureModifier(game, creature){
            
                game.m_queries.connect([&](Query& q){
                    if(q.m_creatureName == creature.get_name() &&
                       q.m_argument == Query::Argument::attack){
                            q.m_result *= 2;
                    }
                });
            }
};

int main(){

    
    return 0;
}
