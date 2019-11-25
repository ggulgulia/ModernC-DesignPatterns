#include <iostream>
#include <cstdio>
#include <sstream>
#include <tuple>
#include <memory>
#include <string>
#include <memory>
#include <vector>
#include <fstream>

typedef std::pair<std::string, std::string> str_pair;
class  Tag{
    
    private:
        std::string m_name;
        std::string m_text;
        std::vector<Tag> m_children;
    protected:
        std::vector<str_pair> m_attributes;

        //protected constuctors are not allowed to be used 
        //by the (human) client but are supposed to 
        //be called by the objects that are inherited from
        //them. Protectd constructors allow users to 
        //develop codes using the builder pattern implicitly
        Tag(const std::string& name, const std::string& text):
            m_name(name), m_text(text) {    }
        Tag(const std::string& name, const std::vector<Tag>& children):
            m_name(name), m_children(children){     }

    public:
        friend std::ostream& operator<<(std::ostream& os, const Tag& tag){
            os << "<" << tag.m_name;
            for(const auto& att : tag.m_attributes)
                os << " " << att.first << "=\"" << att.second << "\"";
            
            if(tag.m_children.size() == 0 && tag.m_text.length() == 0){
                os << "/>\n";
            }
            else{
                os << ">\n";
                if(tag.m_text.length())
                    os << tag.m_text << "\n";
                
                for(const auto& child : tag.m_children)
                    os << child;
                
                os << "</"  << tag.m_name << ">\n";
            }
            return os;
        }
};

class Paragraph : public Tag{
    public:
        Paragraph(const std::string& text): Tag("p", text){ 
            std::cout << "Paragraph(const std::string&)\n";
        }
        Paragraph(std::initializer_list<Tag> children): Tag("p", children) {  
            std::cout << "Paragraph(std::initializer_list)\n";
        }
};

class Image : public Tag{
    public:
        explicit Image(const std::string& url):
            Tag("IMG", ""){
                m_attributes.emplace_back(std::make_pair("src", url));
            }
};

int main(){

    std::cout << Paragraph{
                           Image{"http//pokemon.com/piakchu.png"}, 
                           Image{"https://dragonballZ.com/piccolo.png"}
                          } << "\n";
    return 0;
}
