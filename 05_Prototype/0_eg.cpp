#include <iostream>
#include <memory>
#include <string>

struct Address{
    std::string m_street;
    std::string m_city;
    int m_suite;
    Address() = default;
    Address(const std::string& street, const std::string& city, const int suite):
        m_street(street), m_city(city), m_suite(suite){     }
    
    Address(const Address& other):m_street(other.m_street),
                                  m_city(other.m_city),
                                  m_suite(other.m_suite){
                                    std::cout << "Address(const Address&)\n";
                                  }
    friend std::ostream& operator<<(std::ostream& os, Address& add){
        return os << "\nStreet: " << add.m_street << "\nCity: " << add.m_city
                  << "\nSuite : " << add.m_suite;
    }
};

struct Contact{
    std::string m_name;
    Address *m_address = nullptr;
    Contact(const std::string& name, Address*const address):
        m_name(name), m_address(address){   }

    Contact(const Contact& other):m_name(other.m_name)
        ,m_address(new Address(*other.m_address)){
        std::cout << "Contact(const Contact&)\n";

    }

    friend std::ostream& operator<<(std::ostream& os, Contact& cont){
        return os << "Name: " << cont.m_name 
                  << "\nAddress: " << *cont.m_address << "\n";
    }
};


class EmployeeFactory{
    private:
        static std::unique_ptr<Contact> new_employee(const std::string name,
                                                const int suite,
                                                const Contact& prototype){
            auto result = std::make_unique<Contact>(prototype);
            result->m_name = name;
            result->m_address->m_suite = suite;
            return result;
        }
    public :
        static std::unique_ptr<Contact> new_main_office_employee
                                        (const std::string& name, const int suite)
        {
            static Contact p{"", new Address{"123 East Dr", "London", 0}};
            return new_employee(name, suite, p);
         }

};

int main(){

    Contact john{"John Doe", new Address{"124, West St", "Berlin", 23}};
    Contact jane = john;
    jane.m_name = "Jane Smith";
    jane.m_address->m_suite = 103;
    std::cout << john << "\n" <<jane ;

    return 0;
}
