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
