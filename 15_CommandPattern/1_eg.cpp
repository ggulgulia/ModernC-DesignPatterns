#include <vector>
#include <iostream>

struct BankAccount{
    int m_balance{0};
    int m_overdraftLimit{-500};

    void deposit(int amt){
        m_balance += amt;
        std::cout << "deposited " << amt
                  << " new balance: " << m_balance << "\n";
    }

    bool withdraw(int amt){
            if(m_balance - amt >= m_overdraftLimit){
                m_balance -= amt;
                std::cout << "withdrawn " << amt
                          << " new balance: " << m_balance << "\n";
                return true;
            }
            return false;
    }
};


struct Command{
        virtual void call() = 0;
        virtual void undo() = 0;
        bool m_succeeded;
};

struct BankAccountCommand : public Command{
    
    BankAccount& m_acc;
    enum Action{deposit, withdraw} m_action;
    int m_amt;

    BankAccountCommand(BankAccount& acc, Action action, const int amt):
        m_acc(acc), m_action(action), m_amt(amt){   }

    void call() override{
        switch(m_action){

            case Action::deposit:
                 m_acc.deposit(m_amt);
                 m_succeeded = true;
                 break;
            case Action::withdraw:
                 m_succeeded = m_acc.withdraw(m_amt);
                 break;
        }
    }

    void undo() override{
        if(m_succeeded){
            switch(m_action){
                case Action::deposit:
                    m_acc.withdraw(m_amt);
                    break;
                case Action::withdraw:
                    m_acc.deposit(m_amt);
            }
        }
            
    }
};

int main(){
    
    BankAccount ba1;

    std::vector<BankAccountCommand> commands{
                                        BankAccountCommand{ba1, BankAccountCommand::deposit, 100},
                                        BankAccountCommand{ba1, BankAccountCommand::withdraw, 200}
                                       };

    for(auto& cmd : commands){
        cmd.call();
    }

    std::cout << "\n";
    
    for(auto it = commands.rbegin(); it != commands.rend(); ++it){
        it->undo();
    }

    return 0;
}
