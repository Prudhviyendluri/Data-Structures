/**************************** Red_Black_Tree.h ****************************/
#ifndef __RED_BLACK_TREE_H__
#define __RED_BLACK_TREE_H__

/********************************************************************/
#include "Node.h"
#include "helper.h"
#include <iostream>

using std::cout   ; 
using std::ostream; 

/********************************************************************/
class Red_Black_Tree{
private: 
	Node<int>   NULL_NODE	;
	Node<int>	*root		; 
	size_t		tree_size	; 
	bool		debug_flag	; 
	static bool deletion_flag; 

	/****** Utility functions. ******/
	/* To get the parent of a node. */
	Node<int>* get_parent(Node<int>* node); 
	Node<int>* get_parent(int value); 

	/* To check whether a node is a left child or right child 
	 * of its parent. For root node, it returns false. 
	 */
	bool is_left_child (Node<int>* node); 
	bool is_right_child(Node<int>* node); 
	bool is_left_child (int value); 
	bool is_right_child(int value); 

	/* To check whether a given node is a root node. */
	bool is_root(Node<int>* node); 
	bool is_root(int value); 

	/* To check whether a given node is a leaf node. */
	bool is_leaf(Node<int>* node); 
	bool is_leaf(int value); 

	/* To check whether a node has only one child. */
	bool has_only_one_child(Node<int>* node); 
	bool has_only_one_child(int value); 

	/* To check whether a node has two children. */
	bool has_two_children(Node<int>* node); 
	bool has_two_children(int value); 

	/* Rotation. */
	void left_rotation(Node<int> *node); 
	void right_rotation(Node<int> *node); 
	
	/* Finding inorder successors. */
	Node<int>* get_inorder_successor(Node<int> *node);
	Node<int>* get_inorder_successor(int value);

	/* Finding inorder predecessor. */
	Node<int>* get_inorder_predecessor(Node<int> *node);
	Node<int>* get_inorder_predecessor(int value);

	/* To get the grandparent, uncle, and sibling. */
	Node<int>* get_grandparent(Node<int> *node); 
	Node<int>* get_uncle      (Node<int> *node); 
	Node<int>* get_sibling    (Node<int> *node); 

	/* Various functions related to insertion. */
	void insert_case_1(Node<int>* node); 
	void insert_case_2(Node<int>* node); 
	void insert_case_3(Node<int>* node); 
	void insert_case_4(Node<int>* node); 
	void insert_case_5(Node<int>* node); 

	/* Various functions related to deletion. */
	void delete_case_1   (Node<int> *node); 
	void delete_case_2   (Node<int> *node); 
	void delete_case_3   (Node<int> *node); 
	void delete_case_4   (Node<int> *node); 
	void delete_case_5   (Node<int> *node); 
	void delete_case_6   (Node<int> *node); 

	/* Rebalancing functions. */
	void recolor_and_rebalance_insert(Node<int> *node); 
	void recolor_and_rebalance_delete(Node<int> *node); 

public: 
	/* Constructor / Destructor. */
	Red_Black_Tree() : NULL_NODE(), root(&NULL_NODE), tree_size(0), debug_flag(false){
		NULL_NODE.set_color    (Black     ); 
		NULL_NODE.set_left_ptr (&NULL_NODE); /* Self referencing. */
		NULL_NODE.set_right_ptr(&NULL_NODE); /* Self referencing. */
		NULL_NODE.set_parent   (&NULL_NODE); /* Self referencing. */
	}
	~Red_Black_Tree(){ clear(); }

	/* Insert a new item to the tree. */
	void insert(int x); 

	/* To delete a node with a specific value. */
	bool delete_node(int value); 
	bool delete_node(Node<int>* node);  

	/* To get the height of a particular node. 
	 * Complexity: O(n) where n is the number of elements in the 
	 *                  subtree with 'node' as the root. 
	 */ 
	int get_height(Node<int> *node) const; 

	/* To get the height of the entire tree. 
	 * Complexity: O(n). 
	 */
	int get_height() const; 

	/* Traverse the tree. */
	void inorder   (Node<int> *node_ptr, ostream& out = cout) const ; 
	void preorder  (Node<int> *node_ptr, ostream& out = cout) const ; 
	void postorder (Node<int> *node_ptr, ostream& out = cout) const ; 
	void levelorder(Node<int> *node_ptr, ostream& out = cout) const ; 

	/* Traverse the tree; always from the root. */
	void inorder   (ostream& out = cout) const ; 
	void preorder  (ostream& out = cout) const ; 
	void postorder (ostream& out = cout) const ; 
	void levelorder(ostream& out = cout) const ; 

	/* To get/set the root of the tree. */
	Node<int>* get_root() const         { return root; } 
	void       set_root(Node<int>* node){ root = node; } 

	/* To know the number of nodes in the tree. */
	size_t size() const { return tree_size; }

	/* To check whether the tree is empty. */
	bool empty() const { return (tree_size == 0); }

	/* To print the tree. */
	void print_tree(ostream &out = cout) const; 

	/* To search for a key. */
	Node<int>* search(int value);
	
	/* Clear the tree. */
	void clear(); 
	void clear(Node<int>* node); 
		
	/* Set/unset debug flag. */
	void set_debug_flag  (){ debug_flag = true;  }
	void unset_debug_flag(){ debug_flag = false; }

}; 

#endif
/********************************************************************/
