/**************************** AVL_Tree.cpp ****************************/
#include "AVL_Tree.h"
#include <iostream>
#include <string> 
#include <queue> 
#include <vector> 
#include <iomanip>

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

/**********************************************************************/
/* Static data of the tree class. */
bool AVL_Tree::deletion_flag = false; 

/**********************************************************************/
/* Insert a new item to the tree. */
void AVL_Tree::insert(int x){
	if(tree_size == 0){
		/* Inserting the first node. 
		 * The parent of root node is NULL. 
		 */
		Node<int> *node = new Node<int>(x); 
		root = node; 
		++tree_size; 
	}
	else{
		/* Tree not empty. */
		Node<int> *node = new Node<int>(x); 
		Node<int> *temp = root; 
		while(1){
			if(temp->get_data() > x){
				/* Traverse the left sub-tree. */
				if(temp->get_left_ptr() == NULL){
					/* Left sub-tree is empty. Inserting the node. */
					temp->set_left_ptr(node); 
					node->set_parent(temp); 
					++ tree_size; 
					
					/* Rebalancing. */
					update_height_after_insert(node); 
					rebalance_insert(node);
					
					break; 
				}
				else{
					/* Left sub-tree not null. */
					temp = temp->get_left_ptr(); 
				}
			}
			else if(temp->get_data() < x){
				/* Traverse the right sub-tree. */
				if(temp->get_right_ptr() == NULL){
					/* Right sub-tree is empty. Inserting the node. */
					temp->set_right_ptr(node); 
					node->set_parent(temp); 
					++ tree_size; 

					/* Rebalancing. */
					update_height_after_insert(node); 
					rebalance_insert(node);

					break; 
				}
				else{
					/* Right sub-tree not null. */
					temp = temp->get_right_ptr(); 
				}
			}
			else{
				/* Data already present in the tree. */
				return; 
			}
		} /* while(1){ ... } */

	} /* Tree not empty. */

	/* In debug mode, print the tree after insertion. */
	if(debug_flag) print_tree(); 

	return; 
}

/**********************************************************************/
/* Search for a key. 
 * Returns NULL if not found and pointer to node otherwise. 
 */
Node<int>* AVL_Tree::search(int value){
	Node<int> *curr_node = get_root(); 
	while(curr_node != NULL){ 
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
Node<int>* AVL_Tree::get_parent(Node<int>* node){
	if(node == NULL) return NULL; 
	return node->get_parent(); 
}

/* To get the parent node, given the value of the node */
Node<int>* AVL_Tree::get_parent(int value){
	Node<int>* node = search(value); 
	return get_parent(node); 
}

/**********************************************************************/
/* To check whether the node is the left child of its parent,  
 * given a pointer to a node. 
 */
bool AVL_Tree::is_left_child(Node<int>* node){
	if(node == NULL) return false; 
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
bool AVL_Tree::is_left_child(int value){
	Node<int>* node = search(value); 
	return is_left_child(node); 
}

/**********************************************************************/
/* To check whether the node is the right child of its parent; 
 * given a pointer to a node. 
 */
bool AVL_Tree::is_right_child(Node<int>* node){
	if(node == NULL) return false; 
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
bool AVL_Tree::is_right_child(int value){
	Node<int>* node = search(value); 
	return is_right_child(node); 
}

/**********************************************************************/
/* To check whether a given node is a root node; 
 * given a pointer to a node. 
 */
bool AVL_Tree::is_root(Node<int>* node){
	if(node == NULL) return false; 
	return (get_root() == node); 
}

/* To check whether a given node is a root node; 
 * given the value of the node. 
 */
bool AVL_Tree::is_root(int value){
	return (get_root()->get_data() == value); 
}

/**********************************************************************/
/* To check whether a given node is a leaf node; 
 * given a pointer to a node. 
 */
bool AVL_Tree::is_leaf(Node<int>* node){
	if(node == NULL) return false; 
	return (
		(node->get_left_ptr () == NULL) && 
		(node->get_right_ptr() == NULL)
	); 
}

/* To check whether a given node is a leaf node, 
 * given value of a node. 
 */
bool AVL_Tree::is_leaf(int value){
	Node<int>* node = search(value); 
	return is_leaf(node); 
}

/**********************************************************************/
/* To check whether a node has two children, given a pointer to the 
 * node. 
 */
bool AVL_Tree::has_two_siblings(Node<int>* node){
	if(node == NULL) return false; 
	return (
		(node->get_left_ptr () != NULL) &&
		(node->get_right_ptr() != NULL)
	); 
}

/* To check whether a node has two children, given value of a node. */
bool AVL_Tree::has_two_siblings(int value){
	Node<int>* node = search(value); 
	return has_two_siblings(node); 
}

/**********************************************************************/
/* To check whether a node has only one child, given a pointer to the 
 * node. 
 */
bool AVL_Tree::has_only_one_sibling(Node<int>* node){
	if(node == NULL) return false; 
	return (
		(
			(node->get_left_ptr () != NULL) &&
			(node->get_right_ptr() == NULL)
		) ||
		(
			(node->get_left_ptr () == NULL) &&
			(node->get_right_ptr() != NULL)
		)
	); 
}

/**********************************************************************/
/* To check whether a node has only one child, given value of a node. */
bool AVL_Tree::has_only_one_sibling(int value){
	Node<int>* node = search(value); 
	return has_only_one_sibling(node); 
}

/**********************************************************************/
/* To clear the tree given a pointer to a specific node. 
 * Complexity: O(n)
 */
void AVL_Tree::clear(Node<int>* node){
	if(node == NULL) return; 
	else{
		/* Recursive calls. */
		clear(node->get_left_ptr()); 
		clear(node->get_right_ptr()); 
		
		if(! is_root(node)){
			if(is_left_child(node)){
				get_parent(node)->set_left_ptr(NULL); 
			}
			else if(is_right_child(node)){
				get_parent(node)->set_right_ptr(NULL); 
			}
		}
		else{
			root = NULL; 
		}

		delete node; 
		--tree_size; 
	}
}

/**********************************************************************/
/* To clear the entire tree. 
 * Complexity: O(n)
 */ 
void AVL_Tree::clear(){
	clear(get_root()); 
	root = NULL; 
	return; 
}

/**********************************************************************/
/* To update the height. */
void AVL_Tree::update_height_after_insert(Node<int> *node){
	if(node == NULL) return;
	else if(node == root) return; 
	else{
		Node<int>* temp_node_ptr = node->get_parent(); 
		size_t temp_height = 0; 
		while((temp_node_ptr != NULL) && (temp_node_ptr->get_height() <= temp_height)){
			temp_node_ptr->set_height(temp_height + 1); 
			temp_height = temp_height + 1; 
			temp_node_ptr = temp_node_ptr->get_parent(); 
		}
	}
}

/**********************************************************************/
void AVL_Tree::update_height_after_delete(Node<int>* node){
	//if(node == NULL) cout << "NULL" << endl; 
	if(node == NULL) return; 
	int h_left = 0, h_right = 0; 
	bool change_flag = true; 
	Node<int> *temp_node_ptr = node; 
	int prev_h = 0; 
	while(temp_node_ptr != NULL){
		prev_h  = temp_node_ptr->get_height(); 
		h_left  = ((temp_node_ptr->get_left_ptr () == NULL) ? -1 : temp_node_ptr->get_left_ptr() ->get_height()); 
		h_right = ((temp_node_ptr->get_right_ptr() == NULL) ? -1 : temp_node_ptr->get_right_ptr()->get_height()); 
		(h_left > h_right) ? temp_node_ptr->set_height(h_left + 1) : temp_node_ptr->set_height(h_right + 1); 
		
		if(
			(prev_h == temp_node_ptr->get_height()) 
		){
			break; 
		}

		/* Moving up the tree. */
		temp_node_ptr = temp_node_ptr->get_parent(); 
	}
}

/**********************************************************************/
/* To traverse the tree 'inorder'. 
 * Uses node_ptr as the root of the tree. 
 */
void AVL_Tree::inorder(Node<int> *node_ptr, ostream& out) const {
	if(node_ptr == NULL){
		return; 
	}
	else{
		inorder(node_ptr->get_left_ptr(), out); 
		out << node_ptr->get_data() << "[" << node_ptr->get_height() << "] "; 
		inorder(node_ptr->get_right_ptr(), out); 
	}
	return; 
}

/**********************************************************************/
/* To traverse the tree 'inorder'. 
 * Always starts from the root. 
 */
void AVL_Tree::inorder(ostream& out) const {
	inorder(get_root(), out); 
	out << endl; 
	return; 
}

/**********************************************************************/
void AVL_Tree::left_rotation(Node<int> *node){
	//cout << "inside left_rotation with node = " << node->get_data() << endl; 
	Node<int> *root = node; 
	if(root == NULL) return; 

	Node<int> *pivot = root->get_right_ptr(); 
	if(pivot == NULL) return; 

	if(debug_flag) clog << "root: " << root->get_data() << ", " 
						<< "pivot: " << pivot->get_data() << endl; 

	root->set_right_ptr(pivot->get_left_ptr()); 
	if(root->get_right_ptr() != NULL) root->get_right_ptr()->set_parent(root); 
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

	//cout << "Before updating height: ", inorder(); 

	/* Updating the heights. */
	int h_left = 0, h_right = 0; 
	bool change_flag = true; 
	Node<int> *temp_node_ptr = root; 
	//cout << "Starting to update height from " << temp_node_ptr->get_data() << endl; 
	int prev_h = 0; 
	while(temp_node_ptr != NULL){
		//cout << "temp_node_ptr: " << temp_node_ptr->get_data() << endl; 
		prev_h  = temp_node_ptr->get_height(); 
		h_left  = ((temp_node_ptr->get_left_ptr () == NULL) ? -1 : temp_node_ptr->get_left_ptr() ->get_height()); 
		h_right = ((temp_node_ptr->get_right_ptr() == NULL) ? -1 : temp_node_ptr->get_right_ptr()->get_height()); 
		(h_left > h_right) ? temp_node_ptr->set_height(h_left + 1) : temp_node_ptr->set_height(h_right + 1); 
		//cout << "After process: ", inorder(); 
		if(
			(prev_h == temp_node_ptr->get_height()) && 
			((temp_node_ptr != root) && (temp_node_ptr != pivot))
		){
			break; 
		}

		/* Moving up the tree. */
		temp_node_ptr = temp_node_ptr->get_parent(); 
	}
	
	//cout << "After left rotation, tree is: ", inorder(); 
	return; 
}

/**********************************************************************/
void AVL_Tree::right_rotation(Node<int> *node){
	//cout << "Inside right_rotation" << endl; 
	Node<int> *root = node; 
	if(root == NULL) return; 
	
	Node<int> *pivot = root->get_left_ptr(); 
	if(pivot == NULL) return; 

	if(debug_flag) clog << "root: " << root->get_data() << ", " 
						<< "pivot: " << pivot->get_data() << endl; 

	root->set_left_ptr(pivot->get_right_ptr()); 
	if(pivot->get_right_ptr() != NULL) pivot->get_right_ptr()->set_parent(root); 
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

	/* Updating the heights. */
	int h_left = 0, h_right = 0; 
	bool change_flag = true; 
	Node<int> *temp_node_ptr = root; 
	int prev_h = 0; 
	while(temp_node_ptr != NULL){
		prev_h  = temp_node_ptr->get_height(); 
		h_left  = ((temp_node_ptr->get_left_ptr () == NULL) ? -1 : temp_node_ptr->get_left_ptr() ->get_height()); 
		h_right = ((temp_node_ptr->get_right_ptr() == NULL) ? -1 : temp_node_ptr->get_right_ptr()->get_height()); 
		(h_left > h_right) ? temp_node_ptr->set_height(h_left + 1) : temp_node_ptr->set_height(h_right + 1); 
		
		if(
			(prev_h == temp_node_ptr->get_height()) && 
			((temp_node_ptr != root) && (temp_node_ptr != pivot))
		){
			break; 
		}

		/* Moving up the tree. */
		temp_node_ptr = temp_node_ptr->get_parent(); 
	}
	
	//cout << "After right rotation, tree is: ", inorder(); 

	return; 
}

/**********************************************************************/
int AVL_Tree::balance_factor(Node<int>* node){
	assert(node != NULL); 
	int left_bf = 0, right_bf = 0; 

	if(node->get_right_ptr() == NULL) right_bf = 0; 
	else right_bf = node->get_right_ptr()->get_height() + 1; 

	if(node->get_left_ptr() == NULL) left_bf = 0; 
	else left_bf = node->get_left_ptr()->get_height() + 1; 

	return (right_bf - left_bf); 
}

/**********************************************************************/
void AVL_Tree::rebalance_insert(Node<int> *node){
	if(debug_flag) clog << "Before rebalancing: \n", print_tree(); 

	if(node == NULL) return; 
	string curr_direction, prev_direction; 
	Node<int> *temp_node = node->get_parent(); 
	int curr_bf = 0;

	if(is_left_child(node)) curr_direction = "L"; 
	else if(is_right_child(node)) curr_direction = "R"; 
	else curr_direction = ""; 

	while(temp_node != NULL){
		curr_bf = balance_factor(temp_node); 
		if(debug_flag)
			clog << "BF(" << temp_node->get_data() 
			     << "): " << curr_bf << endl; 
		if(curr_bf == 0){
			//cout << "bf = 0 at node " << node->get_data() << endl; 
			if(debug_flag) clog << "Rebalance complete. " << endl; 
			break; 
		}
		else if((curr_bf <= 1) && (curr_bf >= -1)){
			/* Balance factor is within limit: -1, 0 or -1. 
			 * So we climb up the tree. 
			 * But before climbing up the tree, save the direction. 
			 * The direction is important to decide which of the four
			 * cases to be used for rotation. 
			 */
			//cout << "BF within limits" << endl; 
			prev_direction = curr_direction; 
			if(is_left_child(temp_node)) curr_direction = "L"; 
			else if(is_right_child(temp_node)) curr_direction = "R"; 
			else if(is_root(temp_node)){
				break; 
			}
			else{
				cout << "Error: Not left, right or parent" << endl; 
				assert(0); 
			}

			//cout << "curr_direction: " << curr_direction << endl;
			//cout << "prev_direction: " << prev_direction << endl; 
			
			temp_node = temp_node->get_parent(); 
		}
		else{
			/* Balance factor is not within the limits. 
			 * Find out which of the four cases to be used and
			 * rebalance the tree. 
			 */
			if(debug_flag) clog << "BF not withing limits. " << endl; 
			if((curr_direction == "L")&&(prev_direction == "R")){
				/* Left-Right case. 
				 * Do a left rotation, followed by a right rotation. 
				 */
				if(debug_flag){
					clog << "LR case. " << endl; 
					clog << "Doing left-rotation on " << temp_node->get_left_ptr()->get_data() << endl; 
				}
				left_rotation(temp_node->get_left_ptr()); 
				if(debug_flag) print_tree(); 

				if(debug_flag) clog << "Doing right-rotation on " << temp_node->get_data() << endl; 
				right_rotation(temp_node); 
				if(debug_flag) print_tree(); 

				/* Moving up. */
				temp_node = temp_node->get_parent(); 
			}
			else if((curr_direction == "R")&&(prev_direction == "L")){
				/* Right-Left case. 
				 * Do a right rotation, followed by a left rotation. 
				 */
				if(debug_flag){
					clog << "RL case" << endl; 
					clog << "Doing right-rotation on " << temp_node->get_right_ptr()->get_data() << endl; 
				}
				right_rotation(temp_node->get_right_ptr()); 

				if(debug_flag) clog << "Doing a left-rotation on " << temp_node->get_data() << endl; 
				left_rotation(temp_node); 
				if(debug_flag) print_tree(); 

				/* Moving up. */
				temp_node = temp_node->get_parent(); 
			}
			else if((curr_direction == "L")&&(prev_direction == "L")){
				/* Left-Left case. 
				 * Do a single right rotation. 
				 */
				if(debug_flag){
					clog << "LL case" << endl; 
					clog << "Doing right_rotation on " << temp_node->get_data() << endl; 
				}
				right_rotation(temp_node); 
				if(debug_flag) print_tree(); 

				/* Moving up. */
				temp_node = temp_node->get_parent(); 
			}
			else if((curr_direction == "R")&&(prev_direction == "R")){
				/* Right-Right case. 
				 * Do a single left rotation. 
				 */
				if(debug_flag){ 
					clog << "RR case" << endl; 
					clog << "Doing left-rotation on " << temp_node->get_data() << endl; 
				}
				left_rotation(temp_node); 
				if(debug_flag) print_tree(); 

				/* Moving up. */
				temp_node = temp_node->get_parent(); 
			}
			else{
				cerr << "None of the cases matched" << endl; 
				assert(false); 
			}
		}
	}

	return; 
}

/**********************************************************************/
void AVL_Tree::rebalance_delete(Node<int> *node){
	if(node == NULL) return; 

	/* If you have done a rebalance one, then you have to move up the 
	 * tree till root even if you get a BF of 0 at some node along 
	 * the path. 
	 */
	bool rebalance_done_flag = false; 
	Node<int>* temp_node_ptr = node; 
	int temp_bf = 0; 

	while(temp_node_ptr != NULL){
		if(debug_flag){
			clog << "Rebalancing from node " 
				 << temp_node_ptr->get_data() << endl; 
		}
		temp_bf = balance_factor(temp_node_ptr); 

		if(debug_flag){
			clog << "BF(" << temp_node_ptr->get_data() 
				 << "): " << temp_bf 
				 << endl; 
		}

		if((temp_bf <= 1) && (temp_bf >= -1)){
			/* Balance factor within limits. */
			if((temp_bf == 0) && (rebalance_done_flag == false)){
				break; 
			}
		}
		else{
			/* Balance factor not within limits. 
			 * Find which of the 4 cases: RR, RL, LR, LL. 
			 */
			string rotation_case; 
			if(temp_bf > 1){
				/* Either RR or RL. 
				 * Moving to the right child. 
				 */
				Node<int> *temp_node_ptr_2 = temp_node_ptr->get_right_ptr(); 
				if(balance_factor(temp_node_ptr_2) >= 0){
					rotation_case = "RR"; 
				}
				else{
					rotation_case = "RL"; 
				}
			}
			else{
				/* Either LL or LR. 
				 * Moving to the left child. 
				 */
				Node<int> *temp_node_ptr_2 = temp_node_ptr->get_left_ptr(); 
				if(balance_factor(temp_node_ptr_2) > 0){
					rotation_case = "LR"; 
				}
				else{
					rotation_case = "LL"; 
				}
			}
			
			if(debug_flag) clog << "Rotation case: " << rotation_case << endl; 

			if(rotation_case == "LL"){
				/* Do a single right rotation. */
				if(debug_flag) clog << "Doing right-rotation on " << temp_node_ptr->get_data() << endl; 
				right_rotation(temp_node_ptr); 
				if(debug_flag) print_tree(); 
				
			}
			else if(rotation_case == "LR"){
				/* Do a left-rotation, followed by right-rotation. */
				if(debug_flag) clog << "Doing left-rotation on " 
									<< temp_node_ptr->get_left_ptr()->get_data() << endl; 
				left_rotation(temp_node_ptr->get_left_ptr()); 
				if(debug_flag) print_tree(); 

				if(debug_flag) clog << "Doing right-rotation on " << temp_node_ptr->get_data() << endl; 
				right_rotation(temp_node_ptr); 
				if(debug_flag) print_tree(); 
			}
			else if(rotation_case == "RL"){
				/* Do a right-rotation, followed by left-rotation. */
				if(debug_flag) clog << "Doing right-rotation on " 
									<< temp_node_ptr->get_right_ptr()->get_data() << endl; 
				right_rotation(temp_node_ptr->get_right_ptr()); 
				if(debug_flag) print_tree(); 

				if(debug_flag) clog << "Doing left-rotation on " << temp_node_ptr->get_data() << endl; 
				left_rotation(temp_node_ptr); 
				if(debug_flag) print_tree(); 
			}
			else{
				/* RR case. Do a single left rotation. */
				if(debug_flag) clog << "Doing left-rotation on " << temp_node_ptr->get_data() << endl; 
				left_rotation(temp_node_ptr); 
				if(debug_flag) print_tree(); 
			}

			/* Set the rebalance done flag. */
			rebalance_done_flag = true; 
		}

		/* Move up the tree. */
		temp_node_ptr = temp_node_ptr->get_parent(); 
	}

	return; 
}

/**********************************************************************/
/* To print the tree. */
void AVL_Tree::print_tree(ostream& out) const {
	//out << "size of tree: " << size() << endl; 
	if(size() == 0) return; 

	size_t temp_counter = 0; 
	queue<Node<int>*> temp_q; 
	vector<Node<int>*> temp_v; 
	Node<int> *curr_node_ptr = NULL; 
	temp_q.push(root), temp_counter += 1; 
	vector<size_t> lr_node_count; 
	size_t max_nodes = (size_t)pow(2.0, root->get_height() + 1.0) - 1; 
	//out << "max_nodes: " << max_nodes << endl; 
	while(temp_counter <= max_nodes){
		curr_node_ptr = temp_q.front(), temp_q.pop(); 
		temp_v.push_back(curr_node_ptr); 
		++ temp_counter; 

		if(curr_node_ptr != NULL){
			if(curr_node_ptr->get_left_ptr() != NULL)
				temp_q.push(curr_node_ptr->get_left_ptr()); 
			else temp_q.push(NULL); 
			
			if(curr_node_ptr->get_right_ptr() != NULL)
				temp_q.push(curr_node_ptr->get_right_ptr()); 
			else temp_q.push(NULL); 
		}
		else{
			temp_q.push(NULL), temp_q.push(NULL); 
		}
	}

	//for(vector<Node<int>*>::iterator i = temp_v.begin(); i != temp_v.end(); i++){
	//	if((*i) == NULL) out << "NULL "; 
	//	else out << (*i)->get_data() << " "; 
	//}
	//out << endl; 
	
	size_t h = root->get_height(); 

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
				out << temp_v[counter]->get_data() << ","
					<< temp_v[counter]->get_height(); 

				if(temp_v[counter]->get_left_ptr() != NULL)
					lr_node_count.push_back(1); 
				else
					lr_node_count.push_back(0); 

				if(temp_v[counter]->get_right_ptr() != NULL)
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
				out << ((lr_node_count[k*2] == 1) ? "/" : " "); 
				
				/* Spaces between left and right arrows. */
				for(size_t l = 0; l < 3+count_2; l++) out << ' '; 

				/* Right arrow. */
				out << ((lr_node_count[k*2+1] == 1) ? "\\" : " "); 

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
bool AVL_Tree::delete_node(int value){
	Node<int>* node = search(value); 
	return delete_node(node); 
}

/**********************************************************************/
/* To delete a node when a pointer to it is available. 
 * Returns true on success and false on failure. 
 */
bool AVL_Tree::delete_node(Node<int>* node){
	if(debug_flag) clog << "Deleting node " << node->get_data() << endl; 
	if(node == NULL){
		return false; 
	}
	else{
		/* Check if leaf node. */
		if(is_leaf(node)){
			/* It is a leaf node. So just delete it. 
			 * Set the pointer of the parent node to this node
			 * appropriately. To do that, we need to know whether 
			 * this node is a left child of the parent or a 
			 * right child of the parent. 
			 */
			if(debug_flag) clog << "Deleting a leaf node" << endl; 
			Node<int>* temp_parent_ptr = node->get_parent(); 
			
			if(is_root(node)){
				/* It is a root and this is the only node in this tree. */
				if(debug_flag) clog << "Deleting root node" << endl; 
				root = NULL; 
			}
			else if(is_left_child(node)){
				get_parent(node)->set_left_ptr(NULL); 
			}
			else{
				assert(is_right_child(node)); 
				get_parent(node)->set_right_ptr(NULL); 
			}
			
			delete node; 
			--tree_size; 

			/* Rebalancing after deletion. */
			update_height_after_delete(temp_parent_ptr); 
			if(debug_flag) clog << "After height updation: \n", print_tree(); 
			rebalance_delete(temp_parent_ptr); 
			if(debug_flag) clog << "After deletion: \n", print_tree(); 

			return true; 
		} /* is_leaf(node){ ... } */
		else{
			/* Not a leaf node. */
			/* Check if it has only one child. */
			if(has_only_one_sibling(node)){
				/* Save the pointer to parent first. 
				 * Required while rebalancing. 
				 */
				Node<int>* temp_parent_ptr = node->get_parent(); 

				if(node->get_left_ptr() != NULL){
					if(debug_flag) clog << "Deleting a node with only a single left child. " << endl;

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
						node->get_left_ptr()->set_parent(NULL); 
					}
					delete node; 
					--tree_size; 

					/* Rebalancing after deletion. */
					update_height_after_delete(temp_parent_ptr); 
					if(debug_flag) clog << "After height updation: \n", print_tree(); 
					rebalance_delete(temp_parent_ptr); 
					if(debug_flag) clog << "After deletion: \n", print_tree(); 
					
					return true; 
				}
				else{
					/* This node has only one sibling.
					 * This node has no left child. 
					 * So it needs to have right child. 
					 */
					assert(node->get_right_ptr() != NULL); 
					if(debug_flag) clog << "Deleting a node with only a single right child. " << endl;

					/* Save the pointer to parent first. 
					 * Required while rebalancing. 
					 */
					Node<int>* temp_parent_ptr = node->get_parent(); 

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
						node->get_right_ptr()->set_parent(NULL); 
					}
					delete node, --tree_size; 

					/* Rebalancing after deletion. */
					update_height_after_delete(temp_parent_ptr); 
					if(debug_flag) clog << "After height updation: \n", print_tree(); 
					rebalance_delete(temp_parent_ptr); 
					if(debug_flag) clog << "After deletion: \n", print_tree(); 

					return true; 
				}
			}
			else{
				/* Has two siblings. 
				 * So either you have to find the inorder successor 
				 * or you have to find the inorder predecessor. 
				 * Always using inorder successor or inorder predecessor results
				 * in unbalanced tree. So alternate between them. 
				 */
				assert(has_two_siblings(node)); 
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
				node->set_data(temp);  /* Assign the data to node. */
								
				if(debug_flag){
					clog << "After deletion: \n", print_tree(); 
				}
				
				return true; 
			}
		}/* Not a leaf node. */
	}/* Node do not point to NULL. */
}

/**********************************************************************/
/* To get the inorder successor, given a pointer to that node. 
 * Returns NULL if not found. 
 */
Node<int>* AVL_Tree::get_inorder_successor(Node<int> *node){
	/* If the right subtree is not NULL: 
	 *       return the leftmost node of the right subtree. 
	 * else
	 *       Start from the root. 
	 *       Travel down the tree & save the curr node when moving left. 
	 *       When you find the node with 'value' return the saved node. 
	 */
	if(node == NULL){
		/* Node not found. Return NULL. */
		return NULL; 
	}
	else{
		/* Node is valid. */
		if(node->get_right_ptr() != NULL){
			/* Right subtree not NULL. 
			 * So return the leftmost child of the right subtree. 
			 * Complexity: O(log n). 
			 */
			Node<int>* curr_node = node->get_right_ptr(); 
			while(curr_node->get_left_ptr() != NULL){
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
			while(curr_node != NULL){
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
Node<int>* AVL_Tree::get_inorder_successor(int value){
	Node<int>* node_ptr = search(value);	/* Complexity: O(log n). */
	return get_inorder_successor(node_ptr); /* Complexity: O(log n). */
}

/**********************************************************************/
/* Finding inorder predecessor, given a pointer to a node. */
Node<int>* AVL_Tree::get_inorder_predecessor(Node<int> *node){
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
		if(node->get_left_ptr() != NULL){
			/* Left subtree not NULL. 
			 * So return the rightmost child of the left subtree. 
			 * Complexity: O(log n). 
			 */
			Node<int>* curr_node = node->get_left_ptr(); 
			while(curr_node->get_right_ptr() != NULL){
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
			while(curr_node != NULL){
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
Node<int>* AVL_Tree::get_inorder_predecessor(int value){
	Node<int>* node_ptr = search(value);	  /* Complexity: O(log n). */
	return get_inorder_predecessor(node_ptr); /* Complexity: O(log n). */
}

/**********************************************************************/

