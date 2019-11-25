#include "Person.hpp"
#include "ChatRoom.hpp"

Person::Person(const std::string& name):m_name(name){ }

void Person::say(const std::string& message)const {
    //the interaction between people 
    //to do the chat is delegated to the
    //mediator, i.e. the chat room
    //ChatRoom::broadcast() is a mediator 
    //function
    //This makes the people in the chat room
    //loosely coupled because the people
    //in the chat room have no explicit knowledge
    //of each other and can communicate to each
    //other only via its mediator which they
    //refer to
    m_room->broadcast(m_name, message);
}


void Person::pm(const std::string& who, const std::string& message)const {

    m_room->message(m_name, who, message);
        
}

void Person::receive(const std::string& origin, const std::string& message)const {
    std::cout << origin << " says: " << message << "\n";
    std::string s{origin +": \"" + message +"\""};
    std::cout << "[" << m_name << "'s chat session]" << s << "\n";
    //this->m_chatLog.push_back(s); //debug later
}

bool Person::operator==(const Person& rhs){
    return this->m_name == rhs.m_name;
}

bool Person::operator!=(const Person& rhs){
    return this->m_name != rhs.m_name;
}
