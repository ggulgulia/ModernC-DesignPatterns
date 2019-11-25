#include <iostream>
#include <sstream>

/*this is a very simple scenario to evaluate a numerical expresion
 *
 * Here we see the double dispatch being used in C++ 
 * The aim is to be able to walk down the hierarchy without 
 * having multiple if statements with ugly dynamic casts
 */

struct DoubleExpression;
struct AdditionExpression;
struct SubtractionExpression;

struct ExpressionVisitor{
  virtual void visit(DoubleExpression *de) = 0;
  virtual void visit(AdditionExpression* ae) = 0;
  virtual void visit(SubtractionExpression* ae) = 0;
};

//will be modified compared to last example using 
//double dispatch
struct ExpressionPrinter : public ExpressionVisitor{
    
    public:
        std::ostringstream oss_;

        std::string str() const{return oss_.str();}
        void visit(DoubleExpression *de) override;
        void visit(AdditionExpression* ae) override;
        void visit(SubtractionExpression* ae) override;

};

struct Expression{
        
    public:
        virtual ~Expression() = default;
        virtual void accept(ExpressionVisitor* ev) = 0;
};

struct DoubleExpression : public Expression{
    public:
        double value_{0.0};
        DoubleExpression(double value) : value_{value}{ }
        void accept(ExpressionVisitor* ev) override{
            ev->visit(this);
        }
};

struct AdditionExpression : public Expression{
    public:
        Expression* left_{nullptr};
        Expression* right_{nullptr};

        AdditionExpression(Expression* left, Expression* right): 
                          left_{left}, right_{right}{ }
        ~AdditionExpression(){
            
            delete  left_;
            delete right_;
        }
        
        void accept(ExpressionVisitor* ev) override{
            ev->visit(this);
        }
};

struct SubtractionExpression : public Expression{
    public:
        Expression* left_{nullptr};
        Expression* right_{nullptr};

        SubtractionExpression(Expression* left, Expression* right): 
                          left_{left}, right_{right}{ }
        ~SubtractionExpression(){
            
            delete  left_;
            delete right_;
        }
        
        void accept(ExpressionVisitor* ev) override{
            ev->visit(this);//this refers to the `ExpressionPrinter` pointer
        }
};

void ExpressionPrinter::visit(DoubleExpression* de){
    oss_ << de->value_;
}

void ExpressionPrinter::visit(AdditionExpression* ae){

    //We don't want braces if the 
    bool isLeftDoubleExpression = dynamic_cast<DoubleExpression*>(ae->left_);
    bool isRightDoubleExpression = dynamic_cast<DoubleExpression*>(ae->right_);
    bool isInnerLeftBinary = dynamic_cast<AdditionExpression*>(ae->left_);

    bool isLeftBracket{false};
    if(!isLeftDoubleExpression){
        oss_ << "(";
        isLeftBracket = true;
    }
    ae->left_->accept(this); //this refers to the `ExpressionPrinter` pointer
    oss_ << "+";
    if(!isRightDoubleExpression){
        oss_ << "(";
        isLeftBracket = true;
    }
    ae->right_->accept(this);// -----"-----"-----"-----"-----"-----"-----"
    if(isLeftBracket){
        oss_ << ")";
    }
    else if(isLeftDoubleExpression && isRightDoubleExpression) oss_ << ")";
}

void ExpressionPrinter::visit(SubtractionExpression* ae){

    //We don't want braces if the 
    bool isLeftDoubleExpression = dynamic_cast<DoubleExpression*>(ae->left_);
    bool isRightDoubleExpression = dynamic_cast<DoubleExpression*>(ae->right_);

    if(!isLeftDoubleExpression) oss_ << "(";
    ae->left_->accept(this); //this refers to the `ExpressionPrinter` pointer
    oss_ << "-";
    if(!isRightDoubleExpression) oss_ << "(";
    ae->right_->accept(this);// -----"-----"-----"-----"-----"-----"-----"
    if(!isLeftDoubleExpression || !isRightDoubleExpression) oss_ << ")";
}

int main(){

    auto e = new AdditionExpression{
                 new DoubleExpression{1},
                 new AdditionExpression{
                     new AdditionExpression{
                         new DoubleExpression{-11},
                         new DoubleExpression{2}
                         },
                     new DoubleExpression{3}
                     }
                };
    //`e` should look like (1+(2+3)) when printed

    ExpressionPrinter ep;
    ep.visit(e);
    std::cout << ep.str() << "\n";
    
    delete e;
    return 0;
}
