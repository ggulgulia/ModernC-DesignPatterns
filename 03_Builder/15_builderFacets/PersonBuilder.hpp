#ifndef PERSONBUILDER_H
#define PERSONBUILDER_H

#include <Person.hpp>

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBaseBuilder{
    protected:
        Person& m_person0;
        explicit PersonBaseBuilder(Person& person0);
    public:
        operator Person() const{
            return std::move(m_person0); 
        }

        //builder facets
    PersonAddressBuilder lives() const;
    PersonJobBuilder works() const;
};

class PersonBuilder : public PersonBaseBuilder{
private:
   Person m_person1; 

public:
    PersonBuilder();
    virtual ~PersonBuilder();
};

#endif /* PERSONBUILDER_H */
