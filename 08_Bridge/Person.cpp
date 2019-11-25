#include "Person.hpp"

class Person::PersonImpl{
    public:
        void greet(Person* p);
    private:
};

void Person::PersonImpl::greet(Person* p){
    std::cout << "Hello, my name is " << p->m_name << "\n";
}

Person::Person():m_impl(new PersonImpl){    }
Person::~Person(){delete m_impl;}
void Person::greet(){m_impl->greet(this);}
