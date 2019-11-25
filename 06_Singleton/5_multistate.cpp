#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>

enum class Imporatnce{primary, secondary, tertiary};

template <typename T, typename Key=std::string>
class Multiton{

    private:
        static std::map<Key, std::shared_ptr<T>> m_instances;
    public:
        static std::shared_ptr<T> get(const Key& key){
            if(const auto it = m_instances.find(key);
                    it!= m_instances.end()){
                return it->second;
            }

            auto instance = std::make_shared<T>();
            m_instances[key] = instance;
            return instance;
        }

    protected:
        Multiton() = default;
        virtual ~Multiton() = default;

};


template<typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::m_instances;

class Printer{

    private:
        static int m_totalInstanceCount;
    public:
        Printer(){
            ++Printer::m_totalInstanceCount;
            std::cout << "A total of " << Printer::m_totalInstanceCount
                      << " instances created so far\n";

        }
};
int Printer::m_totalInstanceCount = 0;

int main(){

    typedef Multiton<Printer, Imporatnce> mt;
    auto main = mt::get(Imporatnce::primary);
    auto aux  = mt::get(Imporatnce::secondary);
    auto aux2 = mt::get(Imporatnce::secondary);
    return 0;
}
