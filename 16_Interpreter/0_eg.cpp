#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <utility>

//Interpreter design pattern is used to process 
//structured text data, by turning it into a separate
//lexical tokens(lexing) and then interpreting sequences of 
//these tokens (parsing)


//Handmade Interpreter : lexing

struct Token{

 enum  class Type{integer, plus, minus, lparen, rparen} m_type;       
 std::string m_text;

    Token(Type type, const std::string& text):
        m_type(type), m_text(text){     }

    friend std::ostream& operator<<(std::ostream& os, const Token& tok){
        os << "text: `" << tok.m_text << "`\n";
        return os;
    }
};

std::vector<Token> lex(const std::string& input){
    std::vector<Token> result;

    for(size_t i=0; i<input.size(); ++i){
        switch(input[i]){
            case '+':
                result.push_back(Token{Token::Type::plus, "+"});
                break;
            case '-':
                result.push_back(Token{Token::Type::plus, "-"});
                break;
            case '(':
                result.push_back(Token{Token::Type::plus, "("});
                break;
            case ')':
                result.push_back(Token{Token::Type::plus, ")"});
                break;
            default:
                std::ostringstream buffer;
                buffer << input[i];
                    for(size_t j=i+1; j<input.size(); j++){
                        if(isdigit(input[j])){
                            buffer << input[j];
                            ++i;
                        }
                        else{
                            result.push_back(Token{Token::Type::integer, buffer.str()} );
                            break;
                        }
                    }
                //impelement to insert an int
                    
    }
}
    return result;
}
int main(){
        
    std::string input{"(13-4) - (12+1)"};

    auto tokens =  lex(input);
    for(auto& l : tokens){
        std::cout << l << " ";
    }
    return 0;
}
