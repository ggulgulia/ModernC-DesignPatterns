#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>
#include "Observer.hpp"
#include <algorithm>
#include <mutex>

template <typename T>
class Observable
{

    public:
       // Observable();
       // virtual ~Observable();
    
        std::vector<Observer<T>*> observers_;
    
        void notify(T& source, const std::string fieldName){
            for(auto observer : observers_){
                    observer->field_changed(source, fieldName);
            }
        }
    
    
        void subscribe(Observer<T>& observer){
            observers_.push_back(&observer);
        }
    
        void unsubscribe(Observer<T>& observer){
            observers_.erase(
                    std::remove(observers_.begin(), observers_.end(), &observer),
                    observers_.end()
                    );
        }
};

template <typename T>
class SaferObservable
{

    public:
       // Observable();
       // virtual ~Observable();
    
        typedef std::mutex mutex_t;
        mutex_t mtx_;
        std::vector<Observer<T>*> observers_;
    
        void notify(T& source, const std::string fieldName){
            std::scoped_lock<mutex_t> lock_{mtx_};
            for(auto observer : observers_){
                    observer->field_changed(source, fieldName);
            }
        }
    
    
        void subscribe(Observer<T>& observer){
            std::scoped_lock<mutex_t> lock_{mtx_};
            observers_.push_back(&observer);
        }
    
        void unsubscribe(Observer<T>& observer){
            std::scoped_lock<mutex_t> lock_{mtx_};
            observers_.erase(
                    std::remove(observers_.begin(), observers_.end(), &observer),
                    observers_.end()
                    );
        }
};
#endif /* OBSERVABLE_H */
