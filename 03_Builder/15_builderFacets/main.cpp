#include <Person.hpp>
#include <PersonBuilder.hpp>
#include <PersonAddressBuilder.hpp>
#include <PersonJobBuilder.hpp>

int main(){

    Person me = Person::create()
                .lives().at("willi graf sraße 11")
                .with_postCode("80805")
                .in("Munich");

std::cout << me << "\n";
    return 0;
}
