/**************************** Red_Black_Tree.cpp ****************************/
#include "Red_Black_Tree.h" 
#include <iostream>
#include <string> 
#include <queue> 
#include <vector> 
#include <iomanip>
#include <algorithm> 

/**********************************************************************/
using std::ostream; 
using std::endl; 
using std::string; 
using std::queue; 
using std::vector; 
using std::cout; 
using std::setw; 
using std::clog; 
using std::cerr; 
using std::max; 

/**********************************************************************/
/* Static data of the tree class. */
bool Red_Black_Tree::deletion_flag = false; 

/**********************************************************************/
/* Insert a new item to the tree. */
void Red_Black_Tree::insert(int x){
	if(tree_size == 0){
		/* Inserting the first node. 
		 * The parent of root node is NULL. 
		 */
		Node<int> *node = new Node<int>(x); 
		node->set_left_ptr (&NULL_NODE); 
		node->set_right_ptr(&NULL_NODE); 
		root = node; 
		root->set_parent(&NULL_NODE); 
		++ tree_size; 

		/* Recoloring and Rebalancing. */
		recolor_and_rebalance_insert(node); 
	}
	else{
		/* Tree not empty. */
		Node<int> *node = new Node<int>(x); 
		node->set_left_ptr (&NULL_NODE); 
		node->set_right_ptr(&NULL_NODE); 

		Node<int> *temp = get_root(); 
		while(1){
			if(temp->get_data() > x){
				/* Traverse the left sub-tree. */
				if(temp->get_left_ptr() == &NULL_NODE){
					/* Left sub-tree is empty. Inserting the node. */
					if(debug_flag) clog << "Inserting as left child of " 
										<< temp->get_data() << endl; 
					temp->set_left_ptr(node); 
					node->set_parent(temp); 
					++ tree_size; 
					
					/* Recoloring and Rebalancing. */
					recolor_and_rebalance_insert(node); 
					
					break; 
				}
				else{
					/* Left sub-tree not null. */
					temp = temp->get_left_ptr(); 
				}
			}
			else if(temp->get_data() < x){
				/* Traverse the right sub-tree. */
				if(temp->get_right_ptr() == &NULL_NODE){
					/* Right sub-tree is empty. Inserting the node. */
					if(debug_flag) clog << "Inserting as right child of " 
										<< temp->get_data() << endl; 
					temp->set_right_ptr(node); 
					node->set_parent(temp); 
					++ tree_size; 

					/* Recoloring and Rebalancing. */
					recolor_and_rebalance_insert(node); 

					break; 
				}
				else{
					/* Right sub-tree not null. */
					temp = temp->get_right_ptr(); 
				}
			}
			else{
				/* Data already present in the tree. */
				if(debug_flag) clog << "Data already present in tree. " << endl; 
				return; 
			}
		} /* while(1){ ... } */

	} /* Tree not empty. */

	return; 
}

/**********************************************************************/
/* Search for a key. 
 * Returns pointer to NULL_NODE if not found and pointer to node otherwise. 
 */
Node<int>* Red_Black_Tree::search(int value){
	Node<int> *curr_node = get_root(); 
	while(curr_node != &NULL_NODE){ 
		if(value == curr_node->get_data())
			return curr_node; 
		else if(value < curr_node->get_data())
			curr_node = curr_node->get_left_ptr(); 
		else if(value > curr_node->get_data())
			curr_node = curr_node->get_right_ptr(); 
	}
	return NULL; 
}

/**********************************************************************/
/* To get the parent node, given a pointer to a node */
Node<int>* Red_Black_Tree::get_parent(Node<int>* node){
	if((node == &NULL_NODE) || (node == NULL)) return &NULL_NODE; 
	return node->get_parent(); 
}

/* To get the parent node, given the value of the node */
Node<int>* Red_Black_Tree::get_parent(int value){
	Node<int>* node = search(value); 
	return get_parent(node); 
}

/**********************************************************************/
/* To check whether the node is the left child of its parent,  
 * given a pointer to a node. 
 */
bool Red_Black_Tree::is_left_child(Node<int>* node){
	if((node == &NULL_NODE) || (node == NULL)) return false; 
	if(is_root(node)){
		/* For root node, return false. */
		return false; 
	}
	else{
		return (get_parent(node)->get_left_ptr() == node); 
	}
}

/* To check whether the node is the left child of its parent; 
 * given the value of a node. 
 */
bool Red_Black_Tree::is_left_child(int value){
	Node<int>* node = search(value); 
	return is_left_child(node); 
}

/**********************************************************************/
/* To check whether the node is the right child of its parent; 
 * given a pointer to a node. 
 */
bool Red_Black_Tree::is_right_child(Node<int>* node){
	if((node == &NULL_NODE) || (node == NULL)) return false; 
	if(is_root(node)){
		/* For root node, return false. */
		return false; 
	}
	else{
		return (get_parent(node)->get_right_ptr() == node); 
	}
}

/* To check whether a node is the right child of its parent; 
 * given the value of the node. 
 */
bool Red_Black_Tree::is_right_child(int value){
	Node<int>* node = search(value); 
	return is_right_child(node); 
}

/**********************************************************************/
/* To check whether a given node is a root node; 
 * given a pointer to a node. 
 */
bool Red_Black_Tree::is_root(Node<int>* node){
	if((node == &NULL_NODE) || (node == NULL)) return false; 
	return (get_root() == node); 
}

/* To check whether a given node is a root node; 
 * given the value of the node. 
 */
bool Red_Black_Tree::is_root(int value){
	return (get_root()->get_data() == value); 
}

/**********************************************************************/
/* To check whether a given node is a leaf node; 
 * given a pointer to a node. 
 */
bool Red_Black_Tree::is_leaf(Node<int>* node){
	if((node == &NULL_NODE) || (node == NULL)) return false; 
	return (
		(node->get_left_ptr () == &NULL_NODE) && 
		(node->get_right_ptr() == &NULL_NODE)
	); 
}

/* To check whether a given node is a leaf node, 
 * given value of a node. 
 */
bool Red_Black_Tree::is_leaf(int value){
	Node<int>* node = search(value); 
	return is_leaf(node); 
}

/**********************************************************************/
/* To check whether a node has two children, given a pointer to the 
 * node. 
 */
bool Red_Black_Tree::has_two_children(Node<int>* node){
	if((node == &NULL_NODE) || (node == NULL)) return false; 
	return (
		(node->get_left_ptr () != &NULL_NODE) &&
		(node->get_right_ptr() != &NULL_NODE)
	); 
}

/* To check whether a node has two children, given value of a node. */
bool Red_Black_Tree::has_two_children(int value){
	Node<int>* node = search(value); 
	return has_two_children(node); 
}

/**********************************************************************/
/* To check whether a node has only one child, given a pointer to the 
 * node. 
 */
bool Red_Black_Tree::has_only_one_child(Node<int>* node){
	if((node == &NULL_NODE) || (node == NULL)) return false; 
	return (
		(
			(node->get_left_ptr () != &NULL_NODE) &&
			(node->get_right_ptr() == &NULL_NODE)
		) ||
		(
			(node->get_left_ptr () == &NULL_NODE) &&
			(node->get_right_ptr() != &NULL_NODE)
		)
	); 
}

/**********************************************************************/
/* To check whether a node has only one child, given value of a node. */
bool Red_Black_Tree::has_only_one_child(int value){
	Node<int>* node = search(value); 
	return has_only_one_child(node); 
}

/**********************************************************************/
/* To clear the tree given a pointer to a specific node. 
 * Complexity: O(n)
 */
void Red_Black_Tree::clear(Node<int>* node){
	if((node == &NULL_NODE) || (node == NULL)) return; 
	else{
		/* Recursive calls. */
		clear(node->get_left_ptr ()); 
		clear(node->get_right_ptr()); 
		
		if(! is_root(node)){
			if(is_left_child(node)){
				get_parent(node)->set_left_ptr(&NULL_NODE); 
			}
			else{
				assert(is_right_child(node)); 
				get_parent(node)->set_right_ptr(&NULL_NODE); 
			}
		}
		else{
			root = &NULL_NODE; 
		}

		delete node; 
		--tree_size; 
	}
}

/**********************************************************************/
/* To clear the entire tree. 
 * Complexity: O(n)
 */ 
void Red_Black_Tree::clear(){
	clear(get_root()); 
	root = &NULL_NODE; 
	return; 
}

/**********************************************************************/
/* To traverse the tree 'inorder'. 
 * Uses node_ptr as the root of the tree. 
 */
void Red_Black_Tree::inorder(Node<int> *node_ptr, ostream& out) const {
	if((node_ptr == NULL) || (node_ptr == &NULL_NODE)){
		return; 
	}
	else{
		inorder(node_ptr->get_left_ptr(), out); 
		out << node_ptr->get_data() << " "; 
		inorder(node_ptr->get_right_ptr(), out); 
	}
	return; 
}

/**********************************************************************/
/* To traverse the tree 'inorder'. 
 * Always starts from the root. 
 */
void Red_Black_Tree::inorder(ostream& out) const {
	inorder(get_root(), out); 
	out << endl; 
	return; 
}

/**********************************************************************/
/* To get the height of a particular node. 
 * Complexity: O(n) where n is the number of elements in the 
 *                  subtree with 'node' as the root. 
 * If there is only the root node, then the height is 0. 
 * If there are no nodes at all, then height is -1. 
 */ 
int Red_Black_Tree::get_height(Node<int> *node) const{
	if((node == &NULL_NODE) || (node == NULL)) return -1; 
	else{
		int left_val  = get_height(node->get_left_ptr ()); 
		int right_val = get_height(node->get_right_ptr()); 
		int max_val   = max(left_val, right_val) + 1; 

		return max_val; 
	}
}

/* To get the height of the entire tree. 
 * Complexity: O(n). 
 */
int Red_Black_Tree::get_height() const{
	return get_height(get_root()); 
}

/**********************************************************************/
void Red_Black_Tree::left_rotation(Node<int> *node){
	Node<int> *root = node; 
	if((root == NULL) || (root == &NULL_NODE)) return; 

	Node<int> *pivot = root->get_right_ptr(); 
	if(pivot == &NULL_NODE) return; 

	if(debug_flag) clog << "Left rotating" << endl
						<< "root : " << root->get_data () << ", " 
						<< "pivot: " << pivot->get_data() << endl; 

	root->set_right_ptr(pivot->get_left_ptr()); 
	if(root->get_right_ptr() != &NULL_NODE) root->get_right_ptr()->set_parent(root); 
	pivot->set_left_ptr(root); 
	
	/* Setting the parent pointers. */
	pivot->set_parent(root->get_parent()); 
	if(is_root(root)) set_root(pivot); 
	root->set_parent(pivot);
	
	if(! is_root(pivot)){
		/* Setting the left/right pointer of parent. */
		if(pivot->get_parent()->get_left_ptr() == root){
			pivot->get_parent()->set_left_ptr(pivot); 
		}
		else if(pivot->get_parent()->get_right_ptr() == root){
			pivot->get_parent()->set_right_ptr(pivot); 
		}
		else{
			cout << "Error: neither left or right child" << endl; 
			assert(0); 
		}
	}

	if(debug_flag) clog << "After left rotation: ", print_tree(); 

	return; 
}

/**********************************************************************/
void Red_Black_Tree::right_rotation(Node<int> *node){
	Node<int> *root = node; 
	if((root == NULL) || (root == &NULL_NODE)) return; 
	
	Node<int> *pivot = root->get_left_ptr(); 
	if(pivot == &NULL_NODE) return; 

	if(debug_flag) clog << "Right rotating" << endl
						<< "root : " << root->get_data()  << ", " 
						<< "pivot: " << pivot->get_data() << endl; 

	root->set_left_ptr(pivot->get_right_ptr()); 
	if(pivot->get_right_ptr() != &NULL_NODE) pivot->get_right_ptr()->set_parent(root); 
	pivot->set_right_ptr(root); 
	
	/* Setting the parent pointers. */
	pivot->set_parent(root->get_parent()); 
	if(is_root(root)) set_root(pivot); 
	root->set_parent(pivot);

	/* Setting the left/right pointer of parent. */
	if(!is_root(pivot)){
		if(pivot->get_parent()->get_left_ptr() == root){
			pivot->get_parent()->set_left_ptr(pivot); 
		}
		else if(pivot->get_parent()->get_right_ptr() == root){
			pivot->get_parent()->set_right_ptr(pivot); 
		}
		else{
			cout << "Error: neither left or right child" << endl; 
			assert(0); 
		}
	}

	if(debug_flag) clog << "After right rotation: ", print_tree(); 

	return; 
}
/**********************************************************************/
/* To get the grandparent of a node. 
 * 
 * Eg. 
 *		 		  /
 *			     () <-- Grandparent
 *		        /  
 *		       /    
 *  Parent--> ()    
 *		     /
 *		    /
 * Node--> () 
 * 
 */
Node<int>* Red_Black_Tree::get_grandparent(Node<int> *node){
	if((node != NULL) && (node->get_parent() != &NULL_NODE) && (node != &NULL_NODE)){
		return node->get_parent()->get_parent(); 
	}
	else{
		return &NULL_NODE; 
	}
}

/**********************************************************************/
/* To get the uncle of a node. 
 * 
 * Eg. 
 *		 		  /
 *			     () <-- Grandparent
 *		        /  \
 *		       /    \
 *  Parent--> ()    () <-- Uncle
 *		     /     /  \
 *		    /     /____\ 
 * Node--> () 
 * 
 */
Node<int>* Red_Black_Tree::get_uncle(Node<int> *node){
	if(node == NULL) return NULL;
	if(node == &NULL_NODE) return NULL; 
	Node<int>* grand_parent = get_grandparent(node); 
	if(grand_parent == &NULL_NODE){
		/* No grandparent mean no uncle. */
		return &NULL_NODE; 
	}
	else{
		if(is_left_child(node->get_parent())){
			/* The parent is the left child of grandparent. 
			 * So the right child of grandparent is the uncle. 
			 */
			return grand_parent->get_right_ptr(); 
		}
		else{
			/* The parent is the right child of grandparent. 
			 * So the left child of grandparent is the uncle. 
			 */
			assert(is_right_child(node->get_parent())); 
			return grand_parent->get_left_ptr(); 
		}
	}
}

/**********************************************************************/
/* To get the sibling of a node. 
 * 
 * Eg. 
 *		      \  		
 *  Parent--> ()    
 *		     /  \
 *		    /    \
 * Node--> ()    () <-- Sibling
 *        / \    / \
 *       /___\  /___\
 * 
 */
Node<int>* Red_Black_Tree::get_sibling(Node<int>* node){
	if(node == NULL)        return &NULL_NODE; 
	if(is_root(node))       return &NULL_NODE; 
	if(is_left_child(node)) return get_parent(node)->get_right_ptr(); 
	else                    return get_parent(node)->get_left_ptr (); 
}

/**********************************************************************/
/* Various functions related to insertion. 
 * 
 * The node's parent, grandparent, and uncle are as follows: 
 * Eg. 
 *		 		  /
 *			     () <-- Grandparent
 *		        /  \
 *		       /    \
 *  Parent--> ()    () <-- Uncle
 *		     /     /  \
 *		    /     /____\
 * Node--> () 
 * 
 * Totally there are 5 cases to be considered when you insert a node: 
 * 
 * case 1: When the node inserted is root. 
 * case 2: When the parent of node is black. 
 * case 3: When both the parent and the uncle are red. 
 * case 4: When the parent is red but the uncle is black and
 * 		     --> (a) node is the right child of parent and parent 
 * 			         is the left child of its grandparent. 
 * 
 * 			 --> (b) node is the left child of parent and parent
 * 				     is the right child of its grandparent. 
 * 
 * 
 * case 5: When the parent is red but the uncle is black and 
 *           --> (a) node is the left child of parent and parent 
 * 			         is the left child of its grandparent. 
 * 
 * 			 --> (b) node is the right child of parent and parent
 * 				     is the right child of its grandparent. 
 */

void Red_Black_Tree::insert_case_1(Node<int>* node){
	if(debug_flag) clog << "In insert_case_1" << endl; 
	if(node == NULL      ) return; 
	if(node == &NULL_NODE) return; 
	if(is_root(node)){
		/* case 1  : When the node inserted is root. 
		 * Solution: Set the color of node to black. 
		 */
		node->set_color(Black); 
	}
	else{
		/* Go to case 2. */
		insert_case_2(node); 
	}

	return; 
}

void Red_Black_Tree::insert_case_2(Node<int>* node){
	if(debug_flag) clog << "In insert_case_2" << endl; 
	if(node == NULL      ) return; 
	if(node == &NULL_NODE) return; 
	if(node->get_parent()->get_color() == Black){
		/* case 2  : When the parent of node is black. 
		 * Solution: Nothing needs to be done; it's a valid red-black tree. 
		 */
		if(debug_flag) clog << "Nothing needs to be done" << endl; 
		return; 
	}
	else{
		/* Go to case 3. */
		insert_case_3(node); 
	}

	return; 
}

void Red_Black_Tree::insert_case_3(Node<int>* node){
	if(debug_flag) clog << "In insert_case_3" << endl; 
	if((node == NULL) || (node == &NULL_NODE)) return; 
	
	Node<int> *uncle_node = get_uncle(node); 
	if((uncle_node != &NULL_NODE) && (uncle_node->get_color() == Red)){
		/* case 3  : When both the parent and the uncle are red. 
		 * Solution: Both parent and uncle can be repainted as 
		 *           black and grandparent becomes red. 
		 * 
		 * Control came from case_2 to case_3 because the color of 
		 * parent is not black; so that need not be explicitly 
		 * checked. 
		 */
		node->get_parent()->set_color(Black); 
		uncle_node->set_color(Black); 
		Node<int> *grandparent_node = get_grandparent(node); 
		grandparent_node->set_color(Red); 

		/* Now, start from case_1 for grandparent.  
		 * This is done because we have just changed the color
		 * of grandparent to red, which may have disturbed 
		 * property 2 (root is black) and/or property 4 (both children
		 * of every node are black). 
		 */
		insert_case_1(grandparent_node); 
		if(debug_flag) clog << "After insert_case_3: " << endl, print_tree(); 
	}
	else{
		/* Go to case 4. */
		insert_case_4(node); 
	}

	return; 
}

void Red_Black_Tree::insert_case_4(Node<int>* node){
	/* case 4: When the parent is red but the uncle is black and
	 * 		     --> (a) node is the right child of parent and parent 
	 * 			         is the left child of its grandparent. 
	 * 
	 * 			 --> (b) node is the left child of parent and parent
	 * 				     is the right child of its grandparent. 
	 * 
	 * Solution: In this case, a left rotation that switches the roles 
	 *           of the current 'node' and its parent can be performed.  
	 *           Then, the former parent node P is dealt with using 
	 *           case 5 (relabeling N and P) because property 4 (both 
	 *           children of every red node are black) is still violated. 
	 *
	 */
	if(debug_flag) clog << "In insert_case_4" << endl; 
	if((node == NULL) || (node == &NULL_NODE)) return; 

	//Node<int> *grandparent_node = get_grandparent(node); 
	Node<int>* temp_node_ptr = &NULL_NODE; 

	if(is_right_child(node) && (is_left_child(node->get_parent()))){
		/* Case 4(a). */
		left_rotation(node->get_parent()); 
		temp_node_ptr = node->get_left_ptr(); 
	}
	else if(is_left_child(node) && (is_right_child(node->get_parent()))){
		/* Case 4(b). */
		right_rotation(node->get_parent()); 
		temp_node_ptr = node->get_right_ptr(); 
	}
	else{
		temp_node_ptr = node; 
		if(debug_flag) clog << "Not case 4" << endl; 
	}
	/* After doing the left or right rotation, go to case 5 since 
	 * case 4 results in two consecutive nodes (left-left or 
	 * right-right) having red color which is not allowed in 
	 * a red-black tree. 
	 */
	
	if(debug_flag) clog << "Passing control to insert_case_5: " << endl; 
	insert_case_5(temp_node_ptr); 

	return; 
}

void Red_Black_Tree::insert_case_5(Node<int>* node){
	/* case 5: When the parent is red but the uncle is black and 
     *           --> (a) node is the left child of parent and parent 
	 * 			         is the left child of its grandparent. 
	 * 
	 * 			 --> (b) node is the right child of parent and parent
	 * 				     is the right child of its grandparent. 
	 * 
	 * Solution: (a) Rotate right with grandparent as the root and 
	 *				 parent as the pivot; and then interchange the 
	 *				 colors of parent and grandparent. 
	 * 
	 *           (b) Rotate left with grandparent as the root and 
	 *				 parent as the pivot; and then interchange the 
	 *				 colors of parent and grandparent. 
	 */
	if(debug_flag) clog << "In insert_case_5" << endl; 
	if((node == NULL) || (node == &NULL_NODE)) return; 

	Node<int> *grandparent_node = get_grandparent(node);
	assert(grandparent_node != &NULL_NODE); 
	cout << "G: " << grandparent_node->get_data() << endl; 

	node->get_parent()->set_color(Black); 
	grandparent_node->set_color(Red); 
	if(is_left_child(node)) right_rotation(grandparent_node); 
	else left_rotation(grandparent_node); 

	if(debug_flag) clog << "After insert_case_5" << endl, print_tree(); 

	return; 
}

/**********************************************************************/
void Red_Black_Tree::recolor_and_rebalance_insert(Node<int> *node){
	if((node == NULL) || (node == &NULL_NODE)) return; 

	/* Start from insert_case_1. */
	insert_case_1(node);

	return; 
}

/**********************************************************************/
/* To print the tree. */
void Red_Black_Tree::print_tree(ostream& out) const {
	if(size() == 0){ 
		out << "Empty Tree" << endl; 
		return; 
	}

	size_t				temp_counter	= 0		; 
	queue<Node<int>*>	temp_q					; 
	vector<Node<int>*>	temp_v					; 
	Node<int>			*curr_node_ptr	= NULL	; 

	temp_q.push(get_root()), temp_counter += 1; 
	
	vector<size_t> lr_node_count; 
	size_t max_nodes = (size_t)pow(2.0, get_height() + 1.0) - 1; 

	while(temp_counter <= max_nodes){
		curr_node_ptr = temp_q.front(), temp_q.pop(); 
		temp_v.push_back(curr_node_ptr); 
		++ temp_counter; 

		if(curr_node_ptr != NULL){
			if(curr_node_ptr->get_left_ptr() != &NULL_NODE)
				temp_q.push(curr_node_ptr->get_left_ptr()); 
			else
				temp_q.push(NULL); 
			
			if(curr_node_ptr->get_right_ptr() != &NULL_NODE)
				temp_q.push(curr_node_ptr->get_right_ptr()); 
			else
				temp_q.push(NULL); 
		}
		else{
			temp_q.push(NULL), temp_q.push(NULL); 
		}
	}

	/* 
	for(vector<Node<int>*>::iterator i = temp_v.begin(); i != temp_v.end(); i++){
		if((*i) == NULL) out << "NULL "; 
		else out << (*i)->get_data() << " "; 
	}
	*/
	out << endl; 
	
	size_t h = get_height(); 

	vector<size_t> spaces; 
	spaces.push_back(0); 
	for(size_t i = 0; i <= h; i++){
		spaces.push_back((spaces[i]+1) * 2); 
	}
	reverse(spaces.begin(), spaces.end()); 

	size_t counter = 0; 
	for(size_t i = 0; i <= h; i++){ /* No. of levels. */
		lr_node_count.clear(); 
		for(size_t k = 0; k < pow(2.0, i*1.0); k++){ /* No. of nodes in one level. */
			if(counter > max_nodes) break; 

			/* Spaces before num. */
			for(size_t j = 0; j < spaces[i]; j++) out << ' '; 
			
			/* Printing num. */
			if(temp_v[counter] != NULL){
				if(temp_v[counter]->get_color() == Red)
					color_print(temp_v[counter]->get_data(), RED); 
				else
					color_print(temp_v[counter]->get_data(), YELLOW); 

				if(temp_v[counter]->get_left_ptr() != &NULL_NODE)
					lr_node_count.push_back(1); 
				else
					lr_node_count.push_back(0); 

				if(temp_v[counter]->get_right_ptr() != &NULL_NODE)
					lr_node_count.push_back(1); 
				else
					lr_node_count.push_back(0); 

				++ counter; 
			}
			else{
				out << setw(3) << ' '; 

				lr_node_count.push_back(0); /* Left.  */
				lr_node_count.push_back(0); /* Right. */

				++ counter; 
			}

			/* Printing spaces after num. */
			for(size_t j = 0; j < spaces[i]+1; j++) out << ' '; 
		}
		out << endl;

		if(counter > max_nodes) break; 
		
		/* Printing arrows. */
		//cout << "lr size: " << lr_node_count.size() << endl; 
		size_t count_1 = spaces[i], count_2 = 0, count_3 = 1;  
		for(size_t j = 0; j < spaces[i]/2; j++){	/* No. of lines in arrow. */
			for(size_t k = 0; k < pow(2.0, i*1.0); k++){	/* No. of arrows per level. */
				/* Spaces before left arrow. */
				for(size_t l = 0; l < count_1-count_3; l++) out << ' '; 

				/* Left arrow. */
				color_print(((lr_node_count[k*2] == 1) ? "/" : " "), GREEN); 
				
				/* Spaces between left and right arrows. */
				for(size_t l = 0; l < 3+count_2; l++) out << ' '; 

				/* Right arrow. */
				color_print(((lr_node_count[k*2+1] == 1) ? "\\" : " "), GREEN); 

				/* Spaces after right arrow. */
				for(size_t l = 0; l < count_1-count_3; l++) out << ' '; 

				/* The extra one space. */
				out << " "; 
			}
			out << endl;
			count_2 += 2;
			count_3 ++; 
		} 
	}
	out << endl; 
	
	return; 
}

/**********************************************************************/
/* To delete a node with a specific value. 
 * Returns true on success and false on failure. 
 */
bool Red_Black_Tree::delete_node(int value){
	Node<int>* node = search(value); 
	return delete_node(node); 
}

/**********************************************************************/
/* Various functions related to deletion. */

void Red_Black_Tree::delete_case_1   (Node<int> *node){
	assert(node != NULL); 
	if(debug_flag) clog << "In delete_case_1(" << node->get_data() << ")" << endl; 

	/* If node is the root node, we are done. 
	 * Else go to delet_case_2(). 
	 */
	if(is_root(node)) return; 
	else delete_case_2(node); 

	return; 
}

void Red_Black_Tree::delete_case_2(Node<int> *node){
	assert(node != NULL); 
	if(debug_flag) clog << "In delete_case_2(" << node->get_data() << ")" << endl; 

	Node<int>* s = get_sibling(node); 
	if(s->get_color() == Red){
		if(debug_flag) clog << "It is a valid case_2 since Sibling " 
							<< s->get_data() << " is Red" << endl; 
		
		if(debug_flag) clog << "Changing color of " << node->get_parent()->get_data() 
							<< " to Red" << endl; 
		node->get_parent()->set_color(Red); 

		if(debug_flag) clog << "Changing color of " << s->get_data() << " to Black. " << endl; 
		s->set_color(Black); 
		
		if(is_left_child(node)){
			if(debug_flag) clog << "Doing left rotation with " 
								<< node->get_parent()->get_data() << " as root" << endl; 
			left_rotation(node->get_parent()); 
		}
		else{
			if(debug_flag) clog << "Doing right rotation with " 
								<< node->get_parent()->get_data() << " as root" << endl; 
			right_rotation(node->get_parent()); 
		}

		if(debug_flag) clog << "After rotation: \n", print_tree(); 
	}
	
	/* Now, go to delete_case_3(). */
	if(debug_flag) clog << "Going to delete_case_3() from delete_case_2(). " << endl; 
	delete_case_3(node); 

	return; 
}

void Red_Black_Tree::delete_case_3   (Node<int> *node){
	assert(node != NULL); 
	if(debug_flag) clog << "In delete_case_3(" << node->get_data() << ")" << endl; 

	Node<int>* s = get_sibling(node); 

	if( 
		(node->get_parent()->get_color() == Black)	&&
		(s                 ->get_color() == Black)	&& 
		(s->get_left_ptr ()->get_color() == Black)	&& 
		(s->get_right_ptr()->get_color() == Black)
	){
		if(debug_flag) clog << "Valid case_3. " << endl 
							<< "Color of P, S, S(L) and S(R) are all black" << endl; 
		
		/* Setting the color of sibling as red. */
		if(debug_flag) clog << "Setting the color of sibling " << s->get_data() 
							<< " as Red" << endl; 
		s->set_color(Red); 
		
		if(debug_flag) clog << "Going to delete_case_1() from delete_case_3(). " << endl; 
		delete_case_1(node->get_parent()); 
	}
	else{
		if(debug_flag) clog << "Not a valid delete_case_3. " << endl 
							<< "Going to delete_case_4(). " << endl; 
		delete_case_4(node); 
	}

	return; 
}

void Red_Black_Tree::delete_case_4(Node<int> *node){
	assert(node != NULL); 
	if(debug_flag) clog << "In delete_case_4(" << node->get_data() << ")" << endl; 

	Node<int>* s = get_sibling(node); 

	if( 
		(node->get_parent()->get_color() == Red  )	&&
		(s                 ->get_color() == Black)	&& 
		(s->get_left_ptr ()->get_color() == Black)	&& 
		(s->get_right_ptr()->get_color() == Black)
	){
		if(debug_flag) clog << "Valid case_4. " << endl 
							<< "Color of P is Red and Color S, S(L) and S(R) are all black" 
							<< endl; 

		/* Change the color of S to red and color of parent to black. */
		if(debug_flag) clog << "Change color of Sibling to Red and "
							<< "color of Parent to Black. " << endl; 
		s->set_color(Red); 
		node->get_parent()->set_color(Black); 
	}
	else{
		if(debug_flag) clog << "Not a valid delete_case_4. " << endl 
							<< "Going to delete_case_5(). " << endl; 
		delete_case_5(node); 
	}
}

void Red_Black_Tree::delete_case_5(Node<int> *node){
	assert(node != NULL); 
	if(debug_flag) clog << "In delete_case_5(" << node->get_data() << ")" << endl; 

	Node<int>* s = get_sibling(node); 

	if(s->get_color() == Black){
		if(
			(is_left_child(node)				     ) && 
			(s->get_right_ptr()->get_color() == Black) && 
			(s->get_left_ptr ()->get_color() == Red  )
		){
			if(debug_flag) clog << "Valid delete_case_5(). " 
								<< "N is a left child, S(R) is Black and S(L) is Red. " 
								<< endl; 
			s->set_color(Red); 
			s->get_left_ptr()->set_color(Black); 
			right_rotation(s); 
		}
		else if(
			(is_right_child(node)				     ) && 
			(s->get_left_ptr ()->get_color() == Black) && 
			(s->get_right_ptr()->get_color() == Red  )
		){
			if(debug_flag) clog << "Valid delete_case_5(). " 
								<< "N is a right child, S(L) is Black and S(R) is Red. " 
								<< endl; 
			s->set_color(Red); 
			s->get_right_ptr()->set_color(Black); 
			left_rotation(s); 
		}
	}

	if(debug_flag) clog << "Going to delete_case_6() from delete_case_5() " << endl; 
	delete_case_6(node); 

	return; 
}

void Red_Black_Tree::delete_case_6   (Node<int> *node){
	assert(node != NULL); 
	if(debug_flag) clog << "In delete_case_6(" << node->get_data() << ")" << endl; 

	Node<int>* s = get_sibling(node); 

	s->set_color(node->get_parent()->get_color()); 
	node->get_parent()->set_color(Black); 
	
	if(is_left_child(node)){
		s->get_right_ptr()->set_color(Black); 
		if(debug_flag) clog << "Doing left_rotation with " 
							<< node->get_parent()->get_data() 
							<< " as root. " << endl; 
		left_rotation(node->get_parent()); 
	}
	else{
		s->get_left_ptr()->set_color(Black); 
		if(debug_flag) clog << "Doing right_rotation with " 
							<< node->get_parent()->get_data() 
							<< " as root. " << endl; 
		right_rotation(node->get_parent()); 
	}

	return; 
}

/**********************************************************************/
/* To delete a node when a pointer to it is available. 
 * Returns true on success and false on failure. 
 */
bool Red_Black_Tree::delete_node(Node<int>* node){
	if((node == NULL) || (node == &NULL_NODE)){
		if(debug_flag) clog << "Node pointer is NULL" << endl
							<< "Deletion cancelled" << endl; 
		return false; 
	}
	else{
		if(debug_flag) clog << "Deleting node " << node->get_data() << endl; 

		if(has_two_children(node)){
			/* This node has two children. */
			if(debug_flag) clog << "Deleting a node with two siblings. " << endl;

			Node<int>* inorder_successor_or_inorder_predecessor = NULL; 
			if(deletion_flag == false){
				deletion_flag = true; 
				inorder_successor_or_inorder_predecessor = get_inorder_successor(node); 
				if(debug_flag) clog << "Using inorder successor: " 
									<< inorder_successor_or_inorder_predecessor->get_data() << endl; 
			}
			else{
				deletion_flag = false; 
				inorder_successor_or_inorder_predecessor = get_inorder_predecessor(node); 
				if(debug_flag) clog << "Using inorder predecessor: " 
									<< inorder_successor_or_inorder_predecessor->get_data() << endl; 
			}
			assert(inorder_successor_or_inorder_predecessor != NULL); 
	
			/* Save the data part of inorder_successor_or_inorder_predecessor node. */
			int temp = inorder_successor_or_inorder_predecessor->get_data(); 

			/* Now delete the inorder_successor_or_inorder_predecessor node. 
			 * This node will either be a leaf node or will have max one child. 
			 */
			delete_node(inorder_successor_or_inorder_predecessor); 

			/* Now, copy the data part; color remains the same. */
			if(debug_flag) clog << "Copying data part" << endl; 
			node->set_data(temp);  
							
			if(debug_flag) clog << "After deletion: \n", print_tree(); 
			return true; 
		}
		else{
			/* This node has one child or no children (null leaves in RB tree). */

			if(is_leaf(node)){
				/* It is a leaf node (with two null leaves; for RB tree). */
				if(debug_flag) clog << "Deleting a leaf node" << endl; 
				
				if(is_root(node)){
					/* It is a root and this is the only node in this tree. */
					if(debug_flag) clog << "Deleting root node" << endl; 
					root = &NULL_NODE; 
				}
				else if(is_left_child(node)){
					/* If it is a red node, it can be just deleted. 
					 * If it is a black node, then call delete_one_child() function. 
					 */
					if(node->get_color() != Red){
						if(debug_flag) clog << "It is a black node. " << endl; 
						delete_case_1(node); 
					}
					else{
						if(debug_flag) clog << "It is a red node. " 
											<< "So it can simply be deleted" << endl; 
					}

					get_parent(node)->set_left_ptr(&NULL_NODE); 
				}
				else{
					assert(is_right_child(node)); 

					/* If it is a red node, it can be just deleted. 
					 * If it is a black node, then call delete_case_1() function. 
					 */
					if(node->get_color() != Red){
						if(debug_flag) clog << "It is a black node. " << endl; 
						delete_case_1(node); 
					}
					else{
						if(debug_flag) clog << "It is a red node. " 
											<< "So it can simply be deleted" << endl; 
					}
					
					get_parent(node)->set_right_ptr(&NULL_NODE); 
				}
			
				cout << "Going to delete the leaf node. "<< endl; 
				delete node, --tree_size; 

				if(debug_flag) clog << "After deletion: \n", print_tree(); 
				
				return true; 
			} /* Leaf node. */
			else{
				/* Not a leaf node and do not have two children. 
				 * So it has exactly one child. 
				 */
				Node<int>* child = NULL; 

				if(node->get_left_ptr() != &NULL_NODE){
					if(debug_flag) clog << "Deleting a node with only a single left child. " << endl;
					child = node->get_left_ptr(); 

					if(is_left_child(node)){
						/*       
						 *       /
						 *      () <--left child of parent
						 *      /     and has only left child
						 *     ()
						 *     /\
						 *    /__\
						 */
						get_parent(node)->set_left_ptr(node->get_left_ptr()); 
						node->get_left_ptr()->set_parent(get_parent(node)); 
					}
					else if(is_right_child(node)){
						/*     
						 *     \
						 *     () <-- right child of parent 
						 *     /      and has only left child
						 *    ()
						 *    /\
						 *   /__\
						 */
						get_parent(node)->set_right_ptr(node->get_left_ptr()); 
						node->get_left_ptr()->set_parent(get_parent(node)); 
					}
					else{
						assert(is_root(node)); 
						/* 
						 *     () <-- root of tree and  
						 *     /      has only left child
						 *    ()
						 *    /\
						 *   /__\ 
						 */
						root = node->get_left_ptr(); 
						node->get_left_ptr()->set_parent(&NULL_NODE); 
					}
				}
				else{
					/* This node has only one sibling.
					 * This node has no left child. 
					 * So it needs to have right child. 
					 */
					assert(node->get_right_ptr() != &NULL_NODE); 
					if(debug_flag) clog << "Deleting a node with only a single right child. " << endl;
					child = node->get_right_ptr(); 

					if(is_left_child(node)){
						/* 
						 *      /
						 *     () <-- left child of parent
						 *      \     and has only right child. 
						 *      ()
						 *      /\
						 *     /__\
						 */
						get_parent(node)->set_left_ptr(node->get_right_ptr()); 
						node->get_right_ptr()->set_parent(get_parent(node)); 
					}
					else if(is_right_child(node)){
						/* 
						 *     \ 
						 *     () <-- right child of parent
						 *      \     and has only right child. 
						 *      ()
						 *      /\
						 *     /__\
						 */
						get_parent(node)->set_right_ptr(node->get_right_ptr()); 
						node->get_right_ptr()->set_parent(get_parent(node)); 
					}
					else{
						assert(is_root(node)); 
						/* 
						 *     () <-- root of tree and
						 *      \     has only one right child. 
						 *      ()
						 *      /\
						 *     /__\
						 */
						root = node->get_right_ptr(); 
						node->get_right_ptr()->set_parent(&NULL_NODE); 
					}
				}

				/* Now do the recoloring and rebalancing. */
				if(node->get_color() == Red){
					if(debug_flag) clog << "Color of node is Red. "
										<< "So nothing needs to be done. " 
										<< endl; 
					delete node, --tree_size; 
				}
				else{
					if(debug_flag) clog << "Color of node is black. " << endl; 
					if(child->get_color() == Red){
						/* The node has a red child. Just recolor it to black. */
						if(debug_flag) clog << "The child is red. " 
											<< "So just recolor it to black and you are done. " << endl; 
						child->set_color(Black); 						
						delete node, --tree_size; 
					}
					else{
						/* The node has a black child. 
							* Black node with a black child --> the complex case. 
							*/
						if(debug_flag) clog << "The child is black. "
											<< "The black node with a black child is the complex case. " 
											<< endl; 
						-- tree_size; /* Why decrement tree_size before deleting node? */
						delete_case_1(child); 
						delete node; 
					}
				}

				if(debug_flag) clog << "After deletion: \n", print_tree(); 
				return true; 

			} /* Else part of 'if(is_leaf(node)){...} */
		} /* Else part of if(has_two_children(node)){...} */
	}/* Else part of 'if(node == NULL){...} */
}

/**********************************************************************/
/* To get the inorder successor, given a pointer to that node. 
 * Returns NULL if not found. 
 */
Node<int>* Red_Black_Tree::get_inorder_successor(Node<int> *node){
	/* If the right subtree is not NULL: 
	 *       return the leftmost node of the right subtree. 
	 * else
	 *       Start from the root. 
	 *       Travel down the tree & save the curr node when moving left. 
	 *       When you find the node with 'value' return the saved node. 
	 */
	if((node == NULL) || (node == &NULL_NODE)){
		/* Node not found. Return NULL. */
		return NULL; 
	}
	else{
		/* Node is valid. */
		if(node->get_right_ptr() != &NULL_NODE){
			/* Right subtree not NULL. 
			 * So return the leftmost child of the right subtree. 
			 * Complexity: O(log n). 
			 */
			Node<int>* curr_node = node->get_right_ptr(); 
			while(curr_node->get_left_ptr() != &NULL_NODE){
				curr_node = curr_node->get_left_ptr(); 
			}
			return curr_node; 
		}
		else{
			/* Right subtree is NULL. 
			 * Start from root. Move down the tree. 
			 * Save node when moving left. 
			 * Inorder successor can be NULL. 
			 * Complexity: O(log n). 
			 */ 
			Node<int>* succ_node = NULL; 
			Node<int>* curr_node = get_root(); 
			while(curr_node != &NULL_NODE){
				if(node->get_data() < curr_node->get_data()){
					/* Moving to the left subtree. 
					 * Save the current node; it may be the answer. 
					 */
					succ_node = curr_node; 
					curr_node = curr_node->get_left_ptr(); 
				}
				else if(node->get_data() > curr_node->get_data()){
					/* Moving to the right subtree. */
					curr_node = curr_node->get_right_ptr(); 
				}
				else{
					break; /* Found the node. */
				}
			}
			return succ_node; 
		}/* Right subtree is NULL. */
	}/* Node found. */
}

/**********************************************************************/
/* To get the inorder successor of a node given its value.  
 * Returns NULL if not found. 
 */
Node<int>* Red_Black_Tree::get_inorder_successor(int value){
	Node<int>* node_ptr = search(value);	/* Complexity: O(log n). */
	return get_inorder_successor(node_ptr); /* Complexity: O(log n). */
}

/**********************************************************************/
/* Finding inorder predecessor, given a pointer to a node. */
Node<int>* Red_Black_Tree::get_inorder_predecessor(Node<int> *node){
	/* If the left subtree is not NULL: 
	 *       return the rightmost node of the left subtree. 
	 * else
	 *       Start from the root. 
	 *       Travel down the tree & save the curr node when moving right. 
	 *       When you find the node with 'value' return the saved node. 
	 */
	if(node == NULL) return NULL; 
	else{
		/* Node is valid. */
		if(node->get_left_ptr() != &NULL_NODE){
			/* Left subtree not NULL. 
			 * So return the rightmost child of the left subtree. 
			 * Complexity: O(log n). 
			 */
			Node<int>* curr_node = node->get_left_ptr(); 
			while(curr_node->get_right_ptr() != &NULL_NODE){
				curr_node = curr_node->get_right_ptr(); 
			}
			return curr_node; 
		}
		else{
			/* Left subtree is NULL. 
			 * Start from root. Move down the tree. 
			 * Save node when moving right. 
			 * Inorder successor can be NULL. 
			 * Complexity: O(log n). 
			 */ 
			Node<int>* succ_node = NULL; 
			Node<int>* curr_node = get_root(); 
			while(curr_node != &NULL_NODE){
				if(node->get_data() < curr_node->get_data()){
					/* Moving to the left subtree. */
					curr_node = curr_node->get_left_ptr(); 
				}
				else if(node->get_data() > curr_node->get_data()){
					/* Moving to the right subtree. 
					 * Save the current node; it may be the answer. 
					 */
					succ_node = curr_node; 
					curr_node = curr_node->get_right_ptr(); 
				}
				else{
					break; /* Found the node. */
				}
			}
			return succ_node; 
		}/* Left subtree is NULL. */
	}/* NULL node. */
}

/**********************************************************************/
/* Finding inorder-predecessor, given value of a node. */
Node<int>* Red_Black_Tree::get_inorder_predecessor(int value){
	Node<int>* node_ptr = search(value);	  /* Complexity: O(log n). */
	return get_inorder_predecessor(node_ptr); /* Complexity: O(log n). */
}

/**********************************************************************/

