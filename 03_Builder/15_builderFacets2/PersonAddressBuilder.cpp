#include <PersonAddressBuilder.hpp>

typedef PersonAddressBuilder self;

PersonAddressBuilder::PersonAddressBuilder(Person& p):
                      PersonBuilderBase{p}{     }

self& PersonAddressBuilder::at(const std::string& address){
    m_person0.m_address = address;
    return *this;
}

self& PersonAddressBuilder::withPostCode(const std::string& postCode){
    m_person0.m_postCode = postCode;
    return *this;
}

self& PersonAddressBuilder::in(const std::string& city){
    m_person0.m_city = city;
    return *this;
}

