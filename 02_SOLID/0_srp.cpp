#include <iostream>
#include <fstream>
#include <cstdio>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <string>
#include <memory>

//Single Responsibility Principle means a function or a class should have a single reason to change.


class Journal{

    private: 
        std::string m_title;
        std::vector<std::string> m_entries;

    public:

        //"PASS BY VALUE MOVE" idiom
        //Journal(std::string title):
        //m_title{std::move(title)}
        //{
        //
        //}
        
        //perfect forwarding constructor is 
        //better than "PASS BY VALUE MOVE" idiom
       template<typename T>
           Journal(T&& title):m_title{std::forward<T>(title)}
       {
           //empty constructor body
            std::cout << "called \"Journal(T&& title)\"\n"; 
       }

        Journal() = default;

        //since I defined a destructor to manage
        //resource, it is a good sign that I should 
        //define all other constructors explicitly
        //to prevent shallow copying, i.e. to manage 
        //the resources w/o error
        Journal(const std::string& title): m_title(title){
        
            std::cout << "called \"Journal(const std::string& title)\"\n"; 
        }

        Journal(std::string&& title):m_title{std::move(title)}
        {
            //empty constructor body
            std::cout << "called \"Journal(std::string&& title)\"\n"; 
        }

        //copy constructor
        Journal(const Journal& j):
            m_title(j.get_title()),  m_entries(j.get_entries())
        {
            std::cout << "called \"Journal(const Journal&) \"\n";
        }

        //move constructor
        //Journal(Journal&& j):
        //    m_title(std::move(j.move_title())),
        //    m_entries(std::move(j.move_entries())){
        //        std::cout << "called \"Journal(Journal&& )\"\n";
        //    }

        std::string get_title() const{
            return m_title;
        }

        std::vector<std::string> get_entries()const{
            return m_entries;
        }

        std::string move_title() {return std::move(m_title);}
        std::vector<std::string> move_entries()  {return std::move(m_entries);}

        ~Journal(){
            m_entries.clear();
        }

        void add_entry(const std::string& entry){
            static int count = 1;
            m_entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
        }

        //the method `save` is a part of persistence 
        //and violates the single responsibility principle
        void save(const std::string& filename){
            std::ofstream ofs(filename);
            for(const auto& e: m_entries){
                ofs << e << "\n";
            }
        }
};

struct PersistenceManager{

    static void save(const Journal& j, const std::string& filename){
        std::ofstream outfile{filename};
        for(const auto& entry : j.get_entries()){
            outfile << entry << "\n";
        }
    }
};

int main()
{
    
    Journal my_journal{"my personal journal"};

    my_journal.add_entry("I ate a dog");
    my_journal.add_entry("I want to drink indian style tea :D");

    PersistenceManager pm1;
    pm1.save(my_journal, "randomtitle.txt");
    return 0;
}
