#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <memory>
#include <iostream>

class PersonBuilder;
class Person
{
private:
    
    std::string m_address;
    std::string m_postCode;
    std::string m_city;

    std::string m_companyName;
    std::string m_designation;
    int m_income = 0;

    Person();

public:
    ~Person();
    Person(const Person&);
    Person(Person&& p);

    static PersonBuilder create();

    Person& operator=(Person&& p);
    friend std::ostream& operator<<(std::ostream& out, const Person& p);

    std::string moveAddress();
    std::string movePostCode();

    std::string moveCity();
    std::string moveCompanyName();
    std::string moveDesignation();
    int getIncome()const;

    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};

#endif /* PERSON_H */
