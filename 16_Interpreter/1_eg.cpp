#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <memory>
#include <utility>
#include <boost/lexical_cast.hpp>

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

struct Element{
    virtual int eval() const = 0;
};

struct Integer : public Element{
        int m_value;
        Integer(int value): m_value(value){     }

        int eval() const override{
                return m_value;
        }
};

struct BinaryOperation : public Element{
        
    enum class Type{ addition, subtraction} m_type;
    std::shared_ptr<Element> m_lhs;
    std::shared_ptr<Element> m_rhs;

    int eval() const override{
            auto left = m_lhs->eval();
            auto right = m_rhs->eval();
            if(m_type == Type::addition){
                    return left + right;
            }
            else
                return left - right;
    }
};

std::shared_ptr<Element> parse(const std::vector<Token>& tokens){
    auto result = std::make_unique<BinaryOperation>();
    bool have_lhs{false};
    for(size_t i=0; i<tokens.size(); ++i){
        auto& token = tokens[i];
            switch(token.m_type){
                case Token::Type::integer:{
                        int value = boost::lexical_cast<int>(token.m_text);
                        auto integer = std::make_shared<Integer>(value);
                        if(!have_lhs){
                            result->m_lhs = integer;
                        }
                        else{
                            result->m_rhs = integer;
                        }
                        break;
                    }
                case Token::Type::plus:
                    result->m_type = BinaryOperation::Type::addition;
                    break;
                case Token::Type::minus: 
                    result->m_type = BinaryOperation::Type::subtraction;
                    break;
                case Token::Type::lparen: 
                    {
                        size_t j = i;
                        for(; j<tokens.size(); ++j){
                           if(tokens[j].m_type == Token::Type::rparen)
                               break;

                           std::vector<Token> subexpression(&tokens[i+1], &tokens[j]);
                           auto element = parse(subexpression);
                           if(!have_lhs){
                               result->m_lhs = element;
                               have_lhs = true;
                           }

                           else result->m_rhs = element;
                           i = j;
                        }
                    }
                        break;
                case Token::Type::rparen: 
                    break;
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


    try{
        auto parsed = parse(tokens);
        std::cout << input << " = " << parsed->eval() << "\n";
    }catch(const std::exception& e){
            std::cout << e.what() << "\n";
    }
    return 0;
}
