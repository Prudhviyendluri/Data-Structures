#ifndef __QUEUE_INT_H__
#define __QUEUE_INT_H__

#include <iostream>
#include <cstdlib>
#include <stdexcept>

using std::ostream; 
using std::cout; 

/* Class to represent a queue. */
class Queue_Int{
public: 
	typedef size_t size_type					; 
	typedef int    value_type					; 

private:
	static const size_t max_queue_size = 5		;	
	value_type			data[max_queue_size]	; 
	size_type			queue_size				; 
	int					front_queue				; 
	int					back_queue				; 

	/* To print the queue. */
	void print(std::ostream& out = cout) const; 

public: 
	/* Default constructor. */
	Queue_Int():queue_size(0), front_queue(-1), back_queue(-1){
		for(int i = 0; i < max_queue_size; i++) data[i] = 0; 
	}

	/* Test whether container is empty. Returns whether the queue is 
	 * empty, i.e. whether its size is 0.
	 */
	bool empty() const { return (queue_size == 0); }

	/* Insert element. Adds a new element at the end of the queue, 
	 * after its current last element. The content of this new element 
	 * is initialized to a copy of x.
	 */
	void push(const int& x); 

	/* Delete next element. Removes the next element in the queue, effectively 
	 * reducing its size by one. The element removed is the "oldest" element in 
	 * the queue whose value can be retrieved by calling member queue::front.
	 */
	void pop(); 
		
	/* To get the size of the queue. */
	size_type size() const { return queue_size; }

	/* Access next element. Returns a reference to the next element 
	 * in the queue. This is the "oldest" element in the queue and the same element 
	 * that is popped out from the queue if member queue::pop is called.
	 */
	      value_type& front ()      { return data[front_queue]; }
	const value_type& front () const{ return data[front_queue]; }

	/* Access last element. Returns a reference to the last element in the queue. 
	 * This is the "newest" element in the queue i.e. the last element 
	 * pushed into queue.
	 */
	      value_type& back ()      { return data[back_queue]; }
	const value_type& back () const{ return data[back_queue]; }

	/* Friend function. */
	friend ostream& operator << (ostream& out, const Queue_Int& q); 

}; 

#endif