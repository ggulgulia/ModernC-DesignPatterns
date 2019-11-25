#include <Person.hpp>
#include <PersonBuilder.hpp>

Person::Person(){
    std::cout << "Person::Person()\n";
}

Person::~Person(){
    std::cout << "Person::~Person()\n";
}

Person::Person(Person&& other):
    m_address(std::move(other.m_address)),
    m_postCode(std::move(other.m_postCode)),
    m_city(std::move(other.m_city)),
    m_companyName(std::move(other.m_companyName)),
    m_designation(std::move(other.m_designation)),
    m_income(std::move(other.m_income))
{
}

Person& Person::operator=(Person&& other){

    if(this == &other)
        return *this;

    m_address = other.m_address;
    m_postCode = other.m_postCode;
    m_city = other.m_city;
    m_companyName = other.m_companyName;
    m_designation = other.m_designation;
    m_income = other.m_income;

    return *this;
}

std::ostream& operator<<(std::ostream& os, const Person& p){

    return os << "address: " << p.m_address
           << "\nPostal Code: " << p.m_postCode 
           << "\nCity: " << p.m_city
           << "\nCompany Name: " << p.m_companyName
           << "\nDesignation: " << p.m_designation
           << "\nAnnual Income: " << p.m_income;
}

PersonBuilder Person::create(){
    return PersonBuilder{};
}
