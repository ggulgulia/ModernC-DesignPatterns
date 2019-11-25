#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <memory>
#include <boost/bimap.hpp>


//A flyweight pattern is a space optimization
//technique that allows user to save memory by 
//storing externally the data associated with 
//similar objects


typedef uint32_t key;

struct User{

    protected:

    key m_firstName;
    key m_lastName;
    static boost::bimap<key, std::string> m_names;
    static key m_seed;

    static key add(const std::string& s){
        auto it = m_names.right.find(s);
        if(it == m_names.right.end()){
            key id = ++m_seed;
            m_names.insert({m_seed, s});
            return id;
        }
        return it->second;
    }

    public:

    User(const std::string& first_name, const std::string& last_name):
        m_firstName(add(first_name)), m_lastName{add(last_name)} { }

    const std::string& get_firstName() const{
        return m_names.left.find(m_firstName)->second;
    }
    
    const std::string& get_lastName() const{
        return m_names.left.find(m_lastName)->second;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const User& user){
        os << "first name: " << user.get_firstName() << " last name: " 
        << user.get_lastName() << "Index: (" << user.m_firstName << ")";
        return os;
    }
};
key User::m_seed{0};
boost::bimap<key, std::string> User::m_names{};

int main(){

    User user1{"John", "Smith"};
    User user2{"John", "Doe"};

    std::cout << "user1 " << user1 << "\n";
    std::cout << "user2 " << user2 << "\n";

    return 0;
}

