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

    friend std::ostream& operator<<(std::ostream& os, const BankAccount& ba){
        os << "balance in account: " << ba.m_balance << "\n";
        return os;
    }
};


struct Command{
        virtual void call() = 0;
        virtual void undo() = 0;
        bool m_succeeded{false};
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
                 this->m_succeeded = m_acc.withdraw(m_amt);
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

struct CompositeBankAccountCommand : public Command{
    protected:
        std::vector<BankAccountCommand> m_commands;
    public: 
        CompositeBankAccountCommand(const std::initializer_list<BankAccountCommand>& items): 
            m_commands{items}{  }

        void call() override{
            for(auto& cmd : m_commands){
                cmd.call();
    }

        }

        void undo() override{
            for(auto it = m_commands.rbegin(); it != m_commands.rend(); ++it){
                it->undo();
            }
        }
};

struct DependentCompositeCommand : public CompositeBankAccountCommand{
   DependentCompositeCommand(const std::initializer_list<BankAccountCommand>& items):
       CompositeBankAccountCommand(items){ }
   void call() override{
        bool ok{true};
        for(auto cmd : m_commands){
            if(ok){
                cmd.call();
                ok = cmd.m_succeeded;
            }
            else {
             cmd.m_succeeded = false;       
            }
        }
   }
};

struct MoneyTransferCommand : public DependentCompositeCommand{

    MoneyTransferCommand(BankAccount& from, BankAccount& to, const int amt):
        DependentCompositeCommand{{BankAccountCommand{from, BankAccountCommand::withdraw, amt},
                                    BankAccountCommand{to, BankAccountCommand::deposit, amt}
                                    }}
    {   }
};

int main(){
    
    BankAccount ba1, ba2;
    ba1.deposit(11100);
    
    MoneyTransferCommand cmd{ba1, ba2, 5000};
    cmd.call();

    std::cout << ba1 << ba2;
    std::cout << "\n";
    cmd.undo();
    std::cout << ba1 << ba2;

    return 0;
}
