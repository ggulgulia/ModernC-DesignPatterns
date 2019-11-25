#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <utility>

//chain of responsibility pattern:
//A chain of components all of which gets a chance to 
//process a command or a query and optionally
//having default processing implementation and an ability to terminate the 
//process chain.

//A pointer chain, singly linked list of pointers


struct Creature{
    std::string m_name;
    int m_attack;
    int m_defence;

    Creature(const std::string& name, int attack, int defence):
        m_name(name), m_attack(attack), m_defence(defence){
                
        }

    friend std::ostream& operator<<(std::ostream& os, const Creature& creature){
        os << "creature name: " << creature.m_name 
           << " attack strength: " << creature.m_attack
           << " defence strength: " << creature.m_defence << "\n";
        return os;
    }
};


class CreatureModifier{
        
    CreatureModifier* m_next{nullptr};
    protected:
    Creature& m_creature;
    public:
    CreatureModifier(Creature& creature): m_creature(creature){     }

    void add(CreatureModifier* cm){
            if(m_next) m_next->add(cm);
            else
                m_next = cm;
    }

    virtual void handle(){
            if(m_next)
                m_next->handle();
    }

};

class DoubleAttackModifier : public CreatureModifier{
   public:
       DoubleAttackModifier(Creature& creature): CreatureModifier(creature){ }
       void handle() override{
               m_creature.m_attack *= 2;
               CreatureModifier::handle();
       }
};


class IncreaseDefenceModifier : public CreatureModifier{
    public:

        IncreaseDefenceModifier(Creature& creature): CreatureModifier(creature){ }

        void handle() override{
            if(m_creature.m_attack<=2){
                m_creature.m_defence++;
                CreatureModifier::handle();
            }
        }
};


class NoBonusesModifier : public CreatureModifier{
    public:
        NoBonusesModifier(Creature& creature): CreatureModifier(creature){ }
        void handle() override{
            
    }
};

int main(){

    Creature gbolin{"Gbolin", 1, 1};
    CreatureModifier root{gbolin};
    DoubleAttackModifier r1{gbolin};
    DoubleAttackModifier r12{gbolin};
    IncreaseDefenceModifier r2{gbolin};

    NoBonusesModifier curse{goblin};
    root.add(&curse);
    root.add(&r1);
    root.add(&r12);
    root.add(&r2);

    root.handle();

    std::cout << gbolin << "\n";
    return 0;

}
