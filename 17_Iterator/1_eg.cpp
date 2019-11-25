#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <memory>

/*
          A
         / \
        B   C
       / \ / \
*/

template <typename T> 
struct BinaryTree;

template<typename T> 
struct Node{
    T m_value = T();
    std::shared_ptr<Node<T>> m_left;
    std::shared_ptr<Node<T>> m_right;
    std::shared_ptr<Node<T>> m_parent;
    std::shared_ptr<BinaryTree<T>> m_tree;

    Node(T value): m_value(value){  }
    Node(T value, Node<T> left, Node<T>right):
    m_value(value){
        m_left = std::make_shared<Node<T>>(left);
        m_right = std::make_shared<Node<T>>(right);


        this->m_left->m_tree = m_tree;
        this->m_right->m_tree = m_tree;

        //the current node is the parent of 
        //its left and right node
        this->m_left->m_parent = this;
        this->m_right->m_parent = this;
    }

    void set_tree(std::shared_ptr<BinaryTree<T>> t){
        if(m_left) m_left->set_tree(t);
        if(m_right) m_right->set_tree(t);
    }

};

template <typename T>
struct BinaryTree{
    
    std::shared_ptr<Node<T>> m_root;
    
    BinaryTree(std::shared_ptr<Node<T>> root): m_root{root}
    {   }

    template <typename U> 
    struct PreOrderIterator{
        std::shared_ptr<Node<U>> m_current;
        PreOrderIterator(std::shared_ptr<Node<U>> current):
                m_current{current}{ }

        bool operator != (const PreOrderIterator<U>& other){
                return m_current !=other.m_current;
        }

        PreOrderIterator<U>& operator++(){
                if(m_current->m_right){
                        m_current = m_current->m_right;
                        while(m_current->m_left)
                            m_current = m_current->m_left;
                }
                else{
                    std::shared_ptr<Node<T>> p = m_current->m_parent;
                    while(p && m_current == p->m_right){
                        m_current = p;
                        p = p->m_parent;
                    }
                    m_current = p;
                }
                
                return *this;
        }

        Node<U>& operator*(){return *m_current;}
    }; //PreOrderIterator

    typedef PreOrderIterator<T> iterator;

    iterator begin(){
        std::shared_ptr<Node<T>> n = m_root;
        if(n){
            while(n->m_left){
                n = n->m_left;
                return iterator{n};
            }
        }
    }

    iterator end(){
        iterator{nullptr};
    }
};

int main()
{
    
    Node<std::string> me{}
    return 0;
}
