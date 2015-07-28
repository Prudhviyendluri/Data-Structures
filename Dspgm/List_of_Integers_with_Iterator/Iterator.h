#ifndef __ITERATOR_NODE_H__
#define __ITERATOR__NODE_H__

#include "Node.h"

using std::cout; 
using std::endl; 

class Iterator_Node{
private:
	Node * node_ptr; 

public: 
	/* No default constructor. */
	Iterator_Node(Node* p):node_ptr(p){}

	/* Get node pointer. */
	Node * get_node_ptr(){ return node_ptr; }

	/* Overload the indirection (*) operator. */
	      int& operator*()       { assert(node_ptr != NULL); return node_ptr->data; }
	const int& operator*() const { assert(node_ptr != NULL); return node_ptr->data; }

	/* Overload the arrow (->) operator. */
	      Node* operator->()       { assert(node_ptr != NULL); return node_ptr; }
	const Node* operator->() const { assert(node_ptr != NULL); return node_ptr; }

	/* Overload equality operators. */
	bool operator==(const Iterator_Node& i){ return (this->node_ptr == i.node_ptr); }
	bool operator!=(const Iterator_Node& i){ return !(*this == i); }

	/* Overload the ++ operator (Prefix version). */
	Node& operator++(){
		node_ptr = node_ptr->get_next_ptr(); 
		return (*node_ptr); 
	}
	
	/* Overload the ++ operator (Postfix version). */
	Node operator++(int){
		Node *temp_ptr = this->node_ptr; 
		node_ptr = node_ptr->get_next_ptr(); 
		return (*temp_ptr); 
	}
}; 

#endif
