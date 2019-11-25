#include <iostream>
#include <sstream>

/*this is a very simple scenario to evaluate a numerical expresion
 *
 * Here we see the reflective visitor
 *
 * This is to adhere to the SRP and not to modify the 
 * existing code (intrusively) as it was done in the previous
 * file while implementing the method for each of the existing 
 * class
 */

struct Expression{
        
    public:
        virtual ~Expression() = default;
};

struct DoubleExpression : public Expression{
    public:
        double value_{0.0};
    DoubleExpression(double value) : value_{value}{ }
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
};


//struct ExpressionPrinter{
//        
//
//    /* from the first galnce one can say that this approach is not
//     * scalable at all as each kind of expression needs a suitable 
//     * overload of `print` method
//     */
//    void print(DoubleExpression *de, std::ostringstream& oss) const{
//        oss << de->value_;
//    }
//
//    void print(AdditionExpression* ae, std::ostringstream& oss) const{
//        oss << "(";
//        //the following won't work because there's no overload
//        //of a `print` method that works with a general
//        //`Expression` type object. The overload resolution 
//        //to determine which function to call, also known as dispatch
//        //occurs at compile time, and there's no way to find out at compile
//        //time which of the overload will be called
//        
//        /* print(ae->left_, oss); */
//    }
//};


struct ExpressionPrinter{
    
    public:
        std::ostringstream oss_;

        std::string str() const{return oss_.str();}

        void print(Expression* e){

            //dynamic casts are ugly but still better than 
            //having 2 overloads of print as in the previous 
            //commented code
            if(auto de = dynamic_cast<DoubleExpression*>(e)){
                oss_ << de->value_;
            }
            else if(auto ae = dynamic_cast<AdditionExpression*>(e)){
                oss_ << "(";
                print(ae->left_);
                oss_ << "+";
                print(ae->right_);
                oss_ << ")";
            }
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

    //`e` should look like (1+(2+3)) when printed

    ExpressionPrinter ep;
    ep.print(e);
    std::cout << ep.str() << "\n";
    
    delete e;
    return 0;
}
