#include <PersonBuilder.hpp>
#include <PersonAddressBuilder.hpp>
#include <PersonJobBuilder.hpp>

PersonBuilderBase::PersonBuilderBase(Person& person0):
                   m_person0(person0){  }

PersonBuilder::PersonBuilder():
               PersonBuilderBase(m_person1){    }

PersonAddressBuilder PersonBuilderBase::lives()const{
    //the constructor receives the member m_person0
    //by reference and hence copies of objects are not 
    //created and the state of the instance is preserved
    return PersonAddressBuilder{m_person0};
}

PersonJobBuilder PersonBuilderBase::works()const{
    //the constructor receives the member m_person0
    //by reference and hence copies of objects are not 
    //created and the state of the instance is preserved
    return PersonJobBuilder{m_person0};
}
