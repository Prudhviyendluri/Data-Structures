#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <cstdlib>
#include <cassert>

/* Template class to represent a node in a tree. 
 *     
 *									  Parent
 *										^
 *										|
 *     +-----+-----+--------+--------+--|--+
 *     |     |     |  Data  | Height |  !  |
 *     |  T  |  T  |        |        |     |
 *     +--|--+--|--+--------+--------+-----+
 *        |     |
 *        v     v
 *      Left   Right 
 *      child  child
 * 
 */
template <class type>
class Node{
private:
	type		 data	;	/* Data part of the node.					*/
	size_t		 height	;	/* Height of the node.						*/
	Node<type> * right	;	/* Pointer to the next node in the tree.	*/
	Node<type> * left	;	/* Pointer to the previous node in tree.	*/
	Node<type> * parent	;	/* Pointer to parent node.					*/ 

public:
	Node(      ):
	  data( ), height(0), right(NULL), left(NULL), parent(NULL) {}
	Node(type d):
	  data(d), height(0), right(NULL), left(NULL), parent(NULL) {}

	/* Getter functions. */
	type		get_data     () const { return data;   }
	size_t		get_height	 () const { return height; }
	Node<type>* get_right_ptr() const { return right;  }
	Node<type>* get_left_ptr () const { return left;   }
	Node<type>* get_parent   () const { return parent; }
	
	/* Setter functions. */
	void set_data     (type		   d  ) { data   = d  ; return; }	
	void set_height	  (size_t	   h  ) { height = h  ; return; }
	void set_right_ptr(Node<type> *ptr) { right  = ptr; return; }	
	void set_left_ptr (Node<type> *ptr) { left   = ptr; return; } 
	void set_parent   (Node<type> *ptr) { parent = ptr; return; } 
}; 


#endif
