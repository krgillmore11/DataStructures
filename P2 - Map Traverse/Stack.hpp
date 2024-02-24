#pragma once
#include "DoublyLinkedList.hpp"
#include "Cell.hpp"
#include "StackUnderflowException.hpp"
#include <iostream>

using namespace std;

template < class T >
class Stack {
public:
	Stack();
	~Stack();
	void push(const T& elem);
	T pop();
	T top();
	bool isEmpty();
	int size();

private:
	DoublyLinkedList <T> list;
	int numElements;
};

template < class T >
Stack<T>::Stack() {
	numElements = 0;
}

template < class T >
Stack<T>::~Stack() {
	//delete p_list;
}

template < class T >
void Stack<T>::push(const T& elem) {
	list.insertAtFront(elem);
	numElements++;
}

template < class T >
T Stack<T>::pop() {
	T elem;
	if (list.isEmpty() == false) {
		list.removeFromFront(elem);
		numElements--;
	}
	else {
		StackUnderflowException ex;
		throw ex;
	}
	return elem;
}

template < class T >
T Stack<T>::top() {
	return list.at(0);
}

template < class T >
bool Stack<T>::isEmpty() {
	bool retVal = false;
	if (numElements == 0) {
		retVal = true;
	}
	return retVal;
}

template < class T >
int Stack<T>::size() {
	return numElements;
}