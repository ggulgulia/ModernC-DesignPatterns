#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <utility>


//Proxy pattern is used as in interfact to a particular resource
//That resource may be expensive to construct or may require logging
//or some other added functionality.


//Proxy pattern allows to defer object creation and object initialization to 
//the time when the object is actually needed.
//this reduces the cost of accesing objects since:
//1. proxy acts as a stand in for the real object
//2. proxy creates the real object only if the user asks for it
//Proxy patten provides location transparency.

struct BankAccount{

    virtual ~BankAccount() = default;
    virtual void deposit(int amount) = 0;
    virtual void withdraw(int amount)=0;
};

struct CurrentAccount : public BankAccount{
    int m_balance;
    explicit CurrentAccount(const int bal):
        m_balance(bal){     }

    void deposit(int amount) override{
        m_balance += amount;
    }

    void withdraw(int amount) override{
        if(m_balance >= amount){
            m_balance -= amount;
        }
        else
            m_balance = 0;
    }

    friend std::ostream& operator<<(std::ostream& os, CurrentAccount ca){
        return os << "available balance in Current Account : " << ca.m_balance <<"\n";
    }
};

int main(){

    BankAccount* first = new CurrentAccount(2000);
    first->deposit(100);
    std::cout << first;

    auto second = std::make_shared<CurrentAccount>(3000);
    second->withdraw(123);
    std::cout << second; 
    return 0;
}
