#include <Person.hpp>
#include <ChatRoom.hpp>

int main(){

    std::shared_ptr<Person> john = std::make_shared<Person>("John");
    std::shared_ptr<Person> jane = std::make_shared<Person>("Jane");

    ChatRoom room;
    room.join(john);
    room.join(jane);
    john->say("hello everyone");
    jane->say("oh, hey John");
    
    std::shared_ptr<Person> joseph = std::make_shared<Person>("Joseph");
    room.join(joseph);
    joseph->say("hi everyone!");
    jane->pm("Joseph", "gald you found us, Simon!");
    return 0;
}
