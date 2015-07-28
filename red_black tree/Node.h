#ifndef __RB_NODE_H__
#define __RB_NODE_H__

#include <iostream>
#include <cstdlib>
#include <cassert>

/* Template class to represent a node in a red-black tree. 
 *     
 *									  Parent
 *										^
 *										|
 *     +-----+-----+--------+--------+--|--+
 *     |     |     |  Data  | Color  |  !  |
 *     |  T  |  T  |        |        |     |
 *     +--|--+--|--+--------+--------+-----+
 *        |     |
 *        v     v
 *      Left   Right 
 *      child  child
 * 
 */

enum Color {Red, Black}; 

template <class type>
class Node{
private:
	type		 data	;	/* Data part of the node.					*/
	Color		 color	;	/* Height of the node.						*/
	Node<type> * right	;	/* Pointer to the next node in the tree.	*/
	Node<type> * left	;	/* Pointer to the previous node in tree.	*/
	Node<type> * parent	;	/* Pointer to parent node.					*/ 

public:
	Node(     ) :
	  data( ), color(Red), right(NULL), left(NULL), parent(NULL) {}
	Node(type d):
	  data(d), color(Red), right(NULL), left(NULL), parent(NULL) {}

	/* Getter functions. */
	type		get_data     () const { return data;   }
	Color		get_color	 () const { return color;  }
	Node<type>* get_right_ptr() const { return right;  }
	Node<type>* get_left_ptr () const { return left;   }
	Node<type>* get_parent   () const { return parent; }
	
	/* Setter functions. */
	void set_data     (type		   d  ) { data   = d  ; return; }	
	void set_color	  (Color	   c  ) { color  = c  ; return; }
	void set_right_ptr(Node<type> *ptr) { right  = ptr; return; }	
	void set_left_ptr (Node<type> *ptr) { left   = ptr; return; } 
	void set_parent   (Node<type> *ptr) { parent = ptr; return; } 
}; 

#endif
