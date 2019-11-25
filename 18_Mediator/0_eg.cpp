#include <iostream>
#include <string>
#include <vector>
#include <boost/signals2.hpp>

//handling events in centralized manner
//with the help of observer  and mediator pattern

struct EventData{
  virtual void print() const= 0;      
};

struct Player;
struct PlayerScoredData : public EventData{
    std::string m_playerName; 
    int m_numGoals;
    PlayerScoredData(const std::string& playerName, int numGoals):
    m_playerName{playerName}, m_numGoals{numGoals}{ }

    void print() const override{
        std::cout << m_playerName << " has scored! (their" << m_numGoals<< " goals so far)\n";
    }
};

struct Game{
    boost::signals2::signal<void(EventData*)> m_events;
};


struct Player{
    std::string m_name;
    int m_goalScored{0};
    Game& m_game;

    Player(const std::string&& name, Game& game):
        m_name(name), m_game(game){     }

    void score(){
        m_goalScored++;
        PlayerScoredData ps{m_name, m_goalScored};
        m_game.m_events(&ps);
    }

};

struct Coach{
    
    Game& m_game;
    Coach(Game& game):m_game{game}{     
        m_game.m_events.connect([](EventData* e){ 
                PlayerScoredData* ps = dynamic_cast<PlayerScoredData*>(e);
                if(ps && ps->m_numGoals < 3){
                    std::cout << "coach says well done, " << ps->m_playerName << "!\n";
                }
                });
    }
};
int main(){

    Game game;
    Player p1{"sam", game};
    Coach coach{game};
    p1.score();
    p1.score();
    p1.score();
    p1.score();
    
    return 0;
}
