#include <Person.hpp>
#include <PersonBuilder.hpp>

Person::Person(){
    std::cout << "Person::Person()\n";
}

Person::~Person(){
    std::cout << "Person::~Person()\n";
}

Person::Person(const Person&){
    std::cout << "Person(const Person& p)\n";
}

Person::Person(Person&& p):
        m_address(p.moveAddress()),
        m_postCode(p.movePostCode()),
        m_city(p.moveCity()),
        m_companyName(p.moveCompanyName()),
        m_designation(p.moveDesignation()),
        m_income(p.getIncome())
    {       }


    PersonBuilder Person::create(){
        return PersonBuilder{};
    }

    
    Person& Person::operator=(Person&& p){

        if(this == &p){
            return *this;
        }

        m_address = p.moveAddress();
        m_postCode = p.movePostCode();
        m_city = p.moveCity();
        m_companyName = p.moveCompanyName();
        m_designation = p.moveDesignation();
        m_income = p.getIncome();

        return *this;
    }
    std::ostream& operator<<(std::ostream& out, const Person& p){
        return out << p.m_address << " "
                   << p.m_postCode << " " 
                   << p.m_city << " "
                   << p.m_companyName << " "
                   << p.m_designation << " "
                   << p.m_income <<"\n";
    }

    std::string Person::moveAddress(){
        return std::move(m_address);
    }

    std::string Person::movePostCode(){
        return std::move(m_postCode);
    }

    std::string Person::moveCity(){
        return std::move(m_city);
    }

    std::string Person::moveCompanyName(){
        return std::move(m_companyName);
    }

    std::string Person::moveDesignation(){
        return std::move(m_designation);
    }

    int Person::getIncome()const{
        return m_income;
    }

