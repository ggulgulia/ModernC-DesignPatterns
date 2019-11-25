#include <iostream>

class Game{
    protected:
        int numPlayers_{0};
        int currentPlayer_{0};
        virtual void start() = 0;
        virtual bool have_winner() = 0;
        virtual void take_turn() = 0;
        virtual int get_winner() = 0;
        virtual void restart() = 0;
    public:

        Game(int numPlayers): numPlayers_{numPlayers}
        { }

        void run(){
                start();
                while(!have_winner()){
                        take_turn();
                        std::cout << "Plyert " << get_winner() << " wins\n";
                }
        }
};

class Chess : public Game{
    private:
        int turn_{0};
        int max_turns{10};
    protected:
        void start() override{

            std::cout << "starting a game of chess with "
                        << numPlayers_ << " players\n";
             
        }

        bool have_winner() override{
                
            return turn_ == max_turns;
        }

        void take_turn() override{
                
            std::cout << "Turn " << turn_++ << " taken by player " 
                      << currentPlayer_ << "\n";

            currentPlayer_ = (currentPlayer_ + 1)%numPlayers_;
        }

        int get_winner() override{
            return currentPlayer_;
        }

        void restart() override{
            turn_ = 0;

        }
    public:
        Chess(): Game{2}{ }
};

int main(){

    Chess chess;
    chess.run();



    return 0;
}
