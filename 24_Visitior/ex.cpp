#include <string>
#include <sstream>
using namespace std;

//Forward declaration
struct Expression;
struct AdditionExpression;
struct MultiplicationExpression;


struct ExpressionVisitor
{
  virtual void accept(AdditionExpression& ae) = 0;
  virtual void accept(MultiplicationExpression& me) = 0;
};

struct Expression
{
  virtual void visit(ExpressionVisitor& ev) = 0;
};

struct Value : Expression
{
  int value;

  Value(int value) : value(value) {}
};

struct AdditionExpression : Expression
{
  Expression &lhs, &rhs;

  AdditionExpression(Expression &lhs, Expression &rhs) : lhs(lhs), rhs(rhs) {}
  
  void visit(ExpressionVisitor& ep) override{
      ep.accept(*this);
  }
};

struct MultiplicationExpression : Expression
{
  Expression &lhs, &rhs;

  MultiplicationExpression(Expression &lhs, Expression &rhs)
    : lhs(lhs), rhs(rhs) {}
    
    void visit(ExpressionVisitor& ep) override{
      ep.accept(*this);
};

struct ExpressionPrinter : ExpressionVisitor
{
    ostringstream oss_;
    
    void accept(AdditionExpression& ae) override{
        oss_ << "(";
        ae.lhs.visit(*this);
        oss << "+";
        ae.rhs.visit(*this);
        oss << ")";
    }
    
    void accept(MultiplicationExpression& me) override{
            oss_ << "(";
        ae.lhs.visit(*this);
        oss_ << "*";
        ae.rhs.visit(*this);
        oss_ << ")";
    }

  
  string str() const { return oss_.str(); }
};
