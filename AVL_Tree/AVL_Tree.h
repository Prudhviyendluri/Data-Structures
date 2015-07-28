/**************************** AVL_Tree.h ****************************/
#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

/********************************************************************/
#include "Node.h"
#include <iostream>

using std::cout; 
using std::ostream; 

/********************************************************************/
class AVL_Tree{
private: 
	Node<int>	*root		; 
	size_t		tree_size	; 
	bool		debug_flag	; 
	static bool deletion_flag; 

	/****** Utility functions. ******/
	/* To get the parent of a node. */
	Node<int>* AVL_Tree::get_parent(Node<int>* node); 
	Node<int>* AVL_Tree::get_parent(int value); 

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
	bool has_only_one_sibling(Node<int>* node); 
	bool has_only_one_sibling(int value); 

	/* To check whether a node has two children. */
	bool has_two_siblings(Node<int>* node); 
	bool has_two_siblings(int value); 

	/* To update the height after the insertion/deletion operations. */
	void update_height_after_insert(Node<int>* node); 
	void update_height_after_delete(Node<int>* node); 

	/* Rotation. */
	void left_rotation(Node<int> *node); 
	void right_rotation(Node<int> *node); 
	
	/* To get the balance factor at a node. */
	int balance_factor(Node<int>* node); 

	/* Rebalancing functions. */
	void rebalance_insert(Node<int> *node); 
	void rebalance_delete(Node<int> *node); 

	/* Finding inorder successors. */
	Node<int>* get_inorder_successor(Node<int> *node);
	Node<int>* get_inorder_successor(int value);

	/* Finding inorder predecessor. */
	Node<int>* get_inorder_predecessor(Node<int> *node);
	Node<int>* get_inorder_predecessor(int value);

public: 
	/* Constructor / Destructor. */
	 AVL_Tree() : root(NULL), tree_size(0), debug_flag(false){}
	~AVL_Tree(){ clear(); }

	/* Insert a new item to the tree. */
	void insert(int x); 

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

	/* To delete a node with a specific value. */
	bool delete_node(int value); 
	bool delete_node(Node<int>* node);  

}; 

#endif
/********************************************************************/
