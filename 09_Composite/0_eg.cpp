#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <utility>

//This pattern allows us to treat individual as well as aggregate components
//in the same manner
//Objects use other objects' fields/properties/members either through inheritance
//or composition. (Composition allows us to make compound objects)
//Eg. of composition: 
//  1. mathematical expression composed of simple expressions
//  2. Grouping of shapes consisting of several shapes.
//
//Composite deisgn pattern allows to treat for e.g. Foo
//or Collection<Foo> to have the same API
struct GraphicObject{
    virtual void draw() =0;
};

struct Circle : public GraphicObject{

    void draw() override {
        std::cout << "Circle\n";
    }
};


//Class Group inherits from Graphic Object allowing 
//`Group` objects to be of same type as `GraphicObject`
//objects. Furthermore `Group` objects composes collection
//of `GraphicObjects` which allows collection `Group` to be
//treated as a GraphicObject which furthermore could be treated
//as a single object within this collection member data. 
struct Group : public GraphicObject{
  
    std::string m_name;
    std::vector<GraphicObject*> m_objects;
    Group(const std::string& name) :
        m_name(name){   }
    
    void draw() override{
        std::cout << "Group " << m_name << " contains: \n";
        for(auto&& o : m_objects){
            o->draw();
        }
    }
};

int main(){

    //Group object
    Group root("root");
    Circle c1, c2;
    root.m_objects.push_back(&c1);

    //another group object
    Group subgroup("subgroup");
    subgroup.m_objects.push_back(&c2);

    //second `Group` object being made
    //a part of the first `Group` object
    root.m_objects.push_back(&subgroup);

    root.draw();
    return 0;
}
