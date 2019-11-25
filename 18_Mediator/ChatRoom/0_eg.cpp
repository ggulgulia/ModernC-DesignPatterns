#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

class ChatRoom;
class Person
{
public:
    std::string m_name;
    ChatRoom* m_room{nullptr};
    std::vector<std::string> m_chatLog;

    Person () = default;
    Person(const std::string& name);
    virtual ~Person ();
    
    void say(const std::string& message) const{
        
        std::cout << message << "\n";
    }

    void pm(const std::string& who, const std::string& message){
            
    }

    void receive(const std::string& origin, const std::string message){
            
    }

    bool operator==(const Person& rhs){
        return this->m_name == rhs.m_name;
    }
    bool operator!=(const Person& rhs){
        return this->m_name != rhs.m_name;
    }
};
#endif /* ifndef PERSON_H
 */ 

/* Mediator design pattern lets the components communicate 
 * to each other without letting the individual components 
 * being aware of each others presence
 */

