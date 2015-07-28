#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <climits>

using std::cout; 
using std::endl; 
using std::ostream; 
using std::size_t; 
using std::operator<<; 

/* Stack template. */
template<class Type>
class Stack{
private: 
	/* Data types. */
	typedef size_t	size_type; 
	typedef Type	value_type; 

	/* Size of the stack. */
	static const size_t stack_size = 1000; 
	
	/* Array for holding the elements. */
	value_type data[stack_size]; 
	
	/* To keep track of the top of the stack. */
	signed int top_of_stack; 

public: 
	/* Default constructor. */
	Stack():top_of_stack(-1){}
	
	/* To check whether the stack is empty. */
	bool empty() const{ return (top_of_stack == -1); }

	/* Returns the number of elements on the stack. */
	size_type size() const{ return size_type(top_of_stack + 1); }

	/* Returns a reference to the top element of the stack. */
	      value_type& top()      { return data[top_of_stack]; } /* Non-const version.	*/
	const value_type& top() const{ return data[top_of_stack]; } /* Const version.		*/ 

	/* Add element to the top of the stack. */
	void push(const value_type& x);

	/* Removes the element from the top of the stack, effectively reducing the size by one. 
	 * The value of this element can be retrieved before being popped by calling top(). 
	 */
	void pop();

	/* Clear the stack. */
	void clear(){ 
		top_of_stack = -1; 
	}

	/* Overload the output operator. */
	friend ostream& operator<< <Type> (ostream& out, const Stack<Type>& s); 
}; 

#include "stack.cpp"

#endif

