#include "List_Int.h"

/* Pushing a node to the end of the list. */
void List_Int::push_back(const int &d){
	Node *node = new Node(d);
	list_size ++; 
	/* Check wheter the list is empty. */
	if((head == NULL) && (tail == NULL)){
		head = tail = node; 
	}
	else{
		/* List contains at least one element. */
		tail->set_next_ptr(node); 
		tail = node; 
	}
	return; 
}

/* To insert an element to the head of the list .*/
void List_Int::push_front(const int &d){
	Node *node = new Node(d);
	list_size ++; 
	/* Check wheter the list is empty. */
	if((head == NULL) && (tail == NULL)){
		head = tail = node; 
	}
	else{
		/* List contains at least one element. */
		node->set_next_ptr(head); 
		head = node; 
	}
	return; 
}

/* Removes the last element in the list container, effectively reducing the list size by one. */
void List_Int::pop_back(){
	/* Check if empty. */
	if(empty()) return ; 
	else{
		/* Check whether it contains only one node. */
		if(head == tail){
			Node *temp = head; 
			head = tail = NULL; 
			delete temp; 
			--list_size; 
		}
		else{
			/* There is more than one element in the list. */
			Node *next = head, *prev = NULL; 
			while(next != tail){
				prev = next; 
				next = next->get_next_ptr(); 
			}
			prev->set_next_ptr(NULL); 
			tail = prev; 
			delete next; 
			-- list_size; 

		}
	}
}

/* Removes the first element in the list container, effectively reducing the list size by one. */
void List_Int::pop_front(){
	if(empty()) return; 
	else{
		/* Check whether list contains only one node. */
		if(head == tail){
			Node *temp = head; 
			head = tail = NULL; 
			delete temp; 
			--list_size; 
		}
		else{
			/* List contains more than one node. */
			Node *temp = head; 
			head = head->get_next_ptr(); 
			delete temp; 
			-- list_size; 
		}
	}
}

/* Clear the list. 
 * All the elements in the list container are dropped: their destructors are called, and 
 * then they are removed from the list container, leaving it with a size of 0.
 */
void List_Int::clear(){
	while(! empty()){
		pop_front(); 
	}
}

/* Print the list from head to tail. */
void List_Int::print(){
	if(empty()){
		cout << "LIST EMPTY" << endl; 
	}
	else{
		Node *temp = head; 
		while(temp != NULL){
			cout << temp->get_data() << " "; 
			temp = temp->get_next_ptr(); 
		}
		cout << endl; 
	}
}

/* Insert a new element to the list. 
 * The list container is extended by inserting new elements before the element at 'position'. 
 */
List_Int::iterator List_Int::insert (List_Int::iterator position, const int &x){
	/* Create temporary node. */
	Node *temp = new Node(x); 

	if(position == this->begin()){
		/* Inserting at the head of the list. */
		temp->set_next_ptr(position.get_node_ptr()); 
		head = temp; 
		++ list_size; 
	}
	else if(position == this->end()){
		/* Inserting at the end of the list. */
		tail->set_next_ptr(temp); 
		tail = temp; 
		++ list_size; 
	}
	else{
		/* Inserting at the middle of the list. */
		Node *next = head, *prev = NULL; 
		while(next != position.get_node_ptr()){
			prev = next; 
			next = next->get_next_ptr(); 
		}
		prev->set_next_ptr(temp); 
		temp->set_next_ptr(next); 
		++ list_size; 
	}
	
	return iterator(temp); 
}

/* Removes from the list container a single element pointed by 'position'. */
List_Int::iterator List_Int::erase(List_Int::iterator position){
	if(position.get_node_ptr() == head){
		pop_front(); 
		return this->begin(); 
	}
	else if(position.get_node_ptr() == tail){
		pop_back(); 
		return this->end(); 
	}
	else{
		/* Deleting an element in the middle. */
		Node *next = head, *prev = NULL; 
		while(next != position.get_node_ptr()){
			prev = next; 
			next = next->get_next_ptr(); 
		}

		//cout << "Prev points to: " << prev->get_data() << endl; 
		//cout << "Next poinst to: " << next->get_data() << endl; 

		prev->set_next_ptr(next->get_next_ptr()); 
		delete next; 
		-- list_size; 
		return iterator(prev->get_next_ptr()); 
	}
}

/* Removes from the list container, a range of elements [first, last). */
List_Int::iterator List_Int::erase(iterator first, iterator last){
	iterator i = first;
	while(i != last){
		iterator temp = i; 
		i = i.get_node_ptr()->get_next_ptr(); 
		erase(temp); 
	}
	return last; 
}


