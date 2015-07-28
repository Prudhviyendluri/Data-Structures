#ifndef __LIST_H__
#define __LIST_H__

#include "Node.h"
#include "Iterator.h"

using namespace std; 

/* List of integers. */
class List_Int{
public: 
	/* Public data types. */
	typedef	size_t				size_type		;	/* Type for storing the size of list.	*/
	typedef Iterator_Node		iterator		;	
	typedef const Iterator_Node const_iterator	; 

private:
	Node		* head		;	/* First node in the list of nodes. */
	Node		* tail		;	/* Last node in the list of nodes. 	*/
	size_type	  list_size	;	/* No. of elements in the list.		*/
	
	
public: 
	/* Constructor. */
	explicit List_Int():head(NULL), tail(NULL), list_size(0){}

	/* Pushing a node to the end of the list. */
	void push_back(const int &d);

	/* To insert an element to the head of the list .*/
	void push_front(const int &d);

	/* Removes the last element in the list container, effectively reducing the list size by one. */
	void pop_back(); 

	/* Removes the first element in the list container, effectively reducing the list size by one. */
	void pop_front(); 

	/* Check if emtpy. */
	bool empty(){ return (list_size == 0); }

	/* To print the list from head to tail. */
	void print();

	/* To get the size of the list. */
	size_type size() const { return list_size; }

	/* Returns the iterator to the first element in the list. */
	iterator       begin()       { return iterator(head)      ; }
	const_iterator begin() const { return const_iterator(head); }

	/* Returns an iterator referring to the past-the-end element in the list container. */
	iterator end() { 
		if(tail == NULL) return NULL; 
		else return iterator(tail->get_next_ptr());       
	}
	const_iterator end() const { 
		if(tail == NULL) return NULL; 
		return const_iterator(tail->get_next_ptr()); 
	}

	/* Clear the list. 
	 * All the elements in the list container are dropped: their destructors are called, and 
	 * then they are removed from the list container, leaving it with a size of 0.
	 */
	void clear();

	/* The list container is extended by inserting new elements before the element at 'position'. */
	List_Int::iterator List_Int::insert (List_Int::iterator position, const int& x); 
	
	/* Swap content. 
	 * Exchanges the content of the container by the content of argument lst, which is another list object 
	 * containing elements of the same type. Sizes may differ. After the call to this member function, 
	 * the elements in this container are those which were in lst before the call, and the elements of 
	 * lst are those which were in this. All iterators, references and pointers remain valid for the 
	 * swapped objects.
	 */
	void swap(List_Int& lst); 
	
	/* Removes from the list container either a single element (position) or a range of 
	 * elements ([first,last)). 
	 */
	iterator erase ( iterator position );
	iterator erase ( iterator first, iterator last );

}; /* End of List_Int class. */

#endif

