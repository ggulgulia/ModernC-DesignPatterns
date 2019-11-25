#include <iostream>
#include <cstdlib>

//The idea of the interface seggreation principle is
//to create interfaces that are not too large
struct Document;


//below we define IMachine interface for the clients to use
//the Imachine code is already bloated sincee each of the client
//using this interface will need to define all the three method
//defined in the abstract IMachine class
///struct IMachine{
///    virtual void print(const Document& doc) = 0;
///    virtual void scan(const Document& doc) = 0;
///    virtual void fax(const Document& doc) = 0;
///};
///
///struct MFP : public IMachine{
///
///    void print(const Document& doc) override{
///        ///
///    }
///    void scan(const Document& doc) override {
///
///    }
///
///    void fax(const Document& doc) override {
///
///    }
///};
///
///struct Scanner: public IMachine{ 
///    void print(const Document& doc) override{
///        ///
///    }
///    void scan(const Document& doc) override {
///
///    }
///
///    void fax(const Document& doc) override {
///
///    }
///};


//What interface seggregation principle says is to
//seggregate the interface so that handling of the
//interface by clients becomes easy, avoids code 
//repitition

//Lets go ahead and seggregate the interface of IMachine
//and implement IPrinter, IScanner and IFax separately.

//this is a buffer freshly written in insert mode
struct IPrinter{
    virtual void print(const Document& doc) = 0;
};

struct IScanner{
    virtual void scan(const Document& doc) = 0;
};

struct IFax{
    virtual void fax(const Document& doc) = 0;
};

struct Printer : IPrinter{
    void print(const Document& doc) override{
    }
};

struct Scanner : IScanner{
    void scan(const Document& doc) override{
    }
};

struct Fax : IFax{
    void fax(const Document& doc) override{
    }
};


