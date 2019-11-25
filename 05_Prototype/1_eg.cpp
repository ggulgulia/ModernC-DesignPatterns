#include <iostream>
#include <memory>
#include <string>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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
    private:
        friend class boost::serialization::access;
        
        template<class archive>
        void serialize(archive& ar, const unsigned int version){
            ar& m_street;
            ar& m_city;
            ar& m_suite;
        }
};

struct Contact{
    Contact () = default;
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

    private:
        friend class boost::serialization::access;
        
        template<class archive>
        void serialize(archive& ar, const unsigned int version){
            ar& m_name;
            ar& m_address;
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

    auto clone = [](const Contact& c){
        std::ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << c;
        std::string s = oss.str();
        std::cout << s << "\n";

        std::istringstream iss(s);
        boost::archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;
        return result;
    };

    auto John = EmployeeFactory::new_main_office_employee("John", 234);
    auto Jane = clone(*John);

    return 0;

}
