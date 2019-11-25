#include <PersonBuilder.hpp>
#include <PersonAddressBuilder.hpp>
#include <PersonJobBuilder.hpp>

PersonBaseBuilder::PersonBaseBuilder(Person& person0):
    m_person0(person0){     }

PersonAddressBuilder PersonBaseBuilder::lives() const{
    return PersonAddressBuilder{m_person0};
}

PersonJobBuilder PersonBaseBuilder::works()const{
    return PersonJobBuilder{m_person0};
}

//the member `PersonBuilder::m_person1` is passed by reference
//to the parent. PersonBuilder can call the default constructor 
//`Person::Person()` since `PersonBuilder` has been declared
//as a friend class in `Person`
PersonBuilder::PersonBuilder():PersonBaseBuilder{m_person1}{    }
PersonBuilder::~PersonBuilder(){  }
