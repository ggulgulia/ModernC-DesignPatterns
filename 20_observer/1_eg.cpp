#include <iostream>
//#include "Observer.hpp"
#include "Observable.hpp"


class Person : public Observable<Person>{
        
    private:
        int age_{0};
    public:
        Person(int age): age_{age}{
            
        }

        int getAge() const{
            return age_;
        }

        void setAge(int age){

            auto oldCanVote = getCanVote();
            if(this->age_ == age)
                return;

            this->age_ = age;
            notify(*this, "age");

            if(oldCanVote != getCanVote()){
                notify(*this, "canVote");
            }
        }

        bool getCanVote() const {
            return age_ >= 16;
        }
};


class ConsolePersonObserver : public Observer<Person>{
    private:

    public:
        void field_changed(Person& source, const std::string& fieldName) override{
            std::cout << "Person's " << fieldName << " has changed to ";
            if(fieldName == "age") std::cout << source.getAge()  << "\n";
            if(fieldName == "canVote") std::cout << std::boolalpha << source.getCanVote()  << "\n";

        }
};

int main(){
    Person person{10};
    ConsolePersonObserver cpo;
    person.subscribe(cpo);

    person.setAge(11);
    person.setAge(12);
    person.setAge(12);
    person.setAge(15);

    person.setAge(16);
    person.setAge(17);

    return 0;
}
