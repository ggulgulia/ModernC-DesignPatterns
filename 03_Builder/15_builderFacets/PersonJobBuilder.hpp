#ifndef PERSONJOBBUILDER_H
#define PERSONJOBBUILDER_H

#include <PersonBuilder.hpp>
class PersonJobBuilder : public PersonBaseBuilder
{
public:
    typedef PersonJobBuilder self;
    explicit PersonJobBuilder(Person& m_person0);
    self& at(const std::string companyName);
    self& as(const std::string& designation);
    self& earning(const int income);

    virtual ~PersonJobBuilder();
};

#endif /* PERSONJOBBUILDER_H */
