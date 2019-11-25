#include <iostream>
#include "Observable.hpp"


class Person : public SaferObservable<Person>{
        
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


class TrafficAdministration : public Observer<Person>{
    public:
        void field_changed(Person& source, const std::string& fieldName) override{
            if(fieldName == "age"){
                if(source.getAge()< 17)
                    std::cout << "whoa there, you're too young to drive!\n";
                else
                    std::cout << "Oh ok, we no longer care!\n";
                    source.unsubscribe(*this);
            }
        }
};

int main(){
    Person person{10};
    TrafficAdministration ta;
    person.subscribe(ta);

    person.setAge(11);
    person.setAge(12);
    person.setAge(15);

    person.setAge(16);

    try{
        person.setAge(17);
    }
    catch(const std::exception& e){
        std::cerr << "Oops " <<  e.what() << "\n";
    }
    return 0;
}
