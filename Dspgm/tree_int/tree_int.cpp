/**************************** tree_int.cpp ****************************/
#include "tree_int.h"
#include <iostream>
#include <queue>

using std::ostream; 
using std::endl; 
using std::queue; 

/**********************************************************************/
/* Static data of the tree class. */
int Tree_Int::deletion_flag = 0; 

/**********************************************************************/
/* Insert new item to tree. */
void Tree_Int::insert(int x){
	if(tree_size == 0){
		/* Inserting the first node. */
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
		
		/* Increment the size of the tree. */
		++ tree_size; 

	} /* Tree not empty. */

	return; 
}

/**********************************************************************/
/* To traverse the tree 'inorder'. 
 * Uses node_ptr as the root of the tree. 
 */
void Tree_Int::inorder(Node<int> *node_ptr, ostream& out) const {
	if(node_ptr == NULL){
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
void Tree_Int::inorder(ostream& out) const {
	inorder(get_root(), out); 
	return; 
}

/**********************************************************************/
/* To traverse the tree 'preorder'. */
void Tree_Int::preorder(Node<int> *node_ptr, ostream& out) const {
	if(node_ptr == NULL){
		return; 
	}
	else{
		out << node_ptr->get_data() << " "; 
		preorder(node_ptr->get_left_ptr(), out); 
		preorder(node_ptr->get_right_ptr(), out); 
	}
	return; 
}

/**********************************************************************/
/* To traverse the tree 'preorder'. 
 * Always starts from the root. 
 */
void Tree_Int::preorder(ostream& out) const {
	preorder(get_root(), out); 
	return; 
}

/**********************************************************************/
/* To traverse the tree 'postorder'. */
void Tree_Int::postorder(Node<int> *node_ptr, ostream& out) const {
	if(node_ptr == NULL){
		return; 
	}
	else{
		postorder(node_ptr->get_left_ptr(), out); 
		postorder(node_ptr->get_right_ptr(), out); 
		out << node_ptr->get_data() << " "; 
	}
	return; 
}

/**********************************************************************/
/* To traverse the tree 'postorder'. 
 * Always starts from the root. 
 */
void Tree_Int::postorder(ostream& out) const {
	postorder(get_root(), out); 
	return; 
}

/**********************************************************************/
/* To traverse the tree in 'levelorder'. */
void Tree_Int::levelorder(Node<int> *node_ptr, ostream& out) const {
	if(node_ptr == NULL) return; 

	queue<Node<int>*> q; 
	Node<int>* next_node; 
	q.push(node_ptr); 
	while(! q.empty()){
		next_node = q.front(), q.pop(); 
		out << next_node->get_data() << " "; 
		if(next_node->get_left_ptr() != NULL)
			q.push(next_node->get_left_ptr()); 
		if(next_node->get_right_ptr() != NULL)
			q.push(next_node->get_right_ptr()); 
	}
	return; 
}

/**********************************************************************/
/* Levelorder traverse from the root. */
void Tree_Int::levelorder(ostream& out) const {
	levelorder(get_root(), out); 
	return; 
}

/**********************************************************************/
/* Search for a key. 
 * Returns NULL if not found. 
 * Returns pointer to node otherwise. 
 */
Node<int>* Tree_Int::search(int value){
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
/* To get the inorder successor, given a pointer to that node. 
 * Returns NULL if not found. 
 */
Node<int>* Tree_Int::get_inorder_successor(Node<int> *node){
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
Node<int>* Tree_Int::get_inorder_successor(int value){
	Node<int>* node_ptr = search(value);	/* Complexity: O(log n). */
	return get_inorder_successor(node_ptr); /* Complexity: O(log n). */
}

/**********************************************************************/
/* Finding inorder predecessor, given a pointer to a node. */
Node<int>* Tree_Int::get_inorder_predecessor(Node<int> *node){
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
Node<int>* Tree_Int::get_inorder_predecessor(int value){
	Node<int>* node_ptr = search(value);	  /* Complexity: O(log n). */
	return get_inorder_predecessor(node_ptr); /* Complexity: O(log n). */
}

/**********************************************************************/
/* To get the parent node, given a pointer to a node */
Node<int>* Tree_Int::get_parent(Node<int>* node){
	if(node == NULL) return NULL; 
	Node<int>* curr_node = get_root(), *prev_node = NULL; 
	while(curr_node != NULL){
		if(node->get_data() == curr_node->get_data()){
			return prev_node; 
		}
		else{
			prev_node = curr_node; 
			if(node->get_data() < curr_node->get_data())
				curr_node = curr_node->get_left_ptr(); 
			else if(node->get_data() > curr_node->get_data())
				curr_node = curr_node->get_right_ptr(); 
		}
	}
	return NULL; 
}

/**********************************************************************/
/* Get the parent node, given a value. */
Node<int>* Tree_Int::get_parent(int value){
	Node<int>* node = search(value); /* Complexity: O(log n). */
	return get_parent(node);		 /* Complexity: O(log n). */
}

/**********************************************************************/
/* To check whether the node is the left child of its parent,  
 * given a pointer to a node. 
 */
bool Tree_Int::is_left_child(Node<int>* node){
	if(node == NULL) return false; 
	if(is_root(node)){
		/* For root node, return false. */
		return false; 
	}
	else{
		return (get_parent(node)->get_left_ptr() == node); 
	}
}

/**********************************************************************/
/* To check whether the node is the left child of its parent; 
 * given the value of a node. 
 */
bool Tree_Int::is_left_child(int value){
	Node<int>* node = search(value); 
	return is_left_child(node); 
}

/**********************************************************************/
/* To check whether the node is the right child of its parent; 
 * given a pointer to a node. 
 */
bool Tree_Int::is_right_child(Node<int>* node){
	if(node == NULL) return false; 
	if(is_root(node)){
		/* For root node, return false. */
		return false; 
	}
	else{
		return (get_parent(node)->get_right_ptr() == node); 
	}
}

/**********************************************************************/
/* To check whether a given node is a root node; 
 * given a pointer to a node. 
 */
bool Tree_Int::is_root(Node<int>* node){
	if(node == NULL) return false; 
	return (get_root() == node); 
}

/**********************************************************************/
/* To check whether a given node is a root node; 
 * given the value of a node. 
 */
bool Tree_Int::is_root(int value){
	return (get_root()->get_data() == value); 
}

/**********************************************************************/
/* To check whether the node is the right child of its parent; 
 * given the value of a node. 
 */
bool Tree_Int::is_right_child(int value){
	Node<int>* node = search(value); 
	return is_right_child(node); 
}

/**********************************************************************/
/* To check whether a given node is a leaf node; 
 * given a pointer to a node. 
 */
bool Tree_Int::is_leaf(Node<int>* node){
	if(node == NULL) return false; 
	return (
		(node->get_left_ptr () == NULL) && 
		(node->get_right_ptr() == NULL)
	); 
}

/**********************************************************************/
/* To check whether a given node is a leaf node, 
 * given value of a node. 
 */
bool Tree_Int::is_leaf(int value){
	Node<int>* node = search(value); 
	return is_leaf(node); 
}

/**********************************************************************/
/* To check whether a node has two children, given a pointer to the 
 * node. 
 */
bool Tree_Int::has_two_siblings(Node<int>* node){
	if(node == NULL) return false; 
	return (
		(node->get_left_ptr () != NULL) &&
		(node->get_right_ptr() != NULL)
	); 
}

/**********************************************************************/
/* To check whether a node has two children, given value of a node. */
bool Tree_Int::has_two_siblings(int value){
	Node<int>* node = search(value); 
	return has_two_siblings(node); 
}

/**********************************************************************/
/* To check whether a node has only one child, given a pointer to the 
 * node. 
 */
bool Tree_Int::has_only_one_sibling(Node<int>* node){
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
bool Tree_Int::has_only_one_sibling(int value){
	Node<int>* node = search(value); 
	return has_only_one_sibling(node); 
}

/**********************************************************************/
/* To delete a node with a specific value. 
 * Returns true on success and false on failure. 
 */
bool Tree_Int::delete_node(int value){
	Node<int>* node = search(value); 
	return delete_node(node); 
}

/**********************************************************************/
/* To delete a node when a pointer to it is available. 
 * Returns true on success and false on failure. 
 */
bool Tree_Int::delete_node(Node<int>* node){
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
			if(is_root(node)){
				/* It is a root and this is the only node in this tree. */
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
			return true; 
		} /* is_leaf(node){ ... } */
		else{
			/* Not a leaf node. */
			/* Check if it has only one child. */
			if(has_only_one_sibling(node)){
				if(node->get_left_ptr() != NULL){
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
					}
					delete node; 
					--tree_size; 
					return true; 
				}
				else{
					/* This node has only one sibling.
					 * This node has no left child. 
					 * So it needs to have right child. 
					 */
					assert(node->get_right_ptr() != NULL); 
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
					}
					delete node; 
					--tree_size; 
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
				Node<int>* inorder_successor_or_inorder_predecessor = NULL; 
				if(deletion_flag == 0){
					deletion_flag = 1; 
					//cout << "Using inorder successor" << endl; 
					inorder_successor_or_inorder_predecessor = get_inorder_successor(node); 
				}
				else{
					deletion_flag = 0; 
					//cout << "Using Inorder predecessor" << endl; 
					inorder_successor_or_inorder_predecessor = get_inorder_predecessor(node); 
				}
				assert(inorder_successor_or_inorder_predecessor != NULL); 

				/* Save the data part of inorder_successor_or_inorder_predecessor node. */
				int temp = inorder_successor_or_inorder_predecessor->get_data(); 

				/* Now delete the inorder_successor_or_inorder_predecessor node. 
				 * This node will either be a leaf node or will have max one child. 
				 */
				delete_node(inorder_successor_or_inorder_predecessor); 
				node->set_data(temp);  /* Assign the data to node. */
				return false; 
			}
		}/* Not a leaf node. */
	}/* Node do not point to NULL. */
}

/**********************************************************************/
/* To clear the entire tree. 
 * Complexity: O(n)
 */ 
void Tree_Int::clear(){
	clear(get_root()); 
	root = NULL; 
	return; 
}

/**********************************************************************/
/* To clear the tree given a pointer to a specific node. 
 * Complexity: No. of elements in this tree. 
 */
void Tree_Int::clear(Node<int>* node){
	if(node == NULL) return; 
	else{
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

		delete node; 
		--tree_size; 
	}
}
/**********************************************************************/
