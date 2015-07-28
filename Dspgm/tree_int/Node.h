#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <cstdlib>
#include <cassert>

/* Declartion of template classes. */
template<class type> class Iterator_Node; 

/* Template class to represent a node in a tree. */
template <class type>
class Node{
private:
	type		 data;	/* Data part of the node.					*/
	Node<type> * right;	/* Pointer to the next node in the tree.	*/
	Node<type> * left;	/* Pointer to the previous node in tree.	*/

public:
	Node(     ) :data( ), right(NULL), left(NULL) {}
	Node(type d):data(d), right(NULL), left(NULL) {}

	/* Getter functions. */
	type		get_data    () const { return data;  }
	Node<type>* get_right_ptr() const{ return right; }
	Node<type>* get_left_ptr() const { return left;  }
	
	/* Setter functions. */
	void set_data     (type		 d   ) { data = d  ; return;  }			
	void set_right_ptr(Node<type> *ptr){ right = ptr; return; }	
	void set_left_ptr (Node<type> *ptr){ left = ptr; return;  } 
	
	/* Friend classes and functions. */
	friend class Iterator_Node<type>;
}; 


#endif
