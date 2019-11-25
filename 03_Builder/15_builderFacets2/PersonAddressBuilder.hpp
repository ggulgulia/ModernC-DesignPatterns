#ifndef PERSONADDRESSBUILDER_H
#define PERSONADDRESSBUILDER_H

#include <PersonBuilder.hpp>

class PersonAddressBuilder : public PersonBuilderBase
{
private:
    
    typedef PersonAddressBuilder self;

public:
    explicit PersonAddressBuilder(Person& p);
    virtual ~PersonAddressBuilder()=default;
    self&  at(const std::string& address);
    self& withPostCode(const std::string& postCode);
    self& in(const std::string& city);

};

#endif /* PERSONADDRESSBUILDER_H */
