#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <cstdlib>
#include <cassert>

/* Declartion of template classes. */
template<class type> class Iterator_Node; 

/* Template class to represent a node in a list. */
template <class type>
class Node{
private:
	type		 data;	/* Data part of the node.					*/
	Node<type> * next;	/* Pointer to the next node in the list.	*/
	Node<type> * prev;	/* Pointer to the previous node in list.	*/

public:
	Node(     ) :data( ), next(NULL), prev(NULL) {}
	Node(type d):data(d), next(NULL), prev(NULL) {}

	/* Getter functions. */
	type		get_data    () const{ return data; }
	Node<type>* get_next_ptr() const{ return next; }
	Node<type>* get_prev_ptr() const{ return prev; }
	
	/* Setter functions. */
	void set_data    (type		 d   ){ data = d  ; return; }			
	void set_next_ptr(Node<type> *ptr){ next = ptr; return; }	
	void set_prev_ptr(Node<type> *ptr){ prev = ptr; return; } 
	
	/* Friend classes and functions. */
	friend class Iterator_Node<type>;
}; 


#endif
