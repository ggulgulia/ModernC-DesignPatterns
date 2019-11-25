#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <utility>

//CRTP

//struct Neuron;
//template <typename Self>
//struct SomeNeurons{
//    template<typename T>
//    void connect_to(T& other){
//        for(Neuron& from : *static_cast<Self*>(this)){
//            for(Neuron& to : other){
//                from.m_out.push_back(&to);
//                to.m_in.push_back(&from);
//            }
//        }
//    }
//};

struct Neuron// : public SomeNeurons<Neuron>{
    std::vector<Neuron*> m_in;
    std::vector<Neuron*> m_out;
    size_t m_id;

    Neuron(){
        static int id{1};
        this->m_id = id++;
    }

    void connect_to(Neuron& other){
        m_out.push_back(&other);
        other.m_in.push_back(this);
    }

    Neuron* begin(){return this;}
    Neuron* end(){return this+1;}

    friend std::ostream& operator<<(std::ostream& os, const Neuron& obj){
        for(Neuron* n : obj.m_in){
            os << n->m_id << "\t-->\t[" << obj.m_id << "]\n";
        }
        for(Neuron* n : obj.m_out){
            os << "[" << obj.m_id << "]\t-->\t" << n->m_id << "\n";
        }
        return os;
    }
}; 


struct NeuronLayer : public std::vector<Neuron>//, SomeNeurons<NeuronLayer>
{
    NeuronLayer(int count){
        while(count-- > 0)
            emplace_back(Neuron{});
    }
    friend std::ostream& operator<<(std::ostream& os, const NeuronLayer &obj){
        
        for(auto& n : obj) os << n;
        return os;
    }
};

int main(){

    Neuron n1, n2;
    n1.connect_to(n2);
    std::cout << n1 << n2 << "\n";

    NeuronLayer layer1{2}, layer2{3};
    n1.connect_to(layer1);
    layer2.connect_to(n2);
    layer1.connect_to(layer2);
    return 0;
}
