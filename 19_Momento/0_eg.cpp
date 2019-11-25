//The intent of momento pattern is :
//"without violating encapsulation, capture and externalize
//an objects internal state so that the object can be restored
//to this state later [GoF]

//Momento Design patten solve problems like:
//- without violating encapsulation, how can an objects 
//internal state be captured and externalized, so that 
//the object can be restroed to this state later?
//A direct access to object's data structure is not possible
//because this would break its encapsulation


//A token returned from the system's API saves the state
//of the needed/requisite encapsulated object at the 
//instance the token is generated

#include <iostream>

class Memento{
    private:
        int m_bal2{};
    public:
        Memento(const int bal):m_bal2{bal} { }

        //a friend class can access 
        //all private members of the class 
        //of which it is a friend
        friend class BankAccount;
};

class BankAccount{

    private:
        int m_balance{};

    public:
        BankAccount() = default;
        BankAccount(const int bal): m_balance{bal}{     }

        Memento deposit(const int amt){
            m_balance += amt;

            //inetent of memento pattern is to 
            //save the state before the amt 
            //is deposited
            return {m_balance-amt};
        }

        void restore(const Memento mem){
                m_balance = mem.m_bal2;
        }


        friend std::ostream& operator<<(std::ostream& os, const BankAccount ba){
                os << "current balance in bank account: " << ba.m_balance << " euros\n";
                return os;
        }
};

int main(){

    BankAccount ba1{1005};
    auto m1 = ba1.deposit(120);
    auto m2 = ba1.deposit(11);

    std::cout << ba1;
    ba1.restore(m1);
    std::cout << ba1;
    ba1.restore(m2);

    return 0;
}
