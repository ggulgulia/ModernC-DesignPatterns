#ifndef PERSONJOBBUILDER_H
#define PERSONJOBBUILDER_H

#include <PersonBuilder.hpp>
class PersonJobBuilder : public PersonBuilderBase
{
private:
    typedef PersonJobBuilder self;

public:
    PersonJobBuilder(Person& p);
    virtual ~PersonJobBuilder() = default;

    self& working_at(const std::string& companyName);
    self& as(const std::string& designation);
    self& earning(const int income);
};

#endif /* PERSONJOBBUILDER_H */
