#include <PersonJobBuilder.hpp>

typedef PersonJobBuilder self;

PersonJobBuilder::PersonJobBuilder(Person& p):
                  PersonBuilderBase{p}{     }

self& PersonJobBuilder::working_at(const std::string& companyName){
    m_person0.m_companyName = companyName;
    return *this;
}

self& PersonJobBuilder::as(const std::string& designation){
    m_person0.m_designation = designation;
    return *this;
}

self& PersonJobBuilder::earning(const int income){
    m_person0.m_income = income;
    return *this;
}
