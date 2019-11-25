#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <memory>
#include <string>
#include <cstdlib>


class PersonBuilder;

class Person{
    private:
        std::string m_address;
        std::string m_zipCode;
        std::string m_city;

        std::string m_company;
        std::string m_designation;
        int m_income;

        static PersonBuilder create();

        friend class PersonBuiler;
        friend class PersonJobBuilder;
        friend class PersonAddressBuilder;

};

//forward class declarations
class PersonJobBuilder;
class PersonAddressBuilder;

class PersonBuilderBase{

    protected:
        Person& m_personBase;
    public:
        PersonBuilderBase(Person& p): m_personBase(p){}

        PersonAddressBuilder lives() const;


        PersonJobBuilder works() const;
};

class PersonAddressBuilder: public PersonBuilderBase{


class PersonBuilder{

    private:
        Person m_p;
    public:
        PersonBuilder();


};
#endif /* ifndef PERSON_H */
