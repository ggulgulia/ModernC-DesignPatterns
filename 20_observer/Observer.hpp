#ifndef OBSERVER_H
#define OBSERVER_H

#include <string>
template <class T>
class Observer
{
    public:
    virtual void field_changed(T& source, const std::string& fieldName) = 0;

public:
    //class Observer();
    //virtual ~class Observer();
};

#endif /* OBSERVER_H */
