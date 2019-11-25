#include <iostream>
#include <sstream>
/* A pattern where a component (which we call as visitor) 
 * is allowed to traverse the entire inheritance hierarchy-
 * implemented by propogating a single visit() method throughout the 
 * entire hierarchy
 */

/*this is a very simple scenario to evaluate a numerical expresion
 *
 * Here we see the intrusive visitor
 */

struct Expression{
        
    public:
        virtual ~Expression() = default;

        //this print was added later in the code 
        //and such addition after the design is complete
        //is intrusive as it breaks the Open-Close principle
        //and hence this is an 'intrusive method'
        virtual void print(std::ostringstream& oss) = 0;
};

struct DoubleExpression : public Expression{
    public:
        double value_{0.0};
    DoubleExpression(double value) : value_{value}{ }
        //all inherited methods have to be modified to define 
        //a suitable override of the `print` method
        virtual void print(std::ostringstream& oss) override{
         oss << value_;        
        }
};

struct AdditionExpression : public Expression{
    public:
        Expression *left_{nullptr};
        Expression* right_{nullptr};

        AdditionExpression(Expression* left, Expression* right): 
                          left_{left}, right_{right}{ }
        ~AdditionExpression(){
            
            delete  left_;
            delete right_;
        }

        //all inherited methods have to be modified to define 
        //a suitable override of the `print` method
        virtual void print(std::ostringstream& oss) override{
            
            oss << "(";
            left_->print(oss); 
            oss << "+";
            right_->print(oss);
            oss << ")";
        }
};

int main(){

    auto e = new AdditionExpression{
                 new DoubleExpression{1},
                 new AdditionExpression{
                        new DoubleExpression{2},
                        new DoubleExpression{3}
                        }
                };
    std::ostringstream oss;
    e->print(oss);
    std::cout << oss.str() << "\n";
    
    delete e;
    return 0;
}
