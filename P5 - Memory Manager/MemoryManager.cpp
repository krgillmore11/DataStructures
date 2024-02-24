#include "MemoryManager.hpp"

#include <iostream>

using namespace std;

MemoryManager::MemoryManager(char* p_mem, int size) {
	//Node size is 24 on my machine running x64 in vis
	cout << "Inside MemoryManager constructor, the sizeof(Node) is: " << sizeof(Node) <<
		" sizeof(Node*) is : " << sizeof(Node*) << " size of a bool is : " << sizeof(bool) << endl << endl;

	p_memory = p_mem;

	p_head = (Node*)p_memory;//cast char pointer to type Node
	p_head->p_next = (Node*)(p_memory + (size - sizeof(Node)));//cast pointer to end of initial block (p_tail)
	p_head->p_prev = 0;
	p_head->isFree = true;
	p_head->sizeOfNode = size - (2 * sizeof(Node));//each block has a pointer to the Node on either end so this accounts for that

	//p_tail = (Node*)(p_memory + (size - sizeof(Node))); 
	p_tail = p_head->p_next; //same as line 14
	p_tail->p_next = 0;
	p_tail->p_prev = p_head;
	p_tail->isFree = false;//No block will ever be to the right of it
	p_tail->sizeOfNode = 0;
	//p_tail points p_next to zero because it is the end of the initial block
	//p_head and p_tail will not change location but pointer to prev and next will
	p_current = p_head;

	
}
void* MemoryManager::allocate(int size) {
	//Only one new node is crated because head and tail are there *different then linked list
	//Node acts as a knife to split the memory
	p_current = p_head;
	Node* p_largest = p_current;
	while (p_current->p_next != 0) { //largest slot first - finds biggest block able to cantain size
		if (p_current->sizeOfNode > p_largest->sizeOfNode && p_current->isFree) {//checks if p_current is free and larger then largest
			p_largest = p_current;
		}
		p_current = p_current->p_next;
	}

	if (p_largest->sizeOfNode >= size + sizeof(Node)) {
		Node* p_newNode;
		p_newNode = (Node*)(((char*)p_largest) + sizeof(Node) + size);//casts char pointer of largest to type Node* + new Node and size as memory location
		p_newNode->sizeOfNode = (p_largest->sizeOfNode) - size - sizeof(Node);//size of free block
		p_largest->sizeOfNode = size;//size of used
		p_largest->isFree = false;
		p_newNode->isFree = true;
		p_newNode->p_next = p_largest->p_next;//free block points to next block
		p_newNode->p_prev = p_largest;//points to used block
		p_largest->p_next = p_newNode;//used points to new block now

		return (void*)(((char*)p_largest) + sizeof(Node));//cast memory location of newly used block to void* and return
	}
	else {
		return 0;
	}
	
																					
}
void MemoryManager::deallocate(void* p_delete) {//blocks of memory on either side of it need to be checked to see if a 
												//one large block of memory can be created, this is called 'coalescing'
	p_current = p_head;
	Node* p_requested = (Node*)(((char*)p_delete) - sizeof(Node));//cast p_delete to node pointer after casting to char* ~ for comparing

	while (p_current->p_next != 0) {
		if (p_current == p_requested && !p_current->isFree) {//checks if p_delete is a node and if it is used
			if (p_requested != p_tail) {//tail is doesnt represent a block
				p_requested->isFree = true;//set to free (it is now available for use) like delete
			}
			//coalescing
			coalesc();
			break;
		}
		p_current = p_current->p_next;
	}
}
void MemoryManager::coalesc() {
	bool cont = false;
	p_current = p_head;
	while (p_current != p_tail) {
		if (p_current->p_next->isFree && p_current->isFree) {//Checks 2 blocks next to eachother to see if they are both free
			p_current->sizeOfNode += p_current->p_next->sizeOfNode + sizeof(Node);//new size is the addition of both plus the size of the node you are getting rid of
			p_current->p_next = p_current->p_next->p_next;//new p_current next pointer skips over deleted node
			p_current->p_next->p_prev = p_current;//new prev pointer pointing back to current
		}
		else{
			p_current = p_current->p_next;//iterates through all nodes on "heap"
			//doesn't need to iterate if an adjacent free block is found because its memory is set as free (deleted)
		}
	}

	//DOESNT WORK
		/*while (p_current != p_tail && p_current->p_next->isFree) {
			p_current->sizeOfNode += sizeof(Node) + p_current->p_next->sizeOfNode;//need work or other condition
			p_current->p_next = p_current->p_next->p_next;
			if (p_current != p_tail) {
				p_current = p_current->p_next;
			}
		}
	

		while (p_current != p_head && p_current->p_prev->isFree) {
			p_current->p_prev->p_next = p_current->p_next;
			p_current->p_prev->sizeOfNode += sizeof(Node) +  p_current->sizeOfNode;
			if (p_current != p_head) {
				p_current = p_current->p_prev;
			}
		}*/
}
void MemoryManager::dump() {
	int numBlock = 1;//used for output number of block from left to right
	Node* p_current = p_head;
	while (p_current->p_next != 0) {
		cout << "Block " << numBlock << ": " << p_current->sizeOfNode << " bytes of ";
		if (p_current->isFree) {//prints whether the memory is being used or not
			cout << "free";
		}
		else {
			cout << "used";
		}
		cout << " space." << endl;
		p_current = p_current->p_next;//iterates through all nodes on "heap"
		numBlock++;
	}
	cout << endl;
}
