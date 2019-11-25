#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <memory>

class PersonBuilder;
class Person{
    private:
        std::string m_address;
        std::string m_postCode;
        std::string m_city;
    
        std::string m_companyName;
        std::string m_designation;
        int m_income = 0;

        //the default constructor 
        //is made private to prevent
        //the user from directly creating
        //the person object. This design 
        //enforces the use of builder pattern
        Person();

    public:
        ~Person();

        Person(Person&& other);
        Person& operator=(Person&& other);
        static PersonBuilder create();

        friend std::ostream& operator<<(std::ostream& os, const Person& p);

        friend class PersonBuilder;
        friend class PersonAddressBuilder;
        friend class PersonJobBuilder;

};

#endif /* PERSON_H */
