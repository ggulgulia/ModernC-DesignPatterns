#include <iostream>
#include <sstream>

/* In this lesson, we are taking a look at something called
 * acyclic visitor.
 *
 * The visitor we looked at in the previous session we saw what 
 * could be seen as cyclic visitor which works only when a stable 
 * hierarchy is present to enforce the correct implementation
 * of `accept` method. This is a bit slower
 */

template <typename Visitable>
struct Visitor{
        
    virtual void visit(Visitable& obj) = 0;
};

//`VisitorBase` is a marker interface 
//that doesn't do much but we cannot leave 
//it empty since we need it's vtable to 
//be constructed and hence we declare a
//default destructor and mark it as 
//virtual. (`virtual` is what assists
//in vtable construction)
struct VisitorBase{
        
    virtual ~VisitorBase() = default;
};

struct Expression{
        
    virtual ~Expression() = default;

    //type of Visitor<T> `T` corresponds to `Expression`
    virtual void accept(VisitorBase& obj){
            
        using EV = Visitor<Expression>;
        if(auto ev = dynamic_cast<EV*>(&obj))
            ev->visit(*this);
    }
};

struct DoubleExpression : public Expression{
        
    double value_{0.};
    DoubleExpression(double value):
        value_{value}{ }
    virtual void accept(VisitorBase& obj){
            
        using DV = Visitor<DoubleExpression>;
        if(auto dev = dynamic_cast<DV*>(&obj))
            dev->visit(*this);
    }
};

struct AdditionExpression : public Expression{
        
    Expression* left_{nullptr};
    Expression* right_{nullptr};

    AdditionExpression(Expression* left, Expression* right):
        left_{left}, right_{right}{ }
    ~AdditionExpression(){
        
        delete left_;
        delete right_;
    }
    virtual void accept(VisitorBase& obj){
            
        using AEV = Visitor<AdditionExpression>;
        if(auto aev = dynamic_cast<AEV*>(&obj))
            aev->visit(*this);
    }
};

struct ExpressionPrinter : public VisitorBase, 
                           Visitor<DoubleExpression>,
                           Visitor<AdditionExpression>{
    private:
        std::ostringstream oss_;

    public:
    void visit(AdditionExpression& obj) override{
            
        oss_ << "(";
        obj.left_->accept(*this);
        oss_ << "+";
        obj.right_->accept(*this);
        oss_ << ")";

    }

    void visit(DoubleExpression & obj) override{
            
        oss_ << obj.value_;
    }

    std::string str(){return oss_.str();}
};

int main(){
        
    auto e = new AdditionExpression{
                new DoubleExpression{1},
                new AdditionExpression{
                    new DoubleExpression{2},
                    new DoubleExpression{3}
                    }
                };

    ExpressionPrinter ep;
    ep.visit(*e);

    std::cout << ep.str() << "\n";

    return 0;
}
