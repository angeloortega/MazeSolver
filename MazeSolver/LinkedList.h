/***************************************************************
 * Name:      LinkedList.h
 * Purpose:   Class used to manage lists used to represent
              fractal iterations and iterate through it's items
 * Author:    Angelo Ramirez Ortega/Guilliano D' Ambrosio
 * Created:   2017-09-21
 * Copyright: Angelo Ramirez Ortega/Guilliano D' Ambrosio
 * License:
 **************************************************************/
#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include<stdexcept>
#include "LinkedNode.h"
using namespace std;
template<typename E>

class LinkedList{
private:
    LinkedNode<E> *head;
    LinkedNode<E> *tail;
    LinkedNode<E> *current;
    int size;

public:

    LinkedList(){
        head=tail=current=new LinkedNode<E>();
        size=0;
    }

    ~LinkedList(){
        clear();
        delete head;
    }

    void insert(E pElem){
        current -> next= new LinkedNode<E>(pElem, current->next);
        if (current==tail)
        {
            tail=tail->next;
        }
        size++;
    }

    void append(E pElement) {
        tail->next = new LinkedNode<E>(pElement);
        tail = tail->next;
        size++;
    }

    E remove() throw (runtime_error){
        if (size==0)
        {
            throw runtime_error ("Lista vacia");
        }else if (current==tail)
        {

            throw runtime_error ("Final de lista");
        }else
        {
            E result=current->next->element;
            LinkedNode<E> *temp=current->next;
            current->next=current->next->next;
            if (temp==current)
            {
                tail=current;
            }
            delete temp;
            size--;
            return result;
        }
    }

    void clear(){
        current=head;
        while(current!=NULL)
        {
            head = head->next;
            delete current;
            current = head;
        }
        current=head=tail=new LinkedNode<E>();
        size = 0;
    }
    E getElement(int pos)throw (runtime_error){
            goToPos(pos);
            if (current->next==NULL)
            {
                throw runtime_error("Final de lista");
            }
            return current->next->element;
        }
    void setElement(int pos, E newElement){
        goToPos(pos);
        current->next->element = newElement;
    }
    void next(){
            if (current!=tail){
                current=current->next;
            }
        }

    E getElemNext(E pElem)throw (runtime_error){
            LinkedNode<E> *counter;
            counter=head;
            while(counter!=tail)
            {
                if(counter->next->element==pElem)
                {
                        return current->next->element;
                }else{
                    counter=counter->next;
                }
            }
            throw runtime_error("Element not found");
        }
    E getPrevious() throw (runtime_error){
            if (current==head){
                throw runtime_error("Primer elemento de la lista");
            }
            LinkedNode<E> *counter;
            counter=head;
            while(counter!=NULL){
                if (counter->next==current){
                    return counter->element;
                }
                counter=counter->next;
            }
        }

    LinkedNode<E>* searchPrevious(LinkedNode<E> *pNode){
            if (current==pNode){
                    return NULL;
            }
            LinkedNode<E> *counter;
            counter=head;
            while (counter!=pNode)
            {
                counter=counter->next;
            }
            return counter;
    }

    void previous(){
    if (current!=head){
        current=searchPrevious(current);
        }
    }
    void goToStart(){
        current = head;
    }
    void goToEnd(){
        current = tail;
    }
    int getSize(){
        return size;
    }
    void goToPos(int nPos) throw(runtime_error){
        if ((nPos < 0) || (nPos > size)) {
            throw runtime_error("Index out of bounds");
        }
        current = head;
        for (int i = 0; i < nPos; i++) {
            current = current->next;
        }
    }
    int getPos(){
        int pos = 0;
        LinkedNode<E>* temp = head;
        while (temp != current) {
            pos++;
            temp = temp->next;
        }
        return pos;
    }
    void reverse()throw(runtime_error){
        if(size == 0){
            throw runtime_error("Empty List");
        }
        if(size%2 == 0){
            int y = 0;
            int x = size-1;
            for(int p = 0; p<(size)/2; p++){
                current = head;
                for (int i = 0; i < x; i++) {
                current = current->next;
                }
                int pFinal = current->next->element;
                current = head;
                for (int i = 0; i < y; i++) {
                current = current->next;
                }
                int principio = current->next->element;
                current->next->element = pFinal;
                current = head;
                for (int i = 0; i < x; i++) {
                current = current->next;
                }
                current->next->element = principio;
                y++;
                x--;
            }
        }
        else{
            int y = 0;
            int x = size-1;
            for(int p = 0; p<(size-1)/2; p++){
                current = head;
                for (int i = 0; i < x; i++) {
                current = current->next;
                }
                int pFinal = current->next->element;
                current = head;
                for (int i = 0; i < y; i++) {
                current = current->next;
                }
                int principio = current->next->element;
                current->next->element = pFinal;
                current = head;
                for (int i = 0; i < x; i++) {
                current = current->next;
                }
                current->next->element = principio;
                y++;
                x--;
            }
        }
    }
    void exchange(int x, int y) throw (runtime_error){
        if (x <0  || y<0||x>=size ||y>=size){
            throw runtime_error("No elements exist in this position");
        }
        if(x>y){
            int primero = y;
            int segundo = x;
            x = primero;
            y = segundo;
        }
        LinkedNode<E> *p1;
        LinkedNode<E> *p2;
        LinkedNode<E> *p3;
        LinkedNode<E> *p4;
        current = head;
        for (int i = 0; i < x; i++) {
            current = current->next;
        }
        p1 = new LinkedNode<E>(current->element, current->next);
        p2 = new LinkedNode<E>(current->element, current->next->next);
        current = head;
        for (int i = 0; i < y; i++) {
            current = current->next;
        }
        p3 = new LinkedNode<E>(current->element, current->next);
        p4 = new LinkedNode<E>(current->next->element, current->next->next);
        current = head;
        for (int i = 0; i < x; i++) {
            current = current->next;
        }
        current->next = p3->next;
        current->next->next = p2->next;
        current = head;
        for (int i = 0; i < y; i++) {
            current = current->next;
        }
        current->next = p1->next;
        if(y == size-1){
            tail = p4;
        }
        else{
            current->next->next = p4->next;
        }

    }
    void concat(LinkedList<E> &lista2){
        E element;
        for(lista2.goToStart(); lista2.getPos()<lista2.size; lista2.next()){
            element = lista2.getElement();
            append(element);

            }

    }

};
#endif // LINKEDLIST_H_INCLUDED
