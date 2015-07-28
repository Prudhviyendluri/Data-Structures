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
	Node *  prev;	/* Pointer to the previous node in list.	*/

public:
	Node(     ):data(0), next(NULL), prev(NULL) {}
	Node(int d):data(d), next(NULL), prev(NULL) {}

	/* Getter functions. */
	int   get_data    () const{ return data; }
	Node* get_next_ptr() const{ return next; }
	Node* get_prev_ptr() const{ return prev; }
	
	/* Setter functions. */
	void set_data    (int d    ){ data = d  ; return; }			
	void set_next_ptr(Node *ptr){ next = ptr; return; }	
	void set_prev_ptr(Node *ptr){ prev = ptr; return; } 
	
	/* Friend classes and functions. */
	friend class Iterator_Node;

}; 


#endif
