#pragma once

#include <iostream>

using namespace std;

class MemoryManager {
public:
	MemoryManager(char* p_mem, int size);
	void* allocate(int size);//reserve memory
	void deallocate(void* p_delete);//set memory as usable again
	void dump();//prints information on the heap
private:
	char* p_memory;//pointer to char array brought in through driver

	struct Node { //for doubly linked "list"
		Node* p_next;
		Node* p_prev;
		bool isFree;//if block is available to be written on
		int sizeOfNode;//usable size not including nodes
	};
	Node* p_head;
	Node* p_tail;

	Node* p_current;//used for iterating

	void coalesc();//for combining free blocks that are next to eachother
};

