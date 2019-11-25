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

    void withdraw(int amt){
            if(m_balance - amt >= m_overdraftLimit){
                    m_balance -= amt;
                std::cout << "withdrawn " << amt
                          << " new balance: " << m_balance << "\n";
            }
    }
};


struct Command{
        virtual void call() = 0;
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
                 break;
            case Action::withdraw:
                 m_acc.withdraw(m_amt);
                 break;
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
        std::cout << "\n";
    }

    return 0;
}
