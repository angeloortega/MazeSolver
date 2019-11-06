#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include <stdexcept>
#include "Node.h"

using namespace std;

template <typename E>
class LinkedStack
{
private:
    Node<E>* top;
    int size;

public:
    LinkedStack() {
        top = NULL;
        size = 0;
    }
    ~LinkedStack() {
    }
    void clear() {
        while(top!= NULL){
            Node<E>* tempNode = top;
            top = top->next;
            delete tempNode;
        }
        size = 0;
    }
    void push(E pElement) {
        top = new Node<E>(pElement, top);
        size++;
    }
    E pop() throw(runtime_error) {
        if(top == NULL){
            throw runtime_error("Stack is empty.");
        }
        E pElement = top->element;
        Node<E>* tempNode = top->next;
        delete top;
        top = tempNode;
        size--;
        return pElement;
    }
    E topValue() throw(runtime_error) {
        if (top == NULL) {
            throw runtime_error("Stack is empty.");
        }
        return top->element;
    }
    int getSize() {
        return size;
    }
};

#endif // LINKEDSTACK_H
