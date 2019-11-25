#ifndef PERSONBUILDER_H
#define PERSONBUILDER_H

#include <Person.hpp>

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
    Person& m_person0;

    explicit PersonBuilderBase(Person& person0);

public:
    virtual ~PersonBuilderBase() = default;

    operator Person() const{
    return std::move(m_person0);
}

    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;

};


class PersonBuilder: public PersonBuilderBase
{
private:
//since PersonBuilder is a friend class of Person
//it can access all private members of Person object
//and hence the default constructor too, enabling it 
//to instantiate a Person 
    Person m_person1;
public:
    //this constructor passes the member variable to its
    //parent class `PersonBuilderBase` by reference.
    PersonBuilder();
    virtual ~PersonBuilder()=default;
};

#endif /* PERSONBUILDER_H */
