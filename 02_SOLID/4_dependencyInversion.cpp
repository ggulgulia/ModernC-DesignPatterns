#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <tuple>


//Dependency inversion principle is split into two ideas:
//A. High-level modules should not depend on low level modules.
//Both modules shold depend on abstractions. 
//
//B. Abstractions should not depend on details. 
//   Details should depend on abstractions.


// Relationship between different persons.
enum class Relationship{
    parent,
    child,
    sibling,
};

struct  Person{
    std::string m_name;
};

struct RelationshipBrowser{

    virtual std::vector<Person> find_all_children_of(const std::string& name) = 0;
};

//low level module since it provides constructs for storage of 
//the data like vector, tuple etc
struct Relationships : public RelationshipBrowser{
    std::vector<std::tuple<Person, Relationship, Person>> m_relations;

    void add_parent_and_child(const Person& parent, const Person& child){
        m_relations.push_back({parent, Relationship::parent, child});
        m_relations.push_back({child, Relationship::child, parent});
    }

    std::vector<Person> find_all_children_of(const std::string& name) override{

        std::vector<Person> result;
        for(auto&& [first, rel, second] : m_relations){
            if(first.m_name == name && rel == Relationship::parent){
                result.push_back(second);
            }
        }
        return result;
    }
};
//if we want to do research on the data Relationships
//which processes the data and do something, it will be
//highlevel module
struct Research{

    Research(RelationshipBrowser& browser){
        std::cout << "Research(RelationshipBrowser&)\n";
        for(auto& child : browser.find_all_children_of("john")){
                std::cout << "john has a child called " << child.m_name << "\n";
        }
    }

    //Research(Relationships& relationships){
    //    auto& relations = relationships.m_relations;
    //    for(auto&& [first, rel, second] : relations){
    //        if(first.m_name == "john" && rel == Relationship::parent){
    //            std::cout << "john has a child called " << second.m_name << "\n";
    //        }
    //    }
    //}
};

int main(){

    Person parent{"john"};
    Person child1{"chris"}, child2{"Matt"};
    
    Relationships relationships;
    relationships.add_parent_and_child(parent, child1);
    relationships.add_parent_and_child(parent, child2);


    //Research is a high level module depending on alow 
    //level module, violating the dependency inversion
    // principle
    Research someRel(relationships);


    //if on a very sunny day, the implementor of
    //the object `Relationships` decides to
    //change the way the data is stored or the
    // make the member `Relationship::relations` private
    // then the high level module `Research` will 
    // not function any more. 
    
    return 0;
}
