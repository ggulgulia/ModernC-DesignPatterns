#include "ChatRoom.hpp"

void ChatRoom::broadcast(const std::string& origin, const std::string& message) const {
        for(const auto p : m_people){
            //the message is not broadcasted to 
            //the person who sent it
            if(p->m_name != origin){
                p->receive(origin, message);
            }
        }
}


void ChatRoom::join(PersonPtr p){
    std::string join_msd = p->m_name + " joined the chat";
    broadcast("room", join_msd);

    //when the Person joins the chat room, each reference
    //of the `ChatRoom` within the person is made to refer to
    //the same chat room object, i.e. each `Person` object
    //refers to the same chat room explicity (see `Person` 
    //class definition, pointer to `ChatRoom` as a member
    //variable to explicitly refer to a chat room object
    p->m_room = std::make_shared<ChatRoom>(*this);
    m_people.push_back(p);
}

void ChatRoom::message(const std::string& origin, const std::string& who,
             const std::string& message){
        auto target = std::find_if(std::begin(m_people), std::end(m_people), 
                                  [&](const PersonPtr p){
                                    return p->m_name == who;
                                  });
        if(target != std::end(m_people)){
            (*target)->receive(origin, message);
        }
}
