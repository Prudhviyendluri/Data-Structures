#ifndef __ITERATOR_NODE_H__
#define __ITERATOR__NODE_H__

#include "Node.h"
#include <cstdlib>

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

	/* Don't allow the user of the class to set the node_ptr to an 
	 * arbitrary value using a public member function. 
	 * So, no set_node_ptr(). 
	 */

	/* Overload the indirection (*) operator (non-const version). */
	int& operator*(){
		/* Make sure that: 
		 *  1) this iterator is not pointing to NULL. 
		 *  2) this iterator is not pointing to 'sentinel_tail'. 
		 */
		assert(this->node_ptr != NULL); 
		assert(this->node_ptr->get_next_ptr() != NULL); 

		return this->node_ptr->data; 
	}

	/* Overload the indirection (*) operator (const version). */
	const int& operator*() const { 
		/* Make sure that: 
		 *  1) this iterator is not pointing to NULL. 
		 *  2) this iterator is not pointing to 'sentinel_tail'. 
		 */
		assert(this->node_ptr != NULL); 
		assert(this->node_ptr->get_next_ptr() != NULL); 

		return this->node_ptr->data; 
	}

	/* Overload the arrow (->) operator (non-const version). */
	int* operator->(){ 
		/* Make sure that: 
		 *  1) this iterator is not pointing to NULL. 
		 *  2) this iterator is not pointing to 'sentinel_tail'. 
		 */
		assert(this->node_ptr != NULL); 
		assert(this->node_ptr->get_next_ptr() != NULL); 

		return &(node_ptr->data); 
	}

	/* Overload the arrow (->) operator (const version). */
	const int* operator->() const { 
		/* Make sure that: 
		 *  1) this iterator is not pointing to NULL. 
		 *  2) this iterator is not pointing to 'sentinel_tail'. 
		 */
		assert(this->node_ptr != NULL); 
		assert(this->node_ptr->get_next_ptr() != NULL); 

		return &(node_ptr->data); 
	}

	/* Overload equality operators. */
	bool operator==(const Iterator_Node& i){ return (this->node_ptr == i.node_ptr); }
	bool operator!=(const Iterator_Node& i){ return !(*this == i); }

	/* Overload the ++ operator (Prefix version). */
	Node& operator++(){
		/* Make sure that: 
		 *  1) this iterator is not pointing to NULL and
		 *  2) the node to which this iterator points to have a next_ptr not 
		 *     pointing to NULL. 
		 */
		assert(this->node_ptr != NULL); 
		assert(this->node_ptr->get_next_ptr() != NULL); 

		node_ptr = node_ptr->get_next_ptr(); 
		return (*node_ptr); 
	}
	
	/* Overload the ++ operator (Postfix version). */
	Node operator++(int){
		/* Make sure that: 
		 *  1) this iterator is not pointing to NULL and
		 *  2) the node to which this iterator points to have a next_ptr not 
		 *     pointing to NULL. 
		 */
		assert(this->node_ptr != NULL); 
		assert(this->node_ptr->get_next_ptr() != NULL); 
				
		Node *temp_ptr = this->node_ptr; 
		node_ptr = node_ptr->get_next_ptr(); 
		return (*temp_ptr); 
	}

	/* Overload the -- operator (Prefix version). */
	Node& operator--(){
		/* Make sure that 
		 *  1) this iterator is not pointing to NULL and
		 *  2) the node to which this iterator points to have a prev_ptr not 
		 *     pointing to NULL. 
		 *  3) this iterator is not pointing to the begin() node. 
		 */
		assert(this->node_ptr != NULL); 
		assert(this->node_ptr->get_prev_ptr() != NULL); 
		assert(this->node_ptr->get_prev_ptr()->get_prev_ptr() != NULL); 
			
		node_ptr = node_ptr->get_prev_ptr(); 
		return (*node_ptr); 
	}

	/* Overload the -- operator (Postfix version). */
	Node operator--(int){
		/* Make sure that 
		 *  1) this iterator is not pointing to NULL and
		 *  2) the node to which this iterator points to have a prev_ptr not 
		 *     pointing to NULL. 
		 *  3) this iterator is not pointing to the begin() node. 
		 */
		assert(this->node_ptr != NULL); 
		assert(this->node_ptr->get_prev_ptr() != NULL); 
		assert(this->node_ptr->get_prev_ptr()->get_prev_ptr() != NULL);    
		
		Node *temp_ptr = this->node_ptr; 
		node_ptr = node_ptr->get_prev_ptr(); 
		return (*temp_ptr); 
	}
}; 

#endif
