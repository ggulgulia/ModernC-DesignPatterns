#include <iostream> 
#include <type_traits>
#include <vector> 
#include <string>
#include <sstream>
#include <utility>
#include <functional>
#include <memory>


struct Logger{

    std::function<void(int, int)> m_func;
    std::string m_name;

    Logger() = default;
    Logger(const std::function<void(int, int)>&func, const std::string& name):
        m_func(func), m_name(name){}

    void operator()() const{
        std::cout << "Entering " << m_name << "\n";
        m_func(91, 1012);
        std::cout << "Exiting " << m_name << "\n";
    }

    //This is an implicit conversion operator
    //that converts `Logger` object to `int`
    operator int(){
        static int logVal{0};
        return logVal++;
    }
};

template <typename Func>
struct Logger2{

    Func m_func; //template type
    std::string m_name;

    Logger2() = default;
    Logger2(const Func& func, const std::string& name):
        m_func(func), m_name(name){}

    void operator()() const{
        std::cout << "Logger2: Entering " << m_name << "\n";
        m_func();
        std::cout << "Logger2: Exiting " << m_name << "\n";
    }

    //This is an implicit conversion operator
    //that converts `Logger` object to `int`
    operator int(){
        static int logVal{0};
        return logVal++;
    }
};

//A helper function is needed because the constructor will not be able 
//to deduce the function as its template type when a lambda is passed
//as lambda is not a std::function<T>. Lambdas is a anynomous
//object with an inbuilt operator()(). 

//In the case of `Logger` class, passing a lmbda to the constructor
//worked because the constructor explicitly accepted a std::function<T> 
template <typename Func>
auto make_logger2(Func func, const std::string& name){
    return Logger2<Func>{func, name};
}

template<typename Func2>
void some_function(Func2 func){
    func();
}

//partial specialization with single template 
//parameter
template <typename R>
struct Logger3;

template<typename R, typename ...Args>
struct Logger3<R(Args...)>
{
    std::function<R(Args...)> m_func;
    std::string m_name;
    
    Logger3(const std::function<R(Args...)>& func, const std::string& name):
        m_func(func), m_name(name){     }

    R operator()(Args ...args){
         
        std::cout << "Logger3: Entering " << m_name << "\n";
        R result = m_func(args...);
        std::cout << "Logger3: Exiting " << m_name << "\n";
        return result;
    }
};

template<typename R, typename ...Args>
auto make_logger3(R(*func)(Args...), const std::string& name){
    return Logger3<R(Args...)>(std::function<R(Args...)>(func), name);
}


template<typename R> 
struct Logger4;
template <typename R, typename ...Args>
struct Logger4<R(Args...)>{

    std::function<R(Args...)> m_func;
    std::string m_name;

    Logger4(const std::function<R(Args...)>& func, const std::string& name):
        m_func(func), m_name(name) {    }

    R operator()(Args... args){
        std::cout << "Entering " << m_name << "\n";
        R result = m_func(args...);
        std::cout << "Exiting " << m_name << "\n";
        return result;
    }
};

template <typename R, typename ...Args>
auto make_logger4(R(*func)(Args...), const std::string& name){
    return Logger4<R(Args...)>{std::function<R(Args...)>(func), name};
}

int add2ints(const int a, const int b){
    std::cout << "sum of a and b is " << a+b <<"\n";
    return a+b;
}

int main(){

    Logger([](int a=10, int b=10){std::cout << "Hello\n"
            << "value of a " << a 
            << " value of b " << b <<"\n";}, "HelloFunction")();

    Logger log1;
    int logValue  = log1;
    int logVal2 = log1;
    std::cout << "result of implicit conversion on `Logger` object: " << logValue <<"\n";
    std::cout << "result of implicit conversion on `Logger` object: " << logVal2 <<"\n";

    Logger2<std::function<void()>> log2([](){std::cout << "Hello Logger2\n";}, "Hello Logger2");
    //auto log = make_logger2([](){std::cout << "Hello logger2\n";}, "Hello function");
    
    auto func = [](){std::cout << "some anynomous function\n";};
    some_function(func);
    log2();

    auto logger_add = make_logger3(add2ints, "Add");
    //auto logger_add = make_logger3([](auto ...Args){
    //        auto result = 0 + ...;
    //        std::cout << "sum of a+b+c is: " << result << "\n";
    //        return result;}, "add");

    logger_add(10, 10);

    auto variadic_add = [](auto ...args){return (args+...);};
    std::cout << "result of variadic add with 1,4,5,6,4 is : " << variadic_add(1,4,5,6,4) << "\n";
    
    auto logger4_add = make_logger4(add2ints, "variadic add");
    std::cout << logger4_add(12, 42) << "\n";
    return 0;
}
