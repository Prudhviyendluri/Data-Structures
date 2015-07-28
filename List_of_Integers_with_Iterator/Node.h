#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <cstdlib>
#include <cassert>

/* Class to represent a node in a list. */
class Node{
private:
	int		data;	/* Data part of the node.					*/
	Node *	next;	/* Pointer to the next node in the list.	*/

public:
	Node(     ):data(0), next(NULL){}
	Node(int d):data(d), next(NULL){}

	/* Getter functions. */
	int   get_data    () const{ return data; }
	Node* get_next_ptr() const{ return next; }
	
	/* To set the data part. */
	void set_data(int d){ 
		data = d; 
		return ; 
	}

	/* To set the next_ptr part. */
	void set_next_ptr(Node *ptr){
		next = ptr; 
		return; 
	}

	/* Friend classes and functions. */
	friend class Iterator_Node;

}; 


#endif
