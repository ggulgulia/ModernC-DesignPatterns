#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>
#include <iostream>
#include <memory>

struct ChatRoom;
class Person
{
public:
    std::string m_name;
    std::shared_ptr<ChatRoom> m_room =  nullptr;
    std::vector<std::string> m_chatLog;

    Person () = default;
    Person(const std::string& name);
    virtual ~Person () = default;
    
    void say(const std::string& message) const;
    void pm(const std::string& who, const std::string& message) const;
    void receive(const std::string& origin, const std::string& message) const;
    bool operator==(const Person& rhs);
    bool operator!=(const Person& rhs);
};
#endif /* ifndef PERSON_H
 */ 

/* Mediator design pattern lets the components communicate 
 * to each other without letting the individual components 
 * being aware of each others presence
 */

