#ifndef __LIST_DOUBLY_LINKED_H__
#define __LIST_DOUBLY_LINKED_H__

#include "Node.h"
#include "Iterator_Node.h"

using namespace std; 

/* Doubly linked list template class. */
template<class type>
class List_doubly_linked{
public: 
	/* Public data types. */
	typedef	      size_t			  size_type		; /* Type to represent the size of list.  */
	typedef       Iterator_Node<type> iterator		; /* Iterator to a node in list. 		  */
	typedef const Iterator_Node<type> const_iterator; /* Constant iterator to a node in list. */

private:
	Node<type>	sentinel_head	;	/* Dummy node at the start of list. */
	Node<type>	sentinel_tail	;	/* Dummy node at the end of list.	*/
	size_type	list_size		;	/* No. of elements in the list.		*/
		
public: 
	/* Constructor. */
	explicit List_doubly_linked() : 
		sentinel_head(), sentinel_tail(), list_size(0)	
	{}

	/* Destructor. */
	virtual ~List_doubly_linked(){ clear(); } 

	/* Pushing a node to the end of the list. */
	void push_back(const type &d);

	/* To insert an element to the head of the list .*/
	void push_front(const type &d);

	/* Removes the last element in the list container, 
	 * effectively reducing the list size by one. 
	 */
	void pop_back(); 

	/* Removes the first element in the list container, 
	 * effectively reducing the list size by one. 
	 */
	void pop_front(); 

	/* Check if emtpy. */
	bool empty(){ return (this->size() == 0); }

	/* To print the list from head to tail. */
	void print();

	/* To print the reverse from tail to head. */
	void print_reverse(); 

	/* To get the size of the list. */
	size_type size() const { return list_size; }

	/* Returns the iterator to the first element in the list. */
	iterator begin(){ 
		return iterator (sentinel_head.get_next_ptr()); 
	}
	const_iterator begin() const{ 
		return const_iterator(sentinel_head.get_next_ptr()); 
	}

	/* Returns an iterator referring to the past-the-end element 
	 * in the list container. 
	 */
	iterator end(){ 
		return iterator(&sentinel_tail); 
	}
	const_iterator end() const {
		return const_iterator((Node<type>* const) &sentinel_tail); 
	}

	/* Clear the list. 
	 * All the elements in the list container are dropped: their 
	 * destructors are called, and then they are removed from the list 
	 * container, leaving it with a size of 0.
	 */
	void clear();

	/* The list container is extended by inserting new elements 
	 * before the element at 'position'. 
	 */
	typename List_doubly_linked<type>::iterator 
	List_doubly_linked<type>::insert 
	(typename List_doubly_linked<type>::iterator position, const type& x); 
	
	/* Swap content. 
	 * Exchanges the content of the container by the content of argument lst, 
	 * which is another list object containing elements of the same type. 
	 * Sizes may differ. After the call to this member function, 
	 * the elements in this container are those which were in lst before 
	 * the call, and the elements of lst are those which were in this. 
	 * All iterators, references and pointers remain valid for the 
	 * swapped objects.
	 */
	void swap(List_doubly_linked<type>& lst); 
	
	/* Removes from the list container either a single element (position) 
	 * or a range of elements ([first,last)). 
	 */
	iterator erase ( iterator position );
	iterator erase ( iterator first, iterator last );

}; /* End of List_doubly_linked class. */

#include "List_doubly_linked.cpp"

#endif

