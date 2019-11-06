#ifndef NODE_H
#define NODE_H

template <typename E>
class Node
{
    public:
        E element;
        Node* next;
        Node(E pElement, Node* pNext = NULL) {
            element = pElement;
            next = pNext;
        }
        Node(Node* pNext = NULL) {
            next = pNext;
        }
};

#endif // NODE_H
