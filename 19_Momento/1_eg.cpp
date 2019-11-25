#include <iostream>
#include <memory>
#include <vector>

class Memento{
    private:
        int m_balance;
    public:
        Memento(int bal):
            m_balance{bal}{     }

    friend class BankAccount;
    friend class BankAccount2;
};

class BankAccount{
    private:
        int m_balance{0};
    public:
        BankAccount(int balance):
            m_balance{balance}{     }

        Memento  deposit(int amt){
           m_balance += amt;
           return {m_balance };
        }

        void restore(const Memento& m){
                m_balance = m.m_balance;
        }


        friend std::ostream& operator<<(std::ostream& os, const BankAccount& ba){
            os << "Balance in bank account: " << ba.m_balance << "\n";
            return os;
        }
};

class BankAccount2{
  
    private:
        int m_balance{0};
        size_t m_current{0};
        std::vector<std::shared_ptr<Memento>> m_changes;
    public:
        BankAccount2() = default;
        BankAccount2(const int bal): m_balance{bal} 
        { 
            //the starting balance at m_current = 0 is recorded
            m_changes.emplace_back(std::make_shared<Memento>(m_balance));
            m_current = 0;
        }

        void deposit(int amt){
           m_balance += amt;
           auto m = std::make_shared<Memento>(m_balance);
           m_changes.push_back(m);
           ++m_current;
        }

        void restore(const std::shared_ptr<Memento>& m){
            if(m){
                m_balance = m->m_balance;
                m_changes.push_back(m); //record the current change
                m_current = m_changes.size()-1; //set the current pointer to the
                                                //one where memento has been used,
                                                //i.e. the top of the container

            }
        }

        std::shared_ptr<Memento> undo(){
            if(m_current > 0){
                auto m = m_changes[--m_current];
                m_balance = m->m_balance;
                return m;
            }

            else
                return {};
        }

        std::shared_ptr<Memento> redo(){
            if(m_current < m_changes.size()-1){
                m_current++;
                auto m = m_changes[m_current];
                m_balance = m->m_balance;
                return m;
            }
            else
                return {};
        }

        friend std::ostream& operator<<(std::ostream& os, BankAccount2 ba){
            os << "current bank balance is: " << ba.m_balance << " euros\n";
            return os;
        }
};

int main(){

    BankAccount2 ba{1000};
    ba.deposit(34);
    ba.deposit(100);

    std::cout << ba;

    std::cout << "undo1 :";
    ba.undo();
    std::cout << ba;
    
    std::cout << "undo2 :";
    ba.undo();
    std::cout << ba;


    std::cout << "redo1 :";
    ba.redo();
    std::cout << ba;


    std::cout << "redo2 :";
    ba.redo();
    std::cout << ba;
    return 0;
}
