#pragma once
#include <iostream>

using namespace std;

template < class T >
class DoublyLinkedList{
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void insertAtFront(const T& elem);
	void insertAtRear(const T& elem);
	bool removeFromFront(T& elem); //true if an item is removed, elem holds that value
	bool removeFromRear(T& elem); //true if an item is removed, elem holds that value
	bool remove(); //remove the element that the current pointer points to
	bool remove(const T& elem); //remove all occurrences of the element that is passed in.
	int size();
	bool first(T& elem);
	bool last(T& elem);
	bool next(T& elem);
	bool previous(T& elem);
	bool isEmpty();
	bool find(const T& elem); //returns a true/false value indicating if an element is present in the list
	T& at(int pos); //a method that simulates accessing the list like an array.
	int& operator[](int pos); //call at()

private:
	struct Node {
		T data;
        Node* p_next;
        Node* p_previous;
	};

	Node* p_head;
	Node* p_tail;
	Node* p_current;
	int numElements;
};

template < class T >
DoublyLinkedList<T>::DoublyLinkedList(){
    p_head = 0;
    p_tail = 0;
    p_current = 0;
    numElements = 0;
}

template < class T >
DoublyLinkedList<T>::~DoublyLinkedList(){
    Node* p_delete;
    while (!isEmpty())
    {
        p_delete = p_head;
        p_head = p_head->p_next;
        delete p_delete;
        numElements--;
    }
    //cout << "Deleting a DoublyLinkedList" << endl;
}

template < class T >
void DoublyLinkedList<T>::insertAtFront(const T& elem) {
    Node* p_newNode = new Node;
    p_newNode->data = elem;
    p_newNode->p_previous = 0;
    if (numElements == 0) {
        p_newNode->p_next = 0;
        p_tail = p_newNode;
        p_head = p_newNode;
        numElements++;
    }
    else {
        p_head->p_previous = p_newNode;
        p_newNode->p_next = p_head;
        p_head = p_newNode;
        numElements++;
    }
}

template < class T >
void DoublyLinkedList<T>::insertAtRear(const T& elem) {
    Node* p_newNode = new Node;
    p_newNode->data = elem;
    p_newNode->p_next = 0;
    if (numElements == 0) {
        p_newNode->p_previous = 0;
        p_head = p_newNode;
        p_tail = p_newNode;
        numElements++;
        return;
    }
    else {
        p_tail->p_next = p_newNode;
        p_newNode->p_previous = p_tail;
        p_tail = p_newNode;
        numElements++;
    }
}

template < class T >
bool DoublyLinkedList<T>::next(T& elem){
    bool retVal = false;

    if (p_current && p_current->p_next != 0){
        p_current = p_current->p_next;
        elem = p_current->data;
        retVal = true;
    }

    return retVal;
}

template < class T >
bool DoublyLinkedList<T>::previous(T& elem) {
    bool retVal = false;

    if (p_current && p_current->p_previous != 0){
        p_current = p_current->p_previous;
        elem = p_current->data;
        retVal = true;
    }

    return retVal;
}

template < class T >
bool DoublyLinkedList<T>::removeFromFront(T& elem) {
    bool retVal = false;

    if (p_head != 0){
        elem = p_head->data;
        p_current = p_head;
        remove();
        retVal = true;
    }

    return retVal;
}


template < class T >
bool DoublyLinkedList<T>::removeFromRear(T& elem) {
    bool retVal = false;

    if (p_tail != 0){
        elem = p_tail->data;
        p_current = p_tail;
        remove();
        retVal = true;
    }

    return retVal;
}

template < class T >
bool DoublyLinkedList<T>::remove() {
    bool retVal = false;

    if (p_current != 0){
        Node* p_temp;
        p_temp = p_current;
        if (p_temp != p_tail) {
            p_current->p_next->p_previous = p_current->p_previous;
        }
        if (p_temp != p_head) {
            p_current->p_previous->p_next = p_current->p_next;
        }
        if (p_temp == p_head) {
            p_head = p_current->p_next;
        }
        if (p_temp == p_tail) {
            p_tail = p_current->p_previous;
        }
        p_current = p_current->p_next;
        retVal = true;
        delete p_temp;
        numElements--;
    }

    return retVal;
}

template < class T >
bool DoublyLinkedList<T>::remove(const T& elem) {
    Node* p_counter;
    bool retVal = false;
    p_counter = p_head;
    for (int i = 0; i < numElements; i++) {
        if (p_counter->data == elem) {
            p_current = p_counter;
            remove();
            retVal = true;
            p_counter = p_current;
        }
        else {
            p_counter = p_counter->p_next;
        }
    }
    return retVal;
}

template < class T >
bool DoublyLinkedList<T>::first(T& elem){
    bool retVal = false;

    if (!isEmpty()){
        retVal = true;
        p_current = p_head;
        elem = p_current->data;
    }

    return retVal;
}

template < class T >
bool DoublyLinkedList<T>::last(T& elem){
    bool retVal = false;

    if (!isEmpty()){
        retVal = true;
        p_current = p_tail;
        elem = p_current->data;
    }

    return retVal;
}

template < class T >
int DoublyLinkedList<T>::size(){
    return numElements;
}

template < class T >
bool DoublyLinkedList<T>::isEmpty(){
    return size() == 0;
}

template < class T >
bool DoublyLinkedList<T>::find(const T& elem) {//returns a true/false value indicating if an element is present in the list
    Node* p_counter;
    p_counter = p_head;
    for (int i = 0; i < numElements; i++) {
        if (p_counter->data == elem) {
            return true;
        }
        else {
            p_counter = p_counter->p_next;
        }
    }
    return false;
}

template < class T >
T& DoublyLinkedList<T>::at(int pos) {
    if (pos < numElements) {
        Node* p_counter;
        p_counter = p_head;
        for (int i = 0; i < numElements; i++) {
            if (i == pos) {
                return p_counter->data;
            }
            else {
                p_counter = p_counter->p_next;
            }
        }
    }
    else {
        cout << "Tried to access an element outside the bounds..." << endl;
        throw (pos);
    }
}

template < class T >
int& DoublyLinkedList<T>::operator[](int pos){
    return at(pos);
}