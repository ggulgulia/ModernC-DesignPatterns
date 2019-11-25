#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>
#include <memory>


class FormattedText{

    std::string m_plainText;
    bool *caps;
    public:
    FormattedText(const std::string& plainText):
        m_plainText(plainText){  
            caps = new bool[plainText.length()];
            for(size_t i = 0; i < plainText.length(); ++i){
                caps[i] = 0;
            }
        }

    ~FormattedText(){
        delete[] caps;
    }

    void capitalize(int start, int end){
        for(int i=start; i<=end; ++i){
            caps[i] = true;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj){
        std::string s;
        for(size_t i=0; i<obj.m_plainText.length(); ++i){
            char c = obj.m_plainText[i];
            s += (obj.caps[i]? std::toupper(c) : c);
        }
        return os << s;
    }
};


class BetterFormattedText{
    public:

        //nested class
        struct TextRange{
            int m_start;
            int m_end;
            bool m_capitalize; //bold, italic
            
            bool covers(int pos) const{
                return pos >= m_start && pos <=m_end;
            }
        };
    private:
        std::string m_plainText;
        std::vector<TextRange> m_formatting;
    public:
        BetterFormattedText(const std::string& plainText):
        m_plainText(plainText){     }

        TextRange& get_range(int start, int end){
            m_formatting.emplace_back(TextRange{start, end, 1});
            return *m_formatting.rbegin();
        }

        friend std::ostream& operator<<(std::ostream& os, const BetterFormattedText& text){
            std::string s;
            for(size_t i=0; i< text.m_plainText.length(); ++i){
                char c = text.m_plainText[i];
                for(const auto& rng: text.m_formatting){
                    if(rng.covers(i) && rng.m_capitalize)
                        c = std::toupper(c);
                    s+=c;
                }
            }
            return os << s;
        }
};

int main(){

    FormattedText ft{"CSE is a nice and advanced masters program at tum"};
    ft.capitalize(18,25);

    std::cout << ft <<"\n";

    BetterFormattedText bft{"this is a brave new world"};
    bft.get_range(10, 15).m_capitalize = true;
    std::cout << bft << "\n";
    return 0;
}
