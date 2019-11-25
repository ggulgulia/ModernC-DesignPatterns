#include <iostream>
#include <sstream>
#include <tuple>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <memory>
#include <map>

class SingletonDataBase{
    
    private:
        std::map<std::string, int> m_capitals;
    SingletonDataBase() {
        std::cout << "Initializing database\n";
        std::ifstream ifs("capitals.txt");
        std::string s1, s2;
        while(getline(ifs, s1)){
            getline(ifs, s2);
            int population = boost::lexical_cast<int>(s2);
            m_capitals[s1] = population;
        }
    }

    public:
    SingletonDataBase(const SingletonDataBase&) = delete;
    SingletonDataBase& operator=(const SingletonDataBase&) = delete;

    static SingletonDataBase& get(){
        static SingletonDataBase db;
        return db;
    }
    static SingletonDataBase* get1(){
        static SingletonDataBase* db = new SingletonDataBase();
        return db;
    }


    int get_population(const std::string& city_name){
        return m_capitals[city_name];
    }

};

int main(){
    
    std::string city{"Beljing"};
    std::cout << city << " has population " <<
    SingletonDataBase::get().get_population(city) << "\n";

    SingletonDataBase* db1 = SingletonDataBase::get1();
    std::cout << "Berlin has population: " << db1->get_population("Berlin") << "\n";

    return 0;
}
