#ifndef CHATROOM_H
#define CHATROOM_H
#include <algorithm>
#include "Person.hpp"

typedef std::shared_ptr<Person> PersonPtr;

struct ChatRoom{
    public:

        std::vector<std::shared_ptr<Person>> m_people;
        

        void broadcast(const std::string& origin, const std::string& message) const;
        void join(PersonPtr p);

        void message(const std::string& origin, const std::string& who,
                     const std::string& message);
};

#endif /* CHATROOM_H */
