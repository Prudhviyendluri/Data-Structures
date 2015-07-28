/* Static data member definition. */
template<class Type> const size_t Stack<Type>::stack_size; 

/* Add element to the top of the stack. */
template<class Type> 
void Stack<Type>::push(const value_type& x){
	if(top_of_stack == stack_size-1){	/* Check for overflow. */
		throw std::overflow_error("Stack Overflow"); 
	} 
	data[++top_of_stack] = x; 
	return; 
}

/* Removes the element from the top of the stack, effectively reducing 
 * the size by one. The value of this element can be retrieved before 
 * being popped by calling top(). 
 */
template<typename Type> 
void Stack<Type>::pop(){
	if(top_of_stack == -1){ /* Check for Underflow condition. */
		throw std::underflow_error("Stack Underflow"); 
	}	
	--top_of_stack;
	return; 
}

/* Overload the output operator. */
template<class Type>
std::ostream& operator<< 
(std::ostream& out, const Stack<Type>& s){
	for(Stack<Type>::size_type i = s.size()-1; i != UINT_MAX; i--){
		out << "+-----+" << std::endl; 		
		out << "|"       << std::setw(5) << s.data[i] << "|" 
			<< ((i == s.size() - 1) ? "<-- Top" : "") << std::endl;  
	}
	if(s.size() != 0) out << "+-----+"     << std::endl; 
	else              out << "STACK EMPTY" << std::endl; 

	return out; 
}

