#include "List_double_ptr_Int.h"

/* Pushing a node to the end of the list. */
void List_double_ptr_Int::push_back(const int &d){
	Node *node = new Node(d);

	/* Check whether the list is empty. */
	if(this->size() == 0){
		/* This is the first node to be inserted. */
		sentinel_head.set_next_ptr(node); 
		node->set_prev_ptr(&sentinel_head); 
		sentinel_tail.set_prev_ptr(node); 
		node->set_next_ptr(&sentinel_tail); 
	}
	else{
		/* List contains at least one element. */
		Node *temp = sentinel_tail.get_prev_ptr(); 
		temp->set_next_ptr(node); 
		node->set_prev_ptr(temp); 
		sentinel_tail.set_prev_ptr(node); 
		node->set_next_ptr(&sentinel_tail); 
	}

	list_size ++; 
	return; 
}

/* To insert an element to the head of the list .*/
void List_double_ptr_Int::push_front(const int &d){
	/* Check wheter the list is empty. */
	if(this->size() == 0){
		push_back(d); 
	}
	else{
		/* List contains at least one element. */
		Node *node = new Node(d);
		list_size ++; 

		Node *temp = sentinel_head.get_next_ptr(); 
		temp->set_prev_ptr(node); 
		node->set_next_ptr(temp); 
		node->set_prev_ptr(&sentinel_head); 
		sentinel_head.set_next_ptr(node); 
	}
	return; 
}

/* Removes the last element in the list container, 
 * effectively reducing the list size by one. 
 */
void List_double_ptr_Int::pop_back(){
	/* Check if empty. */
	if(empty()) return ; 
	else{
		/* Check whether it contains only one node. */
		if(this->size() == 1){
			Node *temp_1 = sentinel_head.get_next_ptr(); 
			sentinel_head.set_next_ptr(NULL); 
			sentinel_tail.set_prev_ptr(NULL); 
			delete temp_1; 
			--list_size;
		}
		else{
			/* Contains more than one node. */
			Node *temp_1 = sentinel_tail.get_prev_ptr(); 
			Node *temp_2 = temp_1->get_prev_ptr(); 
			temp_2->set_next_ptr(&sentinel_tail); 
			sentinel_tail.set_prev_ptr(temp_2); 
			delete temp_1; 
			--list_size; 
		}
	}
}

/* Removes the first element in the list container, 
 * effectively reducing the list size by one. 
 */
void List_double_ptr_Int::pop_front(){
	if(empty()) return; 
	else{
		/* Check whether list contains only one node. */
		if(this->size() == 1){
			pop_back(); 
		}
		else{
			/* List contains more than one node. */
			Node *temp_1 = sentinel_head.get_next_ptr(); 
			Node *temp_2 = temp_1->get_next_ptr(); 
			sentinel_head.set_next_ptr(temp_2); 
			temp_2->set_prev_ptr(&sentinel_head); 
			delete(temp_1); 
			-- list_size; 
		}
	}
}

/* Clear the list. 
 * All the elements in the list container are dropped: their destructors are called, and 
 * then they are removed from the list container, leaving it with a size of 0.
 */
void List_double_ptr_Int::clear(){
	while(! empty()){
		pop_back(); 
	}
}

/* Print the list from head to tail. */
void List_double_ptr_Int::print(){
	if(empty()){
		cout << "LIST EMPTY" << endl; 
	}
	else{
		Node *temp = sentinel_head.get_next_ptr(); 
		while(temp != &sentinel_tail){
			cout << temp->get_data() << " "; 
			temp = temp->get_next_ptr(); 
		}
		cout << endl; 
	}
}

/* Print the list from tail to head. */
void List_double_ptr_Int::print_reverse(){
	if(empty()){
		cout << "LIST EMPTY" << endl; 
	}
	else{
		Node *temp = sentinel_tail.get_prev_ptr(); 
		while(temp != &sentinel_head){
			cout << temp->get_data() << " "; 
			temp = temp->get_prev_ptr(); 
		}
		cout << endl; 
	}
}

/* Insert a new element to the list. 
 * The list container is extended by inserting new elements before 
 * the element at 'position'. 
 */
List_double_ptr_Int::iterator List_double_ptr_Int::insert (List_double_ptr_Int::iterator position, const int &x){
	if(position.get_node_ptr() == sentinel_head.get_next_ptr()){
		/* Inserting at the head of the list. */
		push_front(x); 
		return this->begin(); 
	}
	else if(position.get_node_ptr() == &sentinel_tail){
		/* Inserting at the end of the list. */
		push_back(x); 
		return iterator(sentinel_tail.get_prev_ptr()); 
	}
	else{
		/* Inserting at the middle of the list. */
		Node *node = new Node(x); 
		Node *temp = position.get_node_ptr()->get_prev_ptr(); 
		temp->set_next_ptr(node); 
		node->set_prev_ptr(temp); 
		position.get_node_ptr()->set_prev_ptr(node); 
		node->set_next_ptr(position.get_node_ptr()); 
		++ list_size; 
		return iterator(node); 
	}
}

/* Removes from the list container a single element pointed by 'position'. */
List_double_ptr_Int::iterator List_double_ptr_Int::erase
	(List_double_ptr_Int::iterator position){
	if(position.get_node_ptr() == sentinel_head.get_next_ptr()){
		/* Erasing the first element. */
		pop_front(); 
		return this->begin(); 
	}
	else if(position.get_node_ptr() == &sentinel_tail){
		/* Trying to erase the node past the last data node. 
		 * This is not possible. 
		 */
		assert(position.get_node_ptr() != &sentinel_tail); 
	}
	else if(position.get_node_ptr() == sentinel_tail.get_prev_ptr()){
		/* Erase last data node. */
		pop_back(); 
		return iterator(sentinel_tail.get_prev_ptr()); 
	}
	else{
		/* Deleting an element in the middle. 
		 * This list contains at least 3 elements for sure. 
		 */
		Node *temp = position.get_node_ptr()->get_prev_ptr(); 
		temp->set_next_ptr(position.get_node_ptr()->get_next_ptr()); 
		position.get_node_ptr()->get_next_ptr()->set_prev_ptr(temp); 
		delete (position.get_node_ptr()); 
		-- list_size; 
		return iterator(temp->get_next_ptr()); 
	}
}

/* Removes from the list container, a range of elements [first, last). */
List_double_ptr_Int::iterator List_double_ptr_Int::erase(iterator first, iterator last){
	iterator i = first;
	while(i != last){
		iterator temp = i; 
		i = i.get_node_ptr()->get_next_ptr(); 
		erase(temp); 
	}
	return last; 
}


