#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include<stdexcept>
using namespace std;

template<typename E>

class LinkedNode{
public:
    E element;
    LinkedNode<E> *next;

    LinkedNode(E pElement, LinkedNode<E>* pNext = NULL)
    {
        element = pElement;
        next = pNext;
    }
    LinkedNode (LinkedNode<E> *pNext = NULL)
    {
        next = pNext;
    }
};


#endif // NODE_H_INCLUDED
