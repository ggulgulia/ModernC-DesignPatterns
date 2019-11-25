#ifndef PERSONADDRESSBUILDER_H
#define PERSONADDRESSBUILDER_H

#include <PersonBuilder.hpp>

class PersonAddressBuilder: public PersonBaseBuilder{

public:

    typedef PersonAddressBuilder self; 
    explicit PersonAddressBuilder(Person& person);
    self& at(const std::string& address);

    self& with_postCode(const std::string& postCode);

    self& in(const std::string& city);
    virtual ~PersonAddressBuilder() = default;
};

#endif /* PERSONADDRESSBUILDER_H */
