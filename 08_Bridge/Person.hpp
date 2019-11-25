#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
class Person
{
private:
    
public:
    std::string m_name;
    class PersonImpl;
    PersonImpl* m_impl;

    Person();
    virtual ~Person();

    void greet();
};

#endif /* PERSON_H */
