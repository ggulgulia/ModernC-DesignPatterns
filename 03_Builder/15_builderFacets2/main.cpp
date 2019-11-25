#include <Person.hpp>
#include <iostream>
#include <PersonBuilder.hpp>
#include <PersonJobBuilder.hpp>
#include <PersonAddressBuilder.hpp>

int main(){

    Person me = Person::create().lives()
                .at("Willi Graf Strasse")
                .withPostCode("80805")
                .in("Munich")
                .works()
                .working_at("TTTech Auto")
                .as("Software Developer")
                .earning(10000000);

    std::cout << me;
    return 0;
}
