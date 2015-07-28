#ifndef __QUEUE_DOUBLY_LINKED_LIST_H__
#define __QUEUE_DOUBLY_LINKED_LIST_H__

#include "List_doubly_linked.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>

using std::ostream	; 
using std::cout		; 

/* Function and class declaration. */
template<class type> class Queue_doubly_Linked_List; 
template<class type>
ostream& operator << (ostream& out, const Queue_doubly_Linked_List<type>& q); 

/* Class to represent a queue using doubly linked list. */
template <class type>
class Queue_doubly_Linked_List{
public: 
	typedef size_t size_type	; 
	typedef type   value_type	;  

private:
	List_doubly_linked<type> data;  

	/* To print the queue. */
	void print(ostream& out = cout) const; 

public: 
	/* Default constructor. */
	Queue_doubly_Linked_List() : data() {}

	/* Test whether container is empty. Returns whether the queue is 
	 * empty, i.e. whether its size is 0.
	 */
	bool empty() const { return (data.size() == 0); }

	/* Insert element. Adds a new element at the end of the queue, 
	 * after its current last element. The content of this new element 
	 * is initialized to a copy of x.
	 */
	void push(const type& x); 

	/* Delete next element. Removes the next element in the queue, effectively 
	 * reducing its size by one. The element removed is the "oldest" element in 
	 * the queue whose value can be retrieved by calling member queue::front.
	 */
	void pop(); 
		
	/* To get the size of the queue. */
	size_type size() const { return data.size(); }

	/* Access next element. Returns a reference to the next element 
	 * in the queue. This is the "oldest" element in the queue and the same element 
	 * that is popped out from the queue if member queue::pop is called.
	 */
	      value_type& front ()      { return *(data.begin()); }
	const value_type& front () const{ return *(data.begin()); }

	/* Access last element. Returns a reference to the last element in the queue. 
	 * This is the "newest" element in the queue i.e. the last element 
	 * pushed into queue.
	 */
	value_type& back (){ 
		return (*Iterator_Node<type>(data.end().get_node_ptr()->get_prev_ptr())); 
	}
	const value_type& back () const{ 
		return (*Iterator_Node<type>(data.end().get_node_ptr()->get_prev_ptr()));  
	}

	/* Friend function. */
	friend ostream& operator<< <type> 
	(ostream& out, const Queue_doubly_Linked_List<type>& q); 

}; 

#include "Queue_doubly_Linked_List.cpp"

#endif